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

#ifndef FW_SERIAL_H_
#define FW_SERIAL_H_
#include "fw_hardware.h"
#include "fw_esp32_i2c.h"
#include "fw_esp32_spi.h"
#include "fw_esp32_uart.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define FW_I2C 7101
#define FW_SPI 7102
#define FW_UART 7103

 struct serial_config{
	int serial;
    int frequency;

	     struct {
	      	i2c_port_t port;
	      	uint16_t slave_addr;
		    i2c_mode_t mode;
		    int gpio_sda;
		    int gpio_scl;
		    bool master;
	    }i2c;
	    struct {
	    	int master_input_pin; 
			int master_output_pin; 
			int clock_pin ;
			int cs_pin;
			spi_device_handle_t handle;  
	    }spi;
	    struct {
	      	uart_port_t port_num;
		    uart_word_length_t data_bit;
		    uart_stop_bits_t stop_bits;
			uart_parity_t parity_mode; 
	    }uart;
  
};


/**
 * @brief configurates the specific serial port
 *
 * @param config Configuration structure with all the parameters to set up the
 * serial communication
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_serial_configure(struct serial_config *config);

/**
 * @brief Read data from a specific serial port
 *
 * @param  config Configuration structure with all the parameters of the serial port
 * @param data_rd pointer to the buffer to store the message
 * @param size maximum value of bytes of the buffer
 *
 * @return number of bytes read of the uart or -1 in case an error occurs
 */
size_t fw_serial_read(struct serial_config *config, void *data_rd, size_t size);

/**
 * @brief Write data to a specific serial port
 *
 * @param  config Configuration structure with all the parameters of the serial port
 * @param data_wr pointer to the buffer to store the message
 * @param size maximum value of bytes of the buffer
 *
 * @return number of bytes read of the uart or -1 in case an error occurs
 */
size_t fw_serial_write(struct serial_config *config, void *data_wr, size_t size);


/**
 * @brief Free or flush the specified serial port
 *
 * @param config Configuration structure with all the parameters of the
 * serial communication
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_serial_free(struct serial_config *config);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_SERIAL_H_
