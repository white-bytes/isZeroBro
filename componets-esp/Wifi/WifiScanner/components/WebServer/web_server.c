#include <esp_http_server.h>
#include <esp_log.h>
#include <esp_spiffs.h>
#include <cJSON.h>
#include "web_server.h"
#include "wifi_scanner.h"

static const char *TAG = "web_server";

/* Handler for the scan API */
static esp_err_t scan_get_handler(httpd_req_t *req)
{
    int count = 0;
    
    // Perform WiFi Scan
    wifi_ap_record_t *ap_info = wifiScan(&count);
    
    // Create JSON Response
    cJSON *root = cJSON_CreateArray();
    if (ap_info != NULL) {
        for (int i = 0; i < count; i++) {
            cJSON *item = cJSON_CreateObject();
            cJSON_AddStringToObject(item, "ssid", (char *)ap_info[i].ssid);
            cJSON_AddNumberToObject(item, "rssi", ap_info[i].rssi);
            cJSON_AddNumberToObject(item, "channel", ap_info[i].primary);
            cJSON_AddStringToObject(item, "auth", printAuthMode(ap_info[i].authmode));
            cJSON_AddItemToArray(root, item);
        }
        free(ap_info);
    }
    
    const char *json_response = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    if (json_response) {
        httpd_resp_send(req, json_response, strlen(json_response));
        free((void *)json_response);
    } else {
        httpd_resp_send(req, "[]", 2);
    }
    
    cJSON_Delete(root);
    return ESP_OK;
}

/* File Handler (Serve Static Files from SPIFFS) */
static esp_err_t file_get_handler(httpd_req_t *req)
{
    char filepath[64];
    const char *filename = req->uri;
    
    // If root, serve index.html (or scanner page)
    if (strcmp(filename, "/") == 0) {
        strcpy(filepath, "/spiffs/scanner/index.html");
    } else {
        snprintf(filepath, sizeof(filepath), "/spiffs%s", filename);
    }

    FILE *fd = fopen(filepath, "r");
    if (!fd) {
        ESP_LOGE(TAG, "File not found: %s", filepath);
        // Fallback to try and find it without /spiffs prefix if path is messed/redirect
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Set Content Type
    if (strstr(filename, ".html")) {
        httpd_resp_set_type(req, "text/html");
    } else if (strstr(filename, ".css")) {
        httpd_resp_set_type(req, "text/css");
    } else if (strstr(filename, ".js")) {
        httpd_resp_set_type(req, "application/javascript");
    } else if (strstr(filename, ".png")) {
        httpd_resp_set_type(req, "image/png");
    } else if (strstr(filename, ".ico")) {
        httpd_resp_set_type(req, "image/x-icon");
    }

    char *chunk = malloc(1024);
    size_t chunksize;
    while ((chunksize = fread(chunk, 1, 1024, fd)) > 0) {
        httpd_resp_send_chunk(req, chunk, chunksize);
    }
    free(chunk);
    fclose(fd);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

/* Initialize SPIFFS */
void init_spiffs(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }
}

/* Initialize the web server */
void start_webserver(void)
{
    // Initialize File System
    init_spiffs();

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 12; // Increase handler count
    config.stack_size = 8192;
    config.uri_match_fn = httpd_uri_match_wildcard; // Enable wildcard matching

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        
        // API Handler
        httpd_uri_t scan = {
            .uri       = "/scan",
            .method    = HTTP_GET,
            .handler   = scan_get_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &scan);

        // Wildcard File Handler (Catch-all for static files)
        httpd_uri_t file_serve = {
            .uri       = "/*",
            .method    = HTTP_GET,
            .handler   = file_get_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &file_serve);
        
        return;
    }

    ESP_LOGE(TAG, "Error starting server!");
}
