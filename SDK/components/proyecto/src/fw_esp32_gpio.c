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

#include "fw_esp32_gpio.h"

/* ------------------------- Static Variables ------------------------------- */
static int8_t output_level[34]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

static bool isr_service_installed=false;

/* ------------------------- Static Functions ------------------------------- */
/* Returns the value of the output register. */
int8_t static fw_esp32_gpio_read_out(int pin)
{
    if (!GPIO_IS_VALID_OUTPUT_GPIO(pin) || pin<0)
        return -1;
    return output_level[pin];
}

/* ---------------------------- Public API ---------------------------------- */
bool fw_esp32_gpio_set_mode(int pin, gpio_mode_t mode)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0)
        return false;
    /*Pins 34 to 39 can only be inputs*/
    if ((mode==GPIO_MODE_OUTPUT || mode==GPIO_MODE_OUTPUT_OD 
        || mode==GPIO_MODE_INPUT_OUTPUT) &&pin>=34 && pin<=39)
        return false;
    esp_err_t err;
    err = gpio_set_direction(pin, mode);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_esp32_gpio_set_pull(int pin, gpio_pull_mode_t pull)
{
    /*Pins 34 to 39 dont have pullup or pulldown*/
    if (!GPIO_IS_VALID_OUTPUT_GPIO(pin) || pin<0)
        return false;
    if(pull==GPIO_PULLUP_ONLY || pull==GPIO_PULLDOWN_ONLY ||
       pull==GPIO_PULLUP_PULLDOWN || pull==GPIO_FLOATING ){
        esp_err_t err;
        err = gpio_set_pull_mode(pin,pull);
        if (err==FW_OK)
            return true;
    }
    return false;
}

bool fw_esp32_gpio_setup_input(int pin, gpio_pull_mode_t pull)
{
    bool condition=fw_esp32_gpio_set_mode(pin, GPIO_MODE_INPUT);
    if (condition==false)
        return false;
    if(pull==GPIO_PULLUP_ONLY || pull==GPIO_PULLDOWN_ONLY ||
       pull==GPIO_PULLUP_PULLDOWN || pull==GPIO_FLOATING ){
        return fw_esp32_gpio_set_pull(pin,pull);
    }
    return false;
}

bool fw_esp32_gpio_setup_output(int pin, int8_t level)
{
    if (level !=0 && level!=1)
        return false;
    esp_err_t err;
    err =gpio_set_level(pin, level);
    if (err!=FW_OK){
        return false;
    };
    bool condition=fw_esp32_gpio_set_mode(pin, GPIO_MODE_OUTPUT);
    if (condition==false)
        return false;
    output_level[pin]=level;
    return true;
}

int8_t fw_esp32_gpio_read(int pin)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0)
        return -1;
    return gpio_get_level(pin);
}

bool fw_esp32_gpio_write(int pin, int8_t level)
{
    if (!GPIO_IS_VALID_OUTPUT_GPIO(pin) || pin<0)
        return false;
    if (level !=0 && level!=1)
        return false;
    esp_err_t err;
    err =gpio_set_level(pin, level);
    if (err==FW_OK){
        output_level[pin]=level;
        return true;
    }
    return false;
    
}

bool fw_esp32_gpio_toggle(int pin)
{
    int8_t value=fw_esp32_gpio_read_out(pin);
    if(value==0)
        return fw_esp32_gpio_write(pin, 1);
    else if(value==1)
        return fw_esp32_gpio_write(pin, 0);
    return false;
}

bool fw_esp32_gpio_reset(int pin)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0)
        return false;
    esp_err_t err;
    err = gpio_reset_pin(pin);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_esp32_gpio_enable_int(int pin,gpio_int_type_t intr_type)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0 || intr_type<0 || intr_type>5)
        return false;
    esp_err_t err;
    err = gpio_set_intr_type(pin, intr_type);
    if (err!=FW_OK)
        return false;
    err = gpio_intr_enable(pin);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_esp32_gpio_disable_int(int pin)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0)
        return false;
    esp_err_t err;
    err = gpio_intr_disable(pin);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_esp32_gpio_set_int_handler(int pin, gpio_isr_t isr_handler, void *args)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0 || isr_handler==NULL)
        return false;
    if(isr_service_installed==false){
        gpio_install_isr_service(0);
        isr_service_installed=true;
    }
    esp_err_t err;
    err = gpio_isr_handler_add(pin,isr_handler, args);
    if (err==FW_OK)
        return true;
    return false;
} 

bool fw_esp32_gpio_remove_int_handler(int pin)
{
    if (!GPIO_IS_VALID_GPIO(pin) || pin<0)
        return false;
    esp_err_t err;
    err = gpio_isr_handler_remove(pin);
    if (err==FW_OK)
        return true;
    return false;
}
