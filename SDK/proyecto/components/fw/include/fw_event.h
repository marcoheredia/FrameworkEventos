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
#include <sys/queue.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef   void (*fw_event_handler_t)(void *args,void *event_args);

 struct fw_event_handler{
  int ev;
  fw_event_handler_t handler;
  void *handler_args;
  SLIST_ENTRY(fw_event_handler) next;
};



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
bool fw_event_handler_register(int event_id, fw_event_handler_t event_handler, 
                                void* event_handler_arg);

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
bool fw_event_handler_unregister(int event_id, fw_event_handler_t event_handler);

/**
 * @brief Posts an event to the default event loop
 *
 * @param event_id id of the event to post
 * @param event_args null pointer to be used for arguments
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_post(int event_id, void* event_args);

/**
 * @brief Register an event handler with its args in the loop with maximum priority
 *
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_max_priority_handler_register(int event_id,
                fw_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with maximum priority
 *
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_max_priority_handler_unregister(int event_id,
        fw_event_handler_t event_handler);


/**
 * @brief Register an event handler with its args in the loop with medium priority
 *
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_med_priority_handler_register(int event_id,
                fw_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with medium priority
 *
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_med_priority_handler_unregister(int event_id,
        fw_event_handler_t event_handler);

/**
 * @brief Register an event handler with its args in the loop with minimum priority
 *
 * @param event_id id of the event to which the handler will be registered
 * @param event_handler handler to execute when the event occurs
 * @param event_handler_arg pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_min_priority_handler_register(int event_id,
                fw_event_handler_t event_handler, void* event_handler_arg);

/**
 * @brief Unregister an event handler from loop with minimum priority
 *
 * @param event_id id of the event to which the handler will be unregistered
 * @param event_handler handler to be unregistered
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_event_min_priority_handler_unregister(int event_id,
        fw_event_handler_t event_handler);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_EVENT_H_

