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

#include "fw_serial.h"

/* ------------------------- Static Variables ------------------------------- */


/* ------------------------- Static Functions ------------------------------- */


/* ---------------------------- Public API ---------------------------------- */
bool fw_serial_configure(struct serial_config *config)
{
    if(FW_HARDWARE==FWHW_ESP32){
        if(config->serial==FW_I2C)
            return fw_esp32_i2c_config(config->i2c.port, config->i2c.mode, config->i2c.gpio_sda, config->i2c.gpio_scl, config->frequency, config->i2c.slave_addr);
        if(config->serial==FW_SPI)
            return fw_esp32_spi_initialize(config->spi.master_input_pin, config->spi.master_output_pin, config->spi.clock_pin, config->spi.cs_pin, config->frequency, config->spi.handle);
        if(config->serial==FW_UART)
            return fw_esp32_uart_configure(config->uart.port_num, config->uart.data_bit, config->uart.stop_bits, config->uart.parity_mode, config->frequency);
    }
    return false;
}

size_t fw_serial_read(struct serial_config *config, void *data_rd, size_t size)
{
	if(FW_HARDWARE==FWHW_ESP32){
        if(config->serial==FW_I2C){
            if(config->i2c.master==true)
            	return fw_esp32_i2c_master_read(config->i2c.port, config->i2c.slave_addr, data_rd, size);
            else
            	fw_esp32_i2c_slave_read(config->i2c.port, data_rd, size);
        }
        if(config->serial==FW_UART)
            return fw_esp32_uart_read(config->uart.port_num, data_rd, size);
    }
    return -1;
}

size_t fw_serial_write(struct serial_config *config, void *data_wr, size_t size)
{
	if(FW_HARDWARE==FWHW_ESP32){
        if(config->serial==FW_I2C){
        	if(config->i2c.master==true)
            	return fw_esp32_i2c_master_write(config->i2c.port, config->i2c.slave_addr,  data_wr, size);
            else
            	return fw_esp32_i2c_slave_write(config->i2c.port, data_wr,  size);
        }
        if(config->serial==FW_SPI)
            return fw_esp32_spi_transmit(config->spi.handle, data_wr, size);
        if(config->serial==FW_UART)
            return fw_esp32_uart_write(config->uart.port_num, data_wr, size);
    }
    return -1;
}

bool fw_serial_free(struct serial_config *config)
{
	if(FW_HARDWARE==FWHW_ESP32){
        if(config->serial==FW_I2C)
            return fw_esp32_i2c_free(config->i2c.port);
        if(config->serial==FW_SPI)
            return fw_esp32_spi_remove(config->spi.handle);
        if(config->serial==FW_UART)
            return fw_esp32_uart_flush(config->uart.port_num);
    }
    return false;
}
