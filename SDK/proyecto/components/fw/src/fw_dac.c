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

#include "fw_dac.h"

/* ------------------------- Static Variables ------------------------------- */
static int dac_channel[3]={-1,25,26};
static int VDD_mv=3300;

/* ------------------------- Static Functions ------------------------------- */
/* Returns the value of the dac channel associated with the pin or -1 in case 
there is not a DAC pin*/
static int fw_dac_pin_verification(int pin)
{
    if (pin<0){
        return -1;
    }
    for(int i=0;i<3;i++){
        if (pin==dac_channel[i]){
            return i;
        }
    }
    return -1;
}

/* ---------------------------- Public API ---------------------------------- */
bool fw_dac_enable(int pin)
{
    int dac_channel=fw_dac_pin_verification(pin);
    if (dac_channel==-1)
        return false;
    esp_err_t err;
    err = dac_output_enable(dac_channel);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_dac_disable(int pin)
{
    int dac_channel=fw_dac_pin_verification(pin);
    if (dac_channel==-1)
        return false;
    esp_err_t err;
    err = dac_output_disable(dac_channel);
    if (err==FW_OK)
        return true;
    return false;
}

bool fw_dac_output_voltage(int pin, int mv_value)
{
    int dac_channel=fw_dac_pin_verification(pin);
    if (dac_channel==-1 || mv_value<0 || mv_value>3300)
        return false;
    int dac_value= mv_value*255/VDD_mv;
    esp_err_t err;
    err = dac_output_voltage(dac_channel, dac_value);
    if (err==FW_OK){
        #ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_DAC, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
        return true;
    }
    return false;
}