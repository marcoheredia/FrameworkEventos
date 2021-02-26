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

#include "fw_esp32_uart.h"

/* ------------------------- Static Variables ------------------------------- */


/* ------------------------- Static Functions ------------------------------- */


/* ---------------------------- Public API ---------------------------------- */
bool fw_esp32_uart_configure(uart_port_t uart_num, uart_word_length_t data_bit, uart_stop_bits_t stop_bits, uart_parity_t parity_mode, uint32_t baudrate)
{
	if(uart_num<0 || uart_num>2)
		return false;
	if(data_bit<0 || data_bit>4 || stop_bits<0 || stop_bits>4 || parity_mode<0 || parity_mode>3 )
		return false;
	/*const uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = data_bit,
        .parity = parity_mode,
        .stop_bits = stop_bits,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };*/
    esp_err_t ret=uart_driver_install(uart_num, 2048, 0, 0, NULL, 0);
	
    if(ret!=ESP_OK)
    	return false;
    else{
    	return true;
    }
}

size_t fw_esp32_uart_write(uart_port_t uart_num, const void *buf, size_t len)
{
	if(uart_num<0 || uart_num>2 || buf==NULL)
		return -1;
	fw_event_post(FW_EVENT_UARTWRITE, NULL);
	return uart_write_bytes(uart_num, buf, len);
}

size_t fw_esp32_uart_read(uart_port_t uart_num, void *buf, size_t len)
{
	if(uart_num<0 || uart_num>2 || buf==NULL)
		return -1;
	fw_event_post(FW_EVENT_UARTREAD, NULL);
	return uart_read_bytes(uart_num, buf, len, 1/ portTICK_PERIOD_MS);
}

bool fw_esp32_uart_flush(uart_port_t uart_num)
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

