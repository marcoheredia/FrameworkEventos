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
#ifndef FW_GPIO_H_
#define FW_GPIO_H_
#include <stdbool.h>
#include "driver/gpio.h"
#include "fw_error.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @brief Set mode for a specific GPIO pin, 
 *
 * @param pin integer representing the GPIO pin
 * @param mode the gpio_mode_t options are: GPIO_MODE_DISABLE, GPIO_MODE_INPUT, GPIO_MODE_OUTPUT
 * GPIO_MODE_OUTPUT_OD, GPIO_MODE_INPUT_OUTPUT_OD, GPIO_MODE_INPUT_OUTPUT 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_set_mode(int pin, gpio_mode_t mode);

/**
 * @brief Sets pull-up or pull-down type for a specific GPIO pin
 *
 * @param pin integer representing the GPIO pin
 * @param pull the gpio_pull_mode_t options are: GPIO_PULLUP_ONLY, GPIO_PULLDOWN_ONLY,
 * GPIO_PULLUP_PULLDOWN, GPIO_FLOATING 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_set_pull(int pin, gpio_pull_mode_t pull);

/**
 * @brief Sets up a pin as an input and configures pull-up or pull-down.
 *
 * @param pin integer representing the GPIO pin
 * @param pull the gpio_pull_mode_t options are: GPIO_PULLUP_ONLY, GPIO_PULLDOWN_ONLY,
 * GPIO_PULLUP_PULLDOWN, GPIO_FLOATING
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_setup_input(int pin, gpio_pull_mode_t pull);

/**
 * @brief Sets up pin output while avoiding spurious transitions:
 * desired output level is configured first, then mode.
 *
 * @param pin integer representing the GPIO pin
 * @param level the output level should be 0 or 1
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_setup_output(int pin, int8_t level);

/**
 * @brief Read a specific pin input level
 *
 * @param pin integer representing the GPIO pin
 *
 * @return the value of the pin level (0 or 1)
 */
int8_t fw_gpio_read(int pin);

/**
 * @brief Set pin's output level.
 *
 * @param pin integer representing the GPIO pin 
 * @param level value to write on the pin (0 or 1) 
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_write(int pin, int8_t level);

/**
 * @brief Flip output pin value.
 *
 * @param pin integer representing the GPIO pin
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_toggle(int pin);

/**
 * @brief Reset an gpio to default state (select gpio function,
 * enable pullup and disable input and output).
 *
 * @param pin integer representing the GPIO pin
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_reset(int pin);

/**
 * @brief Enable interrupt on a specified pin
 *
 * @param pin integer representing the GPIO pin
 * @param intr_type type of interruption, possible values are:
 *   GPIO_INTR_DISABLE = 0     Disable GPIO interrupt
 *   GPIO_INTR_POSEDGE = 1     GPIO interrupt type : rising edge
 *   GPIO_INTR_NEGEDGE = 2     GPIO interrupt type : falling edge
 *   GPIO_INTR_ANYEDGE = 3     GPIO interrupt type : both rising and falling edge 
 *   GPIO_INTR_LOW_LEVEL = 4   GPIO interrupt type : input low level trigger
 *   GPIO_INTR_HIGH_LEVEL = 5  GPIO interrupt type : input high level trigger
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_enable_int(int pin, gpio_int_type_t intr_type);

/**
 * @brief Disables interrupt (without removing the handler).
 *
 * @param pin integer representing the GPIO pin
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_gpio_disable_int(int pin);

/**
 * @brief invokes handler in ISR context, without the overhead of a context switch. 
 * GPIO interrupts are disabled while the handler is running.
 *
 * @param pin integer representing the GPIO pin
 * @param isr_handler handler for the interruption
 * @param args pointer to the arguments of the handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_set_int_handler(int pin, gpio_isr_t isr_handler, void *args);

/**
 * @brief Removes a previosuly set interrupt handler.If cb and arg are not NULL, 
 * they will contain previous handler and arg.
 *
 * @param pin integer representing the GPIO pin
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_gpio_remove_int_handler(int pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_GPIO_H_

