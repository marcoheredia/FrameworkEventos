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

#include "fw_esp32_adc.h"

/* ------------------------- Static Variables ------------------------------- */
static int adc1_channel[10]={36,37,38,39,32,33,34,35,-1,-1};

static int adc2_channel[10]={4,0,2,15,13,12,14,27,25,26};

typedef struct {
    int unit;
    int channel;
} adc_pin_t;

/* ------------------------- Static Functions ------------------------------- */
/* Returns the adc channel and unit in which is the specific pin or -1 in case 
    the pin is not an adc pin
    */
static adc_pin_t fw_esp32_adc_pin_verification(int pin)
{
    adc_pin_t adc_pin;
    if (pin<0){
        adc_pin.unit=-1;
        adc_pin.channel=-1;
        return adc_pin;
    }
    for(int i=0;i<9;i++){
        if (pin==adc1_channel[i]){
            adc_pin.unit=1;
            adc_pin.channel=i;
            return adc_pin;
        }
        else if (pin==adc2_channel[i]){
            adc_pin.unit=2;
            adc_pin.channel=i;
            return adc_pin;
        }
    }
    adc_pin.unit=-1;
    adc_pin.channel=-1;
    return adc_pin;
}

/* ---------------------------- Public API ---------------------------------- */
bool fw_esp32_adc_enable(int pin)
{
    adc_pin_t adc_pin=fw_esp32_adc_pin_verification(pin);
    if (pin<0 || adc_pin.unit==-1 || adc_pin.channel==-1)
        return false;
    adc_power_on();
    esp_err_t err;
    err = adc_gpio_init(adc_pin.unit, adc_pin.channel);
    if (err!=FW_OK)
        return false;
    if(adc_pin.unit==1){
        esp_err_t err2,err3;
        err2=adc1_config_width(ADC_WIDTH_BIT_12);
        err3=adc1_config_channel_atten(adc_pin.channel,ADC_ATTEN_DB_11);
        if (err2==FW_OK && err3==FW_OK)
            return true;
    }
    else if(adc_pin.unit==2){
        esp_err_t err2;
        err2=adc2_config_channel_atten(adc_pin.channel,ADC_ATTEN_DB_11);
        if (err2==FW_OK)
            return true;
    }
    return false;
}

int fw_esp32_adc_read(int pin)
{
    adc_pin_t adc_pin=fw_esp32_adc_pin_verification(pin);
    if (adc_pin.unit==-1 || adc_pin.channel==-1)
        return -1;
    if(adc_pin.unit==1){
        fw_event_post(FW_EVENT_ADC, NULL);
        return adc1_get_raw(adc_pin.channel);
    }
    else if(adc_pin.unit==2){
        int adc_raw_value=-1;
        adc2_get_raw(adc_pin.channel,ADC_WIDTH_BIT_12, &adc_raw_value);
        fw_event_post(FW_EVENT_ADC, NULL);
        return adc_raw_value;
    }
    return -1;
}

int fw_esp32_adc_read_voltage(int pin)
{
    int adc_raw_value;
    adc_raw_value=fw_esp32_adc_read(pin);
    if(adc_raw_value==-1)
        return -1;
    else{
        return adc_raw_value*0.805861;
    }
}