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

#include "fw_event.h"

/* ------------------------- Static Variables ------------------------------- */
static esp_event_loop_handle_t s_maximum_priority_loop = NULL;
static esp_event_loop_handle_t s_medium_priority_loop = NULL;
static esp_event_loop_handle_t s_minimum_priority_loop = NULL;

/* ------------------------- Static Functions ------------------------------- */

/* ---------------------------- Public API ---------------------------------- */
ESP_EVENT_DEFINE_BASE(TASK_EVENTS);

fw_err_t fw_event_handler_register(int32_t event_id, esp_event_handler_t event_handler, void* event_handler_arg)
{
    return fw_event_med_priority_handler_register(TASK_EVENTS,event_id,event_handler,event_handler_arg);
}

fw_err_t fw_event_handler_unregister(int32_t event_id, esp_event_handler_t event_handler)
{
    return fw_event_med_priority_handler_unregister(TASK_EVENTS,event_id,event_handler);
}

fw_err_t fw_event_post(int32_t event_id, void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    return fw_event_med_priority_post(TASK_EVENTS,event_id,event_data,event_data_size,ticks_to_wait);
}

fw_err_t fw_event_loop_create()
{
    return fw_event_med_priority_loop_create();
}

fw_err_t fw_event_loop_delete()
{
    return fw_event_med_priority_loop_delete();
}

fw_err_t fw_event_loop_run(TickType_t ticks_to_run)
{
    return fw_event_med_priority_loop_run(ticks_to_run);
}

fw_err_t fw_event_max_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg)
{
    if (s_maximum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_handler_register_with(s_maximum_priority_loop, event_base, event_id,
            event_handler, event_handler_arg);
}

fw_err_t fw_event_max_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler)
{
    if (s_maximum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_handler_unregister_with(s_maximum_priority_loop, event_base, event_id,
            event_handler);
}

fw_err_t fw_event_max_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    if (s_maximum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_post_to(s_maximum_priority_loop, event_base, event_id,
            event_data, event_data_size, ticks_to_wait);
}

fw_err_t fw_event_max_priority_loop_create()
{
    if (s_maximum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }
    esp_event_loop_args_t max_priority_loop_args = {
        .queue_size = CONFIG_SYSTEM_EVENT_QUEUE_SIZE,
        .task_name = "max_loop",
        .task_stack_size = ESP_TASKD_EVENT_STACK,
        .task_priority = ESP_TASKD_EVENT_PRIO+1,
        .task_core_id = 0
    };
    fw_err_t err;
    err = esp_event_loop_create(&max_priority_loop_args, &s_maximum_priority_loop);
    if (err != ESP_OK) {
        return err;
    }
     return ESP_OK;
}

fw_err_t fw_event_max_priority_loop_delete()
{
    if (!s_maximum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }
    fw_err_t err;
    err = esp_event_loop_delete(s_maximum_priority_loop);
    if (err != ESP_OK) {
        return err;
    }
    s_maximum_priority_loop = NULL;
    return ESP_OK;
}

fw_err_t fw_event_max_priority_loop_run(TickType_t ticks_to_run)
{
    if (!s_maximum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }
    fw_err_t err;
    err = esp_event_loop_run(s_maximum_priority_loop, ticks_to_run);
    if (err != ESP_OK) {
        return err;
    }
    return ESP_OK;
}

fw_err_t fw_event_med_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg)
{
    if (s_medium_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_handler_register_with(s_medium_priority_loop, event_base, event_id,
            event_handler, event_handler_arg);
}

fw_err_t fw_event_med_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler)
{
    if (s_medium_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_handler_unregister_with(s_medium_priority_loop, event_base, event_id,
            event_handler);
}

fw_err_t fw_event_med_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    if (s_medium_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_event_post_to(s_medium_priority_loop, event_base, event_id,
            event_data, event_data_size, ticks_to_wait);
}

fw_err_t fw_event_med_priority_loop_create()
{
    if (s_medium_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_event_loop_args_t med_priority_loop_args = {
        .queue_size = CONFIG_SYSTEM_EVENT_QUEUE_SIZE,
        .task_name = "med_loop",
        .task_stack_size = ESP_TASKD_EVENT_STACK,
        .task_priority = ESP_TASKD_EVENT_PRIO,
        .task_core_id = 0
    };
    fw_err_t err;
    err = esp_event_loop_create(&med_priority_loop_args, &s_medium_priority_loop);
    if (err != ESP_OK) {
        return err;
    }
     return ESP_OK;
}

fw_err_t fw_event_med_priority_loop_delete()
{
    if (!s_medium_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    fw_err_t err;
    
    err = esp_event_loop_delete(s_medium_priority_loop);

    if (err != ESP_OK) {
        return err;
    }

    s_medium_priority_loop = NULL;
    return ESP_OK;
}

fw_err_t fw_event_med_priority_loop_run(TickType_t ticks_to_run)
{
    if (!s_medium_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }
    fw_err_t err;
    
    err = esp_event_loop_run(s_medium_priority_loop, ticks_to_run);

    if (err != ESP_OK) {
        return err;
    }
    return ESP_OK;
}

fw_err_t fw_event_min_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg)
{
    if (s_minimum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_handler_register_with(s_minimum_priority_loop, event_base, event_id,
            event_handler, event_handler_arg);
}

fw_err_t fw_event_min_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler)
{
    if (s_minimum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_handler_unregister_with(s_minimum_priority_loop, event_base, event_id,
            event_handler);
}

fw_err_t fw_event_min_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    if (s_minimum_priority_loop == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_event_post_to(s_minimum_priority_loop, event_base, event_id,
            event_data, event_data_size, ticks_to_wait);
}

fw_err_t fw_event_min_priority_loop_create()
{
    if (s_minimum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_event_loop_args_t min_priority_loop_args = {
        .queue_size = CONFIG_SYSTEM_EVENT_QUEUE_SIZE,
        .task_name = "min_loop",
        .task_stack_size = ESP_TASKD_EVENT_STACK,
        .task_priority = ESP_TASKD_EVENT_PRIO-1,
        .task_core_id = 0
    };
    fw_err_t err;
    err = esp_event_loop_create(&min_priority_loop_args, &s_minimum_priority_loop);
    if (err != ESP_OK) {
        return err;
    }
    return ESP_OK;
}

fw_err_t fw_event_min_priority_loop_delete()
{
    if (!s_minimum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    fw_err_t err;
    
    err = esp_event_loop_delete(s_minimum_priority_loop);

    if (err != ESP_OK) {
        return err;
    }

    s_maximum_priority_loop = NULL;

    return ESP_OK;
}

fw_err_t fw_event_min_priority_loop_run(TickType_t ticks_to_run)
{
    if (!s_minimum_priority_loop) {
        return ESP_ERR_INVALID_STATE;
    }
    fw_err_t err;
    
    err = esp_event_loop_run(s_minimum_priority_loop, ticks_to_run);

    if (err != ESP_OK) {
        return err;
    }
    return ESP_OK;
}