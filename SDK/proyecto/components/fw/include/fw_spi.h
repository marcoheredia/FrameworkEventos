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

#ifndef FW_SPI_H_
#define FW_SPI_H_
#include <stdbool.h>
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the SPI with the configuration past in parameters
 *
 * @param master_input_pin pin for SPI master input
 * @param master_output_pin pin for SPI master output
 * @param spi_clock_pin pin for SPI clock
 * @param spi_cs_pin pin for SPI chip select
 * @param clk_out_mhz value in MHz for the clock output
 * @param spi pointer to the SPI device handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_spi_initialize(int master_input_pin, int master_output_pin, int spi_clock_pin, 
	int spi_cs_pin, int clk_out_mhz, spi_device_handle_t spi);

/**
 * @brief Close SPI handle
 *
 * @param spi pointer to the SPI device handler
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_spi_remove(spi_device_handle_t spi);

/**
 * @brief 
 *
 * @param spi pointer to the SPI device handler 
 * @param data buffer with the data to transmit
 * @param len length of bytes to transmit
 *
 * @return number of bytes transmited or -1 in case an error occurs
 */
int fw_spi_transmit(spi_device_handle_t spi, const uint8_t *data, int len);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_SPI_H_




