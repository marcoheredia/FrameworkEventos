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
static EventGroupHandle_t s_connect_event_group;
/* ------------------------- Static Functions ------------------------------- */

static void mqtt_connection_complete(esp_mqtt_event_handle_t event)
{
    if (event->event_id==MQTT_EVENT_CONNECTED) 
        xEventGroupSetBits(s_connect_event_group, 1);
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    mqtt_connection_complete(event_data);
}

/* ---------------------------- Public API ---------------------------------- */
esp_mqtt_client_handle_t fw_mqtt_start_client(char *uri)
{
	esp_mqtt_client_config_t mqtt_cfg = {
        .uri = uri,
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
	esp_err_t ret;
    ret=esp_mqtt_client_start(client);
    if(ret!=ESP_OK)
	    return NULL;
	esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
	s_connect_event_group = xEventGroupCreate();

	xEventGroupWaitBits(s_connect_event_group, 1, true, true, portMAX_DELAY);
	fw_event_post(FW_EVENT_MQTTSTART, NULL, 0, portMAX_DELAY);
	return client;
}

bool fw_mqtt_close_client(esp_mqtt_client_handle_t client)
{
	if(client==NULL)
		return false;
	esp_err_t ret;
    ret=esp_mqtt_client_stop(client);
    if(ret!=ESP_OK)
	    return false;
	return true;
}

bool fw_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos)
{
	if(client==NULL || topic==NULL || qos<0 || qos>2)
		return false;
	esp_err_t ret;
    ret=esp_mqtt_client_subscribe(client, topic, qos);
    if(ret!=ESP_OK)
	    return false;
	fw_event_post(FW_EVENT_MQTTSUBS, NULL, 0, portMAX_DELAY);
	return true;
}

bool fw_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic)
{
	if(client==NULL || topic==NULL)
		return false;
	esp_err_t ret;
    ret=esp_mqtt_client_unsubscribe(client, topic);
    if(ret!=ESP_OK)
	    return false;
	return true;
}

int fw_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos)
{
	if(client==NULL || topic==NULL || data==NULL || len<0 || qos<0 || qos>2){
		return -1;
	}
	int msg_id;

    msg_id = esp_mqtt_client_publish(client, topic, data, len, qos, 0);
	ESP_LOGI("mqtt_publish", "sent publish successful, msg_id=%d", msg_id);
	fw_event_post(FW_EVENT_MQTTPUBL, NULL, 0, portMAX_DELAY);
	return msg_id;
}