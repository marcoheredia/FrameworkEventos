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

#ifndef FW_TIMER_H_
#define FW_TIMER_H_
#include <stdbool.h>
#include "driver/timer.h"
#include "fw_error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FW_TIMER_DIVIDER 16 //  Hardware timer clock divider
#define FW_TIMER_MS ((TIMER_BASE_CLK / FW_TIMER_DIVIDER) / 1000) // convert counter value to seconds

typedef enum {
    FW_TIMER0 = 0, /*!<Hw timer0 of group 0*/
    FW_TIMER1 = 1, /*!<Hw timer1 of group 0*/
    FW_TIMER2 = 2, /*!<Hw timer0 of group 1*/
    FW_TIMER3 = 3, /*!<Hw timer1 of group 1*/
    FW_TIMERMAX,
} fw_timer_t;


/**
 * @brief Setup a timer with msecs timeout and cb as a callback.
 *
 * @param timer_id id of the timer
 * @param msecs number of mili seconds to set up the timer
 * @param auto_reload boolean to configure the timer to starts again when it ends
 * @param cb ISR handler to execute when timer is over
 * @param cb_arg arguments for the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_start_timer(fw_timer_t timer_id, int msecs, bool auto_reload, void (*cb)(void *),void *cb_arg);

/**
 * @brief Disable timer with a given timer ID
 *
 * @param timer_id id of the timer
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_stop_timer(fw_timer_t timer_id);

/**
 * @brief Clear the interruption flag for a specific timer
 *
 * @param timer_id id of the timer
 */
void fw_clear_timer_int(fw_timer_t timer_id);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_TIMER_H_