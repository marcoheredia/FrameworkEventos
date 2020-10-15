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

#ifndef FW_WIFI_H_
#define FW_WIFI_H_
#include <stdbool.h>
#include "esp_wifi.h"
#include <esp_wifi_types.h>
#include "nvs_flash.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Setup wifi access point connection
 *
 * @param wifi_ssid SSID of the wifi AP
 * @param wifi_pass password for the wifi AP 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_wifi_setup_ap(char *wifi_ssid, char *wifi_pass);

/**
 * @brief Connect to a wifi Access Point
 *
 * @param wifi_ssid SSID of the wifi AP
 * @param wifi_pass password for the wifi AP  
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_wifi_connect(char *wifi_ssid, char *wifi_pass);

/**
 * @brief Disconnect from wifi station.
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_wifi_disconnect(void);

/**
 * @brief Deinitialize wifi.
 */
void fw_wifi_stop(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_WIFI_H_
