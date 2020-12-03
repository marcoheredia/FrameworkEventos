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

#include "fw_mqtt.h"

/* ------------------------- Static Variables ------------------------------- */

/* ------------------------- Static Functions ------------------------------- */

/* ---------------------------- Public API ---------------------------------- */
esp_mqtt_client_handle_t fw_mqtt_start_client(char *uri)
{
	if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_mqtt_start_client(uri);
	return NULL;
}

bool fw_mqtt_close_client(esp_mqtt_client_handle_t client)
{
	if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_mqtt_close_client(client);
    return false;
}

bool fw_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos)
{
	if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_mqtt_client_subscribe(client, topic, qos);
    return false;
}

bool fw_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic)
{
	if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_mqtt_client_unsubscribe(client,topic);
    return false;
}

int fw_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos)
{
	if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_mqtt_client_publish(client,topic,data,len,qos);
    return -1;
}