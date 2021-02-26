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

#include "fw_esp32_timer.h"

/* ------------------------- Static Variables ------------------------------- */
static esp_timer_handle_t fw_timer_handle;

/* ------------------------- Static Functions ------------------------------- */
static void fw_timer_callback(void* arg);
/* ---------------------------- Public API ---------------------------------- */

bool fw_esp32_timer_set(int msec, esp_timer_handle_t handle_args)
{
    if (msec<0)
        return false;
    esp_err_t ret,ret2;

    const esp_timer_create_args_t timer_args = {
        .callback = &fw_timer_callback,
        .arg = (void*) handle_args,
        .name = "fw_timer"
    };

    ret=esp_timer_create(&timer_args, &fw_timer_handle);
    ret2=esp_timer_start_once(fw_timer_handle, msec*1000);
    if(ret!=ESP_OK || ret2!=ESP_OK)
        return false;
    else
        return true;
}

bool fw_esp32_timer_delete(){
    esp_err_t ret,ret2;
    ret=esp_timer_stop(fw_timer_handle);
    ret2=esp_timer_delete(fw_timer_handle);
    if(ret!=ESP_OK || ret2!=ESP_OK)
        return false;
    else
        return true;
}
