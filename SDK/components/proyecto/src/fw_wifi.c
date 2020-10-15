/* 
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <string.h>
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "tcpip_adapter.h"
#include "freertos/event_groups.h"
#include "fw_wifi.h"


/* ------------------------- Static Variables ------------------------------- */
#define GOT_IPV4_BIT BIT(0)
#define CONNECTED_BITS (GOT_IPV4_BIT)
static EventGroupHandle_t s_connect_event_group;
static ip4_addr_t s_ip_addr;
static const char* s_connection_name;

/* ------------------------- Static Functions ------------------------------- */

static void on_got_ip(void* arg, esp_event_base_t event_base,
                      int32_t event_id, void* event_data)
{
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    memcpy(&s_ip_addr, &event->ip_info.ip, sizeof(s_ip_addr));
    xEventGroupSetBits(s_connect_event_group, GOT_IPV4_BIT);
}

/* ---------------------------- Public API ---------------------------------- */

bool fw_wifi_setup_ap(char *wifi_ssid, char *wifi_pass)
{
	if(wifi_ssid==NULL || wifi_pass==NULL)
		return false;
	nvs_flash_init();
    tcpip_adapter_init();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    esp_wifi_set_mode(WIFI_MODE_AP);
	wifi_config_t ap_config = {
        .ap ={
			.ssid_len = 0,
			.channel = 0,
			.authmode = WIFI_AUTH_WPA2_PSK,
			.ssid_hidden = 0,
			.max_connection = 4, // number of clients to allow
			.beacon_interval = 100 // default value
        }
    };
    strcpy((char *)ap_config.ap.ssid,(char *)wifi_ssid);
    strcpy((char *)ap_config.ap.password,(char *)wifi_pass);
    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
    esp_err_t ret;
    ret=esp_wifi_start();
    if(ret!=ESP_OK)
	    return false;
    #ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_WIFIAP, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
	return true;
}

bool fw_wifi_connect(char *wifi_ssid, char *wifi_pass)
{
    nvs_flash_init();
    tcpip_adapter_init();
    esp_event_loop_create_default();

    if (s_connect_event_group != NULL) {
        return false;
    }
    s_connect_event_group = xEventGroupCreate();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &on_got_ip, NULL);
    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = "",
        },
    };
    strcpy((char *)wifi_config.sta.ssid,wifi_ssid);
    strcpy((char *)wifi_config.sta.password,wifi_pass);


    ESP_LOGI("wifi_connect", "Connecting to %s...", wifi_config.sta.ssid);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();
    s_connection_name = wifi_ssid;
    xEventGroupWaitBits(s_connect_event_group, CONNECTED_BITS, true, true, portMAX_DELAY);
    ESP_LOGI("wifi_connect", "Connected to %s", s_connection_name);
    ESP_LOGI("wifi_connect", "IPv4 address: " IPSTR, IP2STR(&s_ip_addr));
    #ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_WIFICON, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
    return true;
}

bool fw_wifi_disconnect(void)
{
	esp_err_t ret;
	ret=esp_wifi_disconnect();
	if(ret!=ESP_OK)
	    return false;
    #ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_WIFIDIS, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
	return true;
}

void fw_wifi_stop(void)
{
	esp_wifi_stop();
	esp_wifi_deinit();
}