#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <cJSON.h>
#include "esp_crt_bundle.h"  // Include the default certificate bundle

#include "wifiSta.h"
#include "config.h"

#define EXAMPLE_ESP_WIFI_SSID            WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS            WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY        5

#define ESP_WIFI_SCAN_AUTH_MODE_THRESH   WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SAE_MODE                WPA3_SAE_PWE_BOTH
#define EXAMPLE_H2E_IDENTIFIER           ""

static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = "wifi station";

static int s_retry_num = 0;

// OpenWeatherMap API key and city
char open_weather_map_api_key[] = OPEN_WEATHER_MAP_API_KEY;
char city[] = "Birmingham";
char country_code[] = "GB";

// HTTP response data
char *response_data = NULL;
size_t response_len = 0;
bool all_chunks_received = false;

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESH,
            .sae_pwe_h2e = ESP_WIFI_SAE_MODE,
            .sae_h2e_identifier = EXAMPLE_H2E_IDENTIFIER,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

void get_temp_pressure_humidity(const char *json_string)
{
    cJSON *root = cJSON_Parse(json_string);
    cJSON *obj = cJSON_GetObjectItemCaseSensitive(root, "main");

    float temp = cJSON_GetObjectItemCaseSensitive(obj, "temp")->valuedouble;
    int pressure = cJSON_GetObjectItemCaseSensitive(obj, "pressure")->valueint;
    int humidity = cJSON_GetObjectItemCaseSensitive(obj, "humidity")->valueint;
    printf("Temperature: %0.00f°k\nPressure: %d hPa\nHumidity: %d%%\n", temp, pressure, humidity);
    
    cJSON_Delete(root);
    free(response_data);
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            response_data = realloc(response_data, response_len + evt->data_len);
            memcpy(response_data + response_len, evt->data, evt->data_len);
            response_len += evt->data_len;
            break;
        case HTTP_EVENT_ON_FINISH:
            all_chunks_received = true;
            ESP_LOGI("OpenWeatherAPI", "Received data: %s", response_data);
            // get_temp_pressure_humidity(response_data);
            break;
        default:
            break;
    }
    return ESP_OK;
}

void wifi_test_get(void)
{
// 52.39731507393248, -1.8167086257212137
    // char open_weather_map_url[200];
    // snprintf(open_weather_map_url,
    //          sizeof(open_weather_map_url),
    //          "%s%s%s%s%s%s",
    //          "http://api.openweathermap.org/data/2.5/weather?q=",
    //          city,
    //          ",",
    //          country_code,
    //          "&APPID=",
    //          open_weather_map_api_key);

	// snprintf(open_weather_map_url,
    //          sizeof(open_weather_map_url),
    //          "%s%s%s%s%s%s",
	// 		);

    ESP_LOGI(TAG, "Starting test");

    char open_weather_map_url[] = "https://api.open-meteo.com/v1/forecast?latitude=52.4814&longitude=-1.8998&hourly=temperature_2m,weather_code&timeformat=unixtime";

    esp_http_client_config_t config = {
        .url = open_weather_map_url,
        .method = HTTP_METHOD_GET,
        .event_handler = _http_event_handler,
        .crt_bundle_attach = esp_crt_bundle_attach,  // Use the default certificate bundle
    };

    ESP_LOGI(TAG, "Setup complete");

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");

    // 52.39731507393248, -1.8167086257212137
    // char open_weather_map_url[200];
    // snprintf(open_weather_map_url,
    //          sizeof(open_weather_map_url),
    //          "%s%s%s%s%s%s",
    //          "http://api.openweathermap.org/data/2.5/weather?q=",
    //          city,
    //          ",",
    //          country_code,
    //          "&APPID=",
    //          open_weather_map_api_key);

	// snprintf(open_weather_map_url,
    //          sizeof(open_weather_map_url),
    //          "%s%s%s%s%s%s",
	// 		);

    ESP_LOGI(TAG, "Handler created");

    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        int status_code = esp_http_client_get_status_code(client);
        if (status_code == 200)
        {
            ESP_LOGI(TAG, "Message sent Successfully");
        }
        else
        {
            ESP_LOGW(TAG, "Message sent Failed 1");
        }
    }
    else
    {
        ESP_LOGW(TAG, "Message sent Failed 2");
    }
    esp_http_client_cleanup(client);
}