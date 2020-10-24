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

#ifndef FW_UART_H_
#define FW_UART_H_
#include <stdbool.h>
#include "fw_defaultevents.h"
#include "fw_event.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @brief configurates the uart port
 *
 * @param uart_num port number, possible values: UART_NUM_0, UART_NUM_1, UART_NUM_2
 * @param data_bit word lenght, possible values: UART_DATA_5_BITS, UART_DATA_6_BITS, UART_DATA_7_BITS, UART_DATA_8_BITS
 * @param stop_bits number of stop bits, possible values: UART_STOP_BITS_1, UART_STOP_BITS_1_5, UART_STOP_BITS_2
 * @param parity_mode uart trame parity, possible values: UART_PARITY_DISABLE, UART_PARITY_EVEN, UART_PARITY_ODD
 * @param baudrate number in Hz of baudrate for the uart
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_uart_configure(uart_port_t uart_num, uart_word_length_t data_bit, uart_stop_bits_t stop_bits,
		uart_parity_t parity_mode, uint32_t baudrate);

/**
 * @brief Write data to the UART in a specific port
 *
 * @param uart_num port number, possible values: UART_NUM_0, UART_NUM_1, UART_NUM_2
 * @param buf pointer to the buffer with the message to write
 * @param len maximum value of bytes of the buffer to write
 *
 * @return number of bytes written in the uart or -1 in case an error occurs
 */
size_t fw_uart_write(uart_port_t uart_num, const void *buf, size_t len);

/**
 * @brief Read data from a specific UART port
 *
 * @param uart_num port number, possible values: UART_NUM_0, UART_NUM_1, UART_NUM_2
 * @param buf pointer to the buffer to store the message from UART
 * @param len maximum value of bytes of the buffer
 *
 * @return number of bytes read of the uart or -1 in case an error occurs
 */
size_t fw_uart_read(uart_port_t uart_num, void *buf, size_t len);

/**
 * @brief Flush the UART output buffer
 *
 * @param uart_num port number, possible values: UART_NUM_0, UART_NUM_1, UART_NUM_2
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_uart_flush(uart_port_t uart_num);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_UART_H_
