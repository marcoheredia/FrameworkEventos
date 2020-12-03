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

#include "fw_esp32_pwm.h"

/* ------------------------- Static Variables ------------------------------- */
static int pwm_number=0;
static int pin_num[6];

/* ------------------------- Static Functions ------------------------------- */

static int pwm_num_get(int pin)
{
    for(int i=0;i<6;i++){
        if(pin_num[i]==pin)
            return i;
    }
    return -1;
}

static bool pwm_edit(int pwm_num, int frequency, float duty){
    esp_err_t err1, err2;
    err1 = mcpwm_set_frequency(MCPWM_UNIT_0, pwm_num, frequency);
    if((pwm_num%2)==0)
        err2 = mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, duty);
    else
        err2 = mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_B, duty);
    if (err1==FW_OK && err2==FW_OK)
        return true;
    return false;
}

static bool pwm_set(int pwm_num, int pin, int frequency, float duty){
    esp_err_t err1, err2, err3, err4;
    err1 = mcpwm_gpio_init(MCPWM_UNIT_0, pwm_num, pin);
    err2 = mcpwm_set_frequency(MCPWM_UNIT_0, pwm_num, frequency);
    if((pwm_num%2)==0)
        err3 = mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, duty);
    else
        err3 = mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_B, duty);
    err4 = mcpwm_start(MCPWM_UNIT_0, MCPWM_TIMER_2);
    if (err1==FW_OK && err2==FW_OK && err3==FW_OK && err4==FW_OK){
        pin_num[pwm_number]=pin;
        pwm_number++;
        return true;
    }
    return false;
}

/* ---------------------------- Public API ---------------------------------- */

bool fw_esp32_pwm_set(int pin, int frequency, float duty)
{
	if (!GPIO_IS_VALID_OUTPUT_GPIO(pin) || pin<0)
        return false;
    if(frequency<=0  || duty<0 || duty>100)
        return false;
    int pwm_num=pwm_num_get(pin);
    if(pwm_num!=-1){
	fw_event_post(FW_EVENT_PWM, NULL, 0, portMAX_DELAY);
        return pwm_edit(pwm_num, frequency, duty);
    }
    else{
        if (pwm_number>=5)
            return false;
        fw_event_post(FW_EVENT_PWM, NULL, 0, portMAX_DELAY);
        return pwm_set(pwm_number, pin, frequency, duty);
    }
}