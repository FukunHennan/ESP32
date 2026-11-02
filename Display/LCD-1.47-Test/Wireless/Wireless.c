#include "Wireless.h"

/* NimBLE (ESP32-C6) includes */
#include "freertos/semphr.h"

#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "services/gap/ble_svc_gap.h"

uint16_t BLE_NUM = 0;
uint16_t WIFI_NUM = 0;
bool Scan_finish = 0;

bool WiFi_Scan_Finish = 0;
bool BLE_Scan_Finish = 0;

void Wireless_Init(void)
{
    // Initialize NVS.
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    // WiFi
    xTaskCreatePinnedToCore(
        WIFI_Init, 
        "WIFI task",
        8192, 
        NULL, 
        1, 
        NULL, 
        0);
    // BLE
    xTaskCreatePinnedToCore(
        BLE_Init, 
        "BLE task",
        4096, 
        NULL, 
        2, 
        NULL, 
        0);
}

void WIFI_Init(void *arg)
{
    esp_netif_init();                                                     
    esp_event_loop_create_default();                                      
    esp_netif_create_default_wifi_sta();                                 
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();                 
    esp_wifi_init(&cfg);                                      
    esp_wifi_set_mode(WIFI_MODE_STA);              
    esp_wifi_start();                            

    WIFI_NUM = WIFI_Scan();
    printf("WIFI:%d\r\n",WIFI_NUM);
    
    vTaskDelete(NULL);
}

uint16_t WIFI_Scan(void)
{
    uint16_t ap_count = 0;
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    esp_wifi_scan_stop();
    WiFi_Scan_Finish =1;
    if(BLE_Scan_Finish == 1)
        Scan_finish = 1;
    return ap_count;
}

/* ---------------------------------------------------------------------------
 * BLE scanning via NimBLE (ESP32-C6)
 * ------------------------------------------------------------------------- */

#define GATTC_TAG "GATTC_TAG"
#define SCAN_DURATION 5  
#define MAX_DISCOVERED_DEVICES 100 

typedef struct {
    uint8_t address[6];
    bool is_valid;
} discovered_device_t;

static discovered_device_t discovered_devices[MAX_DISCOVERED_DEVICES];
static size_t num_discovered_devices = 0;
static size_t num_devices_with_name = 0; 

static bool ble_synced = false;
static SemaphoreHandle_t scan_done_sem = NULL;

static bool is_device_discovered(const uint8_t *addr) {
    for (size_t i = 0; i < num_discovered_devices; i++) {
        if (memcmp(discovered_devices[i].address, addr, 6) == 0) {
            return true;
        }
    }
    return false;
}

static void add_device_to_list(const uint8_t *addr) {
    if (num_discovered_devices < MAX_DISCOVERED_DEVICES) {
        memcpy(discovered_devices[num_discovered_devices].address, addr, 6);
        discovered_devices[num_discovered_devices].is_valid = true;
        num_discovered_devices++;
    }
}

static bool extract_device_name(const uint8_t *adv_data, uint8_t adv_data_len, char *device_name, size_t max_name_len) {
    size_t offset = 0;
    while (offset < adv_data_len) {
        if (adv_data[offset] == 0) break; 

        uint8_t length = adv_data[offset];
        if (length == 0 || offset + length > adv_data_len) break; 

        uint8_t type = adv_data[offset + 1];
        if (type == 0x09 || type == 0x08) { /* complete / short local name */
            if (length > 1 && length - 1 < max_name_len) {
                memcpy(device_name, &adv_data[offset + 2], length - 1);
                device_name[length - 1] = '\0'; 
                return true;
            } else {
                return false;
            }
        }
        offset += length + 1;
    }
    return false;
}

static int gap_event_cb(struct ble_gap_event *event, void *arg)
{
    char device_name[100] = {0};
    const uint8_t *addr = event->disc.addr.val;

    switch (event->type) {
        case BLE_GAP_EVENT_DISC:
            if (!is_device_discovered(addr)) {
                add_device_to_list(addr);
                BLE_NUM++; 

                if (extract_device_name(event->disc.data, event->disc.length_data, device_name, sizeof(device_name)) && device_name[0]) {
                    num_devices_with_name++;
                    printf("Found device: %02X:%02X:%02X:%02X:%02X:%02X\n        Name: %s\n        RSSI: %d\r\n",
                           addr[0], addr[1], addr[2], addr[3], addr[4], addr[5],
                           device_name, event->disc.rssi);
                    printf("\r\n");
                } else {
                    printf("Found device: %02X:%02X:%02X:%02X:%02X:%02X\n        Name: Unknown\n        RSSI: %d\r\n",
                           addr[0], addr[1], addr[2], addr[3], addr[4], addr[5],
                           event->disc.rssi);
                    printf("\r\n");
                }
            }
            break;

        case BLE_GAP_EVENT_DISC_COMPLETE:
            ESP_LOGI(GATTC_TAG, "Scan complete. Total devices found: %d (with names: %d)", BLE_NUM, (int)num_devices_with_name);
            if (scan_done_sem) {
                xSemaphoreGive(scan_done_sem);
            }
            break;

        default:
            break;
    }
    return 0;
}

static void on_sync(void)
{
    ble_synced = true;
}

static void on_reset(int reason)
{
    ESP_LOGE(GATTC_TAG, "NimBLE reset, status code = %d\n", reason);
}

static void nimble_host_task(void *param)
{
    nimble_port_run();
    nimble_port_freertos_deinit();
}

void BLE_Init(void *arg)
{
    esp_err_t err = nimble_port_init();
    if (err != ESP_OK) {
        printf("%s nimble_port_init failed: %s\n", __func__, esp_err_to_name(err));
        vTaskDelete(NULL);
        return;
    }

    ble_hs_cfg.sync_cb = on_sync;
    ble_hs_cfg.reset_cb = on_reset;

    scan_done_sem = xSemaphoreCreateBinary();

    nimble_port_freertos_init(nimble_host_task);

    /* Wait until the host stack has synchronised with the controller */
    while (!ble_synced) {
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    BLE_Scan();

    vTaskDelete(NULL);
}

uint16_t BLE_Scan(void)
{
    struct ble_gap_disc_params disc_params = {
        .filter_duplicates = 1,
        .passive = 0,
        .itvl = 0x50,
        .window = 0x30,
    };

    BLE_NUM = 0;
    num_discovered_devices = 0;
    num_devices_with_name = 0;

    printf("Starting BLE scan...\n");
    int rc = ble_gap_disc(BLE_OWN_ADDR_PUBLIC,
                          (SCAN_DURATION + 1) * 1000,
                          &disc_params,
                          gap_event_cb, NULL);
    if (rc != 0) {
        printf("ble_gap_disc failed: %d\n", rc);
        return BLE_NUM;
    }

    /* Block until the scan completes (timeout is a safety fallback) */
    xSemaphoreTake(scan_done_sem, pdMS_TO_TICKS((SCAN_DURATION + 3) * 1000));
    ble_gap_disc_cancel();

    printf("Stopping BLE scan...\n");
    BLE_Scan_Finish = 1;
    if(WiFi_Scan_Finish == 1)
        Scan_finish = 1;
    return BLE_NUM;
}
