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

#include "fw_uart.h"

/* ------------------------- Static Variables ------------------------------- */


/* ------------------------- Static Functions ------------------------------- */


/* ---------------------------- Public API ---------------------------------- */
bool fw_uart_configure(uart_port_t uart_num, uart_word_length_t data_bit, uart_stop_bits_t stop_bits, uart_parity_t parity_mode, uint32_t baudrate)
{
	if(uart_num<0 || uart_num>2)
		return false;
	if(data_bit<0 || data_bit>4 || stop_bits<0 || stop_bits>4 || parity_mode<0 || parity_mode>3 )
		return false;
	esp_err_t ret;
	ret=uart_set_word_length(uart_num, data_bit);
	if(ret!=ESP_OK)
    	return false;
	ret=uart_set_stop_bits(uart_num, stop_bits);
	if(ret!=ESP_OK)
    	return false;
	ret=uart_set_parity(uart_num, parity_mode);
	if(ret!=ESP_OK)
    	return false;
	ret=uart_set_baudrate(uart_num,baudrate);
	if(ret!=ESP_OK)
    	return false;
    else{
    	return true;
    }
}

size_t fw_uart_write(uart_port_t uart_num, const void *buf, size_t len)
{
	if(uart_num<0 || uart_num>2 || buf==NULL)
		return -1;
	#ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_UARTWRITE, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
	return uart_write_bytes(uart_num, buf, len);
}

size_t fw_uart_read(uart_port_t uart_num, void *buf, size_t len)
{
	if(uart_num<0 || uart_num>2 || buf==NULL)
		return -1;
	#ifdef FW_DEFAULTEVENTS
        fw_event_post(FW_EVENT_UARTREAD, NULL, 0, portMAX_DELAY);
    #endif // #ifdef FW_DEFAULTEVENTS
	return uart_read_bytes(uart_num, buf, len, 1/ portTICK_PERIOD_MS);
}

bool fw_uart_flush(uart_port_t uart_num)
{
	if(uart_num<0 || uart_num>2)
		return false;
	esp_err_t ret;
	ret=uart_flush(uart_num);
	if(ret!=ESP_OK)
    	return false;
    else{
    	return true;
    }
}

