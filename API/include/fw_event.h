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
#ifndef FW_EVENT_H_
#define FW_EVENT_H_
#include "esp_event.h"
#include "fw_error.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @brief Register an event handler with its args in the default event loop
 *
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_handler_register(int32_t event_id, esp_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler in the default event loop
 *
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_handler_unregister(int32_t event_id, esp_event_handler_t event_handler);

/**
 * @brief Posts an event to the default event loop
 *
 * @param event_id id of the event to post
 * @param event_data pointer to a structure to use with the event
 * @param event_data_size size of the event data
 * @param ticks_to_wait Maximum ticks to wait
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_post(int32_t event_id, void* event_data, size_t event_data_size, TickType_t ticks_to_wait);

/**
 * @brief Creates the default event loop, wich is the same as the medium priority event loop
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_loop_create();

/**
 * @brief Delete the default event loop
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_loop_delete();

/**
 * @brief Dispatches events posted to the default loop
 *
 * @param ticks_to_run Maximum ticks to run. Limit the amount of time it runs, returning control to the 
 * caller when that time expires (or some time afterwards)
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_loop_run(TickType_t ticks_to_run);

/**
 * @brief Register an event handler with its args in the loop with maximum priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with maximum priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler);

/**
 * @brief Posts an event to the maximum priority event loop
 *
 * @param event_base base type for the event
 * @param event_id id of the event to post
 * @param event_data pointer to a structure to use with the event
 * @param event_data_size size of the event data
 * @param ticks_to_wait Maximum ticks to wait
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait);

/**
 * @brief Creates the event loop of maximum priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_loop_create();

/**
 * @brief Deletes the event loop of maximum priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_loop_delete();

/**
 * @brief Dispatches events posted to the loop with maximum priority
 *
 * @param ticks_to_run Maximum ticks to run. Limit the amount of time it runs, returning control to the 
 * caller when that time expires (or some time afterwards)
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_max_priority_loop_run(TickType_t ticks_to_run);

/**
 * @brief Register an event handler with its args in the loop with medium priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with medium priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler);

/**
 * @brief Posts an event to the medium priority event loop
 *
 * @param event_base base type for the event
 * @param event_id id of the event to post
 * @param event_data pointer to a structure to use with the event
 * @param event_data_size size of the event data
 * @param ticks_to_wait Maximum ticks to wait
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait);

/**
 * @brief Creates the event loop of medium priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_loop_create();

/**
 * @brief Deletes the event loop of medium priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_loop_delete();

/**
 * @brief Dispatches events posted to the loop with maximum priority
 *
 * @param ticks_to_run Maximum ticks to run. Limit the amount of time it runs, returning control to the 
 * caller when that time expires (or some time afterwards)
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_med_priority_loop_run(TickType_t ticks_to_run);

/**
 * @brief Register an event handler with its args in the loop with minimum priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with minimum priority
 *
 * @param event_base base type for the event
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler);

/**
 * @brief Posts an event to the minimum priority event loop
 *
 * @param event_base base type for the event
 * @param event_id id of the event to post
 * @param event_data pointer to a structure to use with the event
 * @param event_data_size size of the event data
 * @param ticks_to_wait Maximum ticks to wait
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait);

/**
 * @brief Creates the event loop of minimum priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_loop_create();

/**
 * @brief Deletes the event loop of minimum priority
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_loop_delete();

/**
 * @brief Dispatches events posted to the loop with maximum priority
 *
 * @param ticks_to_run Maximum ticks to run. Limit the amount of time it runs, returning control to the 
 * caller when that time expires (or some time afterwards)
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
fw_err_t fw_event_min_priority_loop_run(TickType_t ticks_to_run);



#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_EVENT_H_

