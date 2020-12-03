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
#ifndef FW_CONVERTER_H_
#define FW_CONVERTER_H_
#include <stdbool.h>
#include "fw_hardware.h"
#include "fw_esp32_adc.h"
#include "fw_esp32_dac.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FW_ADC 7051
#define FW_DAC 7052

typedef struct {
	int conversion;
    int pin;
    int mv_value;
} converter_config_t;

/**
 * @brief Enable DAC
 *
* @param config the structure with the converter parameters
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_converter_enable(converter_config_t config);

/**
 * @brief Disable the DAC mode for the pin
 *
 * @param config the structure with the converter parameters
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_converter_disable(converter_config_t config);

/**
 * @brief Read from the specified analog pin. Returns voltage on the pin, in mV.
 *
 * @param config the structure with the converter parameters
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
int fw_converter_read(converter_config_t config);

/**
 * @brief Puts the specific value in mV on the specified analogic pin
 *
 * @param config the structure with the converter parameters
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_converter_write(converter_config_t config);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_CONVERTER_H_

