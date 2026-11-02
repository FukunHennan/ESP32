# All application sources live under main/ now (drivers, UI, wireless).
# The driver modules are mutually coupled through circular includes, so they
# stay compiled inside a single component instead of separate ones.

idf_component_register(
    SRCS
        "main.c"
        "LCD_Driver/ST7789.c"
        "LCD_Driver/Vernon_ST7789T/Vernon_ST7789T.c"
        "LVGL_Driver/LVGL_Driver.c"
        "LVGL_UI/LVGL_Example.c"
        "RGB/RGB.c"
        "SD_Card/SD_SPI.c"
        "Wireless/Wireless.c"
    INCLUDE_DIRS
        "."
        "LCD_Driver"
        "LCD_Driver/Vernon_ST7789T"
        "LVGL_Driver"
        "LVGL_UI"
        "RGB"
        "SD_Card"
        "Wireless"
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
