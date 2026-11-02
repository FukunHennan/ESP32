#include "LVGL_Example.h"
#include <stdio.h>

/*
 * The file shipped in the repository contained only prototypes; this is a
 * complete implementation of the dashboard demo called by main.c:
 * system info (flash / SD), WiFi & BLE scan counters and a re-scan button.
 */

static lv_obj_t * sd_label;
static lv_obj_t * flash_label;
static lv_obj_t * wifi_label;
static lv_obj_t * ble_label;
static lv_obj_t * status_label;
static lv_timer_t * refresh_timer;

static volatile bool rescan_running = false;

static void rescan_task(void * arg)
{
    rescan_running = true;
    WIFI_NUM = WIFI_Scan();
    BLE_NUM  = BLE_Scan();
    rescan_running = false;
    vTaskDelete(NULL);
}

static void rescan_btn_cb(lv_event_t * e)
{
    (void)e;
    if (rescan_running) return;
    xTaskCreate(rescan_task, "rescan", 8192, NULL, 1, NULL);
}

static void refresh_cb(lv_timer_t * t)
{
    char buf[64];
    (void)t;

    if (SDCard_Size == 0) {
        lv_label_set_text(sd_label, "SD: none");
    } else {
        snprintf(buf, sizeof(buf), "SD: %lu MB", (unsigned long)SDCard_Size);
        lv_label_set_text(sd_label, buf);
    }

    snprintf(buf, sizeof(buf), "Flash: %lu MB", (unsigned long)Flash_Size);
    lv_label_set_text(flash_label, buf);

    snprintf(buf, sizeof(buf), "WiFi AP: %u", (unsigned)WIFI_NUM);
    lv_label_set_text(wifi_label, buf);

    snprintf(buf, sizeof(buf), "BLE Dev: %u", (unsigned)BLE_NUM);
    lv_label_set_text(ble_label, buf);

    lv_label_set_text(status_label, rescan_running ? "Scanning..." : "Ready");
}

static lv_obj_t * create_info_label(lv_obj_t * parent, const char * txt)
{
    lv_obj_t * lbl = lv_label_create(parent);
    lv_label_set_text(lbl, txt);
    return lbl;
}

static void Onboard_create(lv_obj_t * parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x0b1021), 0);
    lv_obj_set_style_pad_top(parent, 14, 0);
    lv_obj_set_style_pad_column(parent, 10, 0);
    lv_obj_set_style_pad_hor(parent, 10, 0);

    lv_obj_t * title = lv_label_create(parent);
    lv_label_set_text(title, "ESP32-C6");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(title, lv_color_hex(0x61dafb), 0);

    lv_obj_t * sub = lv_label_create(parent);
    lv_label_set_text(sub, "1.47\" LCD Demo");
    lv_obj_set_style_text_color(sub, lv_color_hex(0x9aa4b2), 0);

    flash_label = create_info_label(parent, "Flash: --");
    sd_label    = create_info_label(parent, "SD: --");
    wifi_label  = create_info_label(parent, "WiFi AP: --");
    ble_label   = create_info_label(parent, "BLE Dev: --");

    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_set_size(btn, LV_PCT(80), 44);
    lv_obj_add_event_cb(btn, rescan_btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x2f6fed), LV_PART_MAIN);
    lv_obj_t * btn_lbl = lv_label_create(btn);
    lv_label_set_text(btn_lbl, LV_SYMBOL_REFRESH " Re-scan");
    lv_obj_center(btn_lbl);

    status_label = create_info_label(parent, "Ready");
    lv_obj_set_style_text_color(status_label, lv_color_hex(0x7ec69a), 0);

    refresh_cb(NULL);
}

void Lvgl_Example1(void)
{
    lv_obj_t * scr = lv_scr_act();
    Onboard_create(scr);
    refresh_timer = lv_timer_create(refresh_cb, EXAMPLE1_LVGL_TICK_PERIOD_MS, NULL);
}
