/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "ST7789.h"
#include "SD_SPI.h"
#include "RGB.h"
#include "Wireless.h"
#include "LVGL_Example.h"
#include "esp_log.h"

static const char *TAG_MAIN = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG_MAIN, "========================================");
    ESP_LOGI(TAG_MAIN, "ESP32-C6 LCD Display System Starting...");
    ESP_LOGI(TAG_MAIN, "========================================");

    // Step 1: Initialize Flash and get size information
    ESP_LOGI(TAG_MAIN, "[1/6] Initializing Flash...");
    Flash_Searching();

    // Step 2: Initialize Wireless (WiFi and BLE) - Start early to allow parallel scanning
    ESP_LOGI(TAG_MAIN, "[2/6] Initializing Wireless (WiFi & BLE)...");
    Wireless_Init();

    // Step 3: Initialize RGB LED
    ESP_LOGI(TAG_MAIN, "[3/6] Initializing RGB LED...");
    RGB_Init();
    RGB_Example();

    // Step 4: Initialize SD Card (must be before LCD as they share SPI bus)
    ESP_LOGI(TAG_MAIN, "[4/6] Initializing SD Card...");
    SD_Init();

    // Step 5: Initialize LCD Display
    ESP_LOGI(TAG_MAIN, "[5/6] Initializing LCD Display...");
    LCD_Init();
    BK_Light(50);  // Set initial backlight to 50%

    // Step 6: Initialize LVGL and create UI
    ESP_LOGI(TAG_MAIN, "[6/6] Initializing LVGL...");
    LVGL_Init();

    ESP_LOGI(TAG_MAIN, "========================================");
    ESP_LOGI(TAG_MAIN, "System Initialization Complete!");
    ESP_LOGI(TAG_MAIN, "========================================");

/******************** Demo *********************/
    Lvgl_Example1();

    // Uncomment to enable other demos:
    // lv_demo_widgets();
    // lv_demo_keypad_encoder();
    // lv_demo_benchmark();
    // lv_demo_stress();
    // lv_demo_music();

    ESP_LOGI(TAG_MAIN, "Entering main loop...");
    while (1) {
        // LVGL task handler - 10ms delay provides good balance between responsiveness and CPU usage
        // To improve performance: raise task priority or reduce handler period
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }
}
