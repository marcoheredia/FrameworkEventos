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

#ifndef FW_ESP32_TIMER_H_
#define FW_ESP32_TIMER_H_
#include <stdbool.h>
#include "esp_log.h"
#include "esp_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Setup the timer
 *
 * @param msec Miliseconds to set timer
 * @param handle_args arguments to pass to the cb
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_esp32_timer_set(int msec, esp_timer_handle_t handle_args);

/**
 * @brief Delete the timer
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_esp32_timer_delete(void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_ESP32_TIMER_H_
