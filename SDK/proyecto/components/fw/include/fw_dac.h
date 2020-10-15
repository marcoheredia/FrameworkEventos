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
#ifndef FW_DAC_H_
#define FW_DAC_H_
#include <stdbool.h>
#include "driver/gpio.h"
#include "driver/dac.h"
#include "fw_error.h"

/**
 * @brief Enable DAC
 *
 * @param pin the GPIO pin to enable DAC mode (it has to be a specific DAC pin) 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_dac_enable(int pin);

/**
 * @brief Disable the DAC mode for the pin
 *
 * @param pin the GPIO pin to disable DAC mode 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_dac_disable(int pin);

/**
 * @brief Puts the specific value in mV on the specified analogic pin
 *
 * @param pin the GPIO pin on which we want to put the value
 * @param mv_value the value in mV to put in the output pin
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_dac_output_voltage(int pin, int mv_value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_DAC_H_

