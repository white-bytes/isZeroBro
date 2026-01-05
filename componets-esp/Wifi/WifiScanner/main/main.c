#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h" // Include the esp_event header
#include "nvs_flash.h"
#include "wifi_scanner.h"
#include "web_server.h"

static const char* TAG = "MAIN";

void app_main() {

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK( ret );
    
    // Initialize Scanner (AP+STA mode)
    wifiScannerInit();
    
    // Start Web Server
    start_webserver();
    
    // Main loop (can be empty or used for other tasks)
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}