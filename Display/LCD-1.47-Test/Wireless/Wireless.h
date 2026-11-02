#pragma once

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"

/* BLE stack on ESP32-C6 is NimBLE (Bluedroid is not available for this target
 * in ESP-IDF v5.4). The public API below is unchanged from the original
 * Bluedroid-based implementation. */

extern uint16_t BLE_NUM;
extern uint16_t WIFI_NUM;
extern bool Scan_finish;

void Wireless_Init(void);
void WIFI_Init(void *arg);
uint16_t WIFI_Scan(void);
void BLE_Init(void *arg);
uint16_t BLE_Scan(void);
