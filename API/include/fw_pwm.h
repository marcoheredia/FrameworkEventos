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

#ifndef FW_PWM_H_
#define FW_PWM_H_
#include <stdbool.h>
#include "driver/mcpwm.h"
#include "driver/gpio.h"
#include "fw_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configurates the PWM, maximum number of pwms are 6
 *
 * @param pin the 
 * @param frequency pwm frequency in Hz
 * @param duty value from 0-100 which specifies which porcentage of the cycle is spent in "1" 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_pwm_set(int pin, int frequency, float duty);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_PWM_H_