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
#ifndef FW_ESP32_ADC_H_
#define FW_ESP32_ADC_H_
#include <stdbool.h>
#include "driver/adc.h"
#include "fw_defaultevents.h"
#include "fw_event.h"
#include "fw_error.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @brief Configure and enable ADC
 *
 * @param pin the GPIO pin to enable ADC mode (it has to be a specific ADC pin) 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_esp32_adc_enable(int pin);

/**
 * @brief Read from the analog pin. Returns raw value.
 *
 * @param pin the GPIO pin to read the ADC value
 *
 * @return 
 *  - integer with the raw ADC value
 */
int fw_esp32_adc_read(int pin);

/**
 * @brief Read from the specified analog pin. Returns voltage on the pin, in mV.
 *
 * @param pin the GPIO pin to read the ADC value
 *
 * @return 
 *  - float with the ADC value in mV
 */
int fw_esp32_adc_read_voltage(int pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_ESP32_ADC_H_

