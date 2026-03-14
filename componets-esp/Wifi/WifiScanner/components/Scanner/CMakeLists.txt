idf_component_register(SRCS "wifi_scanner.c"
                       INCLUDE_DIRS "."
                       REQUIRES freertos esp_wifi log esp_event esp_netif)