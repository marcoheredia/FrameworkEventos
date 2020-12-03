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

#include "fw_converter.h"

/* ------------------------- Static Variables ------------------------------- */

/* ------------------------- Static Functions ------------------------------- */

/* ---------------------------- Public API ---------------------------------- */
bool fw_converter_enable(converter_config_t config)
{
    if(FW_HARDWARE==FWHW_ESP32){
        if(config.conversion==FW_ADC)
            return fw_esp32_adc_enable(config.pin);
        else
            return fw_esp32_dac_enable(config.pin);
    }
    return false;
}

bool fw_converter_disable(converter_config_t config)
{
    if(FW_HARDWARE==FWHW_ESP32){
        if(config.conversion==FW_ADC)
                    return false;
                else
                    return fw_esp32_dac_disable(config.pin);
        }
    return false;
}

int fw_converter_read(converter_config_t config)
{
    if(FW_HARDWARE==FWHW_ESP32){
        if(config.conversion==FW_ADC)
            return fw_esp32_adc_read_voltage(config.pin);
    }
    return -1;
}

bool fw_converter_write(converter_config_t config)
{
    if(FW_HARDWARE==FWHW_ESP32){
        if(config.conversion==FW_ADC)
            return false;
        else
            return fw_esp32_dac_output_voltage(config.pin, config.mv_value);
    }
    return false;
}