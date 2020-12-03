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

#include "fw_gpio.h"

/* ------------------------- Static Variables ------------------------------- */


/* ------------------------- Static Functions ------------------------------- */


/* ---------------------------- Public API ---------------------------------- */
bool fw_gpio_set_mode(int pin, gpio_mode_t mode)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_set_mode(pin,mode);
    return false;
}

bool fw_gpio_set_pull(int pin, gpio_pull_mode_t pull)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_set_pull(pin,pull);
    return false;
}

bool fw_gpio_setup_input(int pin, gpio_pull_mode_t pull)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_setup_input(pin,pull);
    return false;
}

bool fw_gpio_setup_output(int pin, int8_t level)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_setup_output(pin,level);
    return false;
}

int8_t fw_gpio_read(int pin)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_read(pin);
    return -1;
}

bool fw_gpio_write(int pin, int8_t level)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_write(pin,level);
    return false;
    
}

bool fw_gpio_toggle(int pin)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_toggle(pin);
    return false;
}

bool fw_gpio_reset(int pin)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_reset(pin);
    return false;
}

bool fw_gpio_enable_int(int pin,gpio_int_type_t intr_type)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_enable_int(pin,intr_type);
    return false;
}

bool fw_gpio_disable_int(int pin)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_disable_int(pin);
    return false;
}

bool fw_gpio_set_int_handler(int pin, gpio_isr_t isr_handler, void *args)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_set_int_handler(pin,isr_handler,args);
    return false;
} 

bool fw_gpio_remove_int_handler(int pin)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_gpio_remove_int_handler(pin);
    return false;
}
