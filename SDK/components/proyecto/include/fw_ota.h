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

#ifndef FW_OTA_H_
#define FW_OTA_H_
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_ota_ops.h"
#include "fw_error.h"
#define BUFFSIZE 1024
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Generates an OTA update from the url past as parameter
 *
 * @param url the url to the update file
 * @param cert_pem the url to the certificate to validate the update
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_ota_init(const char *url,const char *cert_pem);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_OTA_H_