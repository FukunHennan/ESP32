# LCD-1.47-Test main component
# Driver modules live in sibling folders of the project root (LCD_Driver, LVGL_Driver, ...)
# and are mutually coupled (circular includes), so they are compiled into this component.

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)

file(GLOB MODULE_SRCS
    "${PROJECT_ROOT}/LCD_Driver/*.c"
    "${PROJECT_ROOT}/LCD_Driver/Vernon_ST7789T/*.c"
    "${PROJECT_ROOT}/LVGL_Driver/*.c"
    "${PROJECT_ROOT}/LVGL_UI/*.c"
    "${PROJECT_ROOT}/RGB/*.c"
    "${PROJECT_ROOT}/SD_Card/*.c"
    "${PROJECT_ROOT}/Wireless/*.c"
)

# main_new.c is an alternative entry point kept for reference; it must not be
# compiled together with main.c (duplicate app_main symbol).
idf_component_register(
    SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/../main.c"
        ${MODULE_SRCS}
    INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        "${PROJECT_ROOT}/LCD_Driver"
        "${PROJECT_ROOT}/LCD_Driver/Vernon_ST7789T"
        "${PROJECT_ROOT}/LVGL_Driver"
        "${PROJECT_ROOT}/LVGL_UI"
        "${PROJECT_ROOT}/RGB"
        "${PROJECT_ROOT}/SD_Card"
        "${PROJECT_ROOT}/Wireless"
    REQUIRES
        esp_lcd
        esp_driver_spi
        esp_driver_gpio
        esp_driver_ledc
        esp_timer
        fatfs
        sdmmc
        esp_wifi
        esp_event
        nvs_flash
        bt
        spi_flash
        lvgl__lvgl
        espressif__led_strip
)
