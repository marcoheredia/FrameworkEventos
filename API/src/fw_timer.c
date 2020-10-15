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

#include "fw_timer.h"
#include "esp_log.h"
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"


/* ------------------------- Static Variables ------------------------------- */

/* ------------------------- Static Functions ------------------------------- */
/* Configurates a timer, which will execute an callback function when the timer is over*/
static bool fw_init_timer(timer_group_t group_num, timer_idx_t timer_num, int msecs, 
		bool auto_reload, void (*cb)(void *),void *cb_arg)
{
	/* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = FW_TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = auto_reload;
    timer_init(group_num, timer_num, &config);
    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(group_num, timer_num, 0);
    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(group_num, timer_num, msecs * FW_TIMER_MS);
    timer_enable_intr(group_num, timer_num);
    timer_isr_callback_add(group_num, timer_num, cb, cb_arg, 0);
    esp_err_t err = timer_start(group_num, timer_num);
    if (err==FW_OK)
        return true;
    return false;
}

/**
* Pauses an specific timer
*/
static bool fw_pause_timer(timer_group_t group_num, timer_idx_t timer_num)
{
    esp_err_t err = timer_pause(group_num,timer_num);
    timer_disable_intr(group_num, timer_num);
    if (err==FW_OK)
        return true;
    return false;
}


/* ---------------------------- Public API ---------------------------------- */

bool fw_start_timer(fw_timer_t timer_id, int msecs, bool auto_reload, void (*cb)(void *),void *cb_arg)
{
	if(timer_id>=FW_TIMER0 && timer_id<=FW_TIMER3 && msecs>0){
		switch(timer_id){
			case FW_TIMER0:{
				return fw_init_timer(0, 0, msecs, auto_reload, cb,cb_arg);
			}
			case FW_TIMER1:{
				return fw_init_timer(0, 1, msecs, auto_reload, cb,cb_arg);
			}
			case FW_TIMER2:{
				return fw_init_timer(1, 0, msecs, auto_reload, cb,cb_arg);
			}
			case FW_TIMER3:{
				return fw_init_timer(1, 1, msecs, auto_reload, cb,cb_arg);
			}
			default:
				return false;
		}
	}
	return false;
}

bool fw_stop_timer(fw_timer_t timer_id)
{
	if(timer_id>=FW_TIMER0 && timer_id<=FW_TIMER3){
		switch(timer_id){
			case FW_TIMER0:{
				return fw_pause_timer(0, 0);
				break;
			}
			case FW_TIMER1:{
				return fw_pause_timer(0, 1);
				break;
			}
			case FW_TIMER2:{
				return fw_pause_timer(1, 0);
				break;
			}
			case FW_TIMER3:{
				return fw_pause_timer(1, 1);
				break;
			}
			default:
				return false;
				break;
		}
	}
	return false;
}

void fw_clear_timer_int(fw_timer_t timer_id)
{
	if(timer_id>=FW_TIMER0 && timer_id<=FW_TIMER3){
		switch(timer_id){
			case FW_TIMER0:{
				TIMERG0.int_clr_timers.t0 = 1;
				break;
			}
			case FW_TIMER1:{
				TIMERG0.int_clr_timers.t1 = 1;
				break;
			}
			case FW_TIMER2:{
				TIMERG1.int_clr_timers.t0 = 1;
				break;
			}
			case FW_TIMER3:{
				TIMERG1.int_clr_timers.t1 = 1;
				break;
			}
			default:
				break;
		}
	}
}