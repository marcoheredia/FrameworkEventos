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

#ifndef FW_MQTT_H_
#define FW_MQTT_H_
#include <stdbool.h>
#include "fw_defaultevents.h"
#include "fw_event.h"
#include "mqtt_client.h"
#include "esp_event.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start a MQTT client with the configuration parameters
 *
 * @param uri the URI of the broker to connect, for example
 * 		mqtt://iot.eclipse.org   -- MQTT over TCP, default port 1883
 * 		mqtt://iot.eclipse.org:1884 -- MQTT over TCP, port 1884
 * 		mqtt://username:password@iot.eclipse.org:1884 -- MQTT over TCP, port 1884, with username
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
esp_mqtt_client_handle_t fw_mqtt_start_client(char *uri);

/**
 * @brief Close the MQTT client with it MQTT handler
 *
 * @param client the handler which want to close MQTT client
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_mqtt_close_client(esp_mqtt_client_handle_t client);

/**
 * @brief Subscribe the MQTT Client to a specific topic
 *
 * @param client the handler from the MQTT client to subscribe
 * @param topic the topic to which you want to subscribe
 * @param qos value between 0 and 2 to determine the quality of service
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos);

/**
 * @brief Unsubcribe the MQTT Client from a specific topic
 *
 * @param client the handler from the MQTT client to unsubscribe
 * @param topic the topic to which you want to unsubscribe
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic);

/**
 * @brief Publish a MQTT message for a specific topic
 *
 * @param client the handler from the MQTT client to unsubscribe
 * @param topic the topic to which you want to unsubscribe
 * @param data buffer with the message to publish
 * @param len maximum buffer size to publish
 * @param qos value between 0 and 2 to determine the quality of service
 *
 * @return the message ID of the subscribed message or 0 if cannot publish 
 */
int fw_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_MQTT_H_
