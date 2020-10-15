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

#ifndef FW_I2C_H_
#define FW_I2C_H_
#include <stdbool.h>
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FW_ACK_CHECK_EN 0x1           /*!< I2C master will check ack from slave*/
#define FW_ACK_CHECK_DIS 0x0          /*!< I2C master will not check ack from slave */
#define FW_ACK_VAL 0x0                /*!< I2C ack value */
#define FW_NACK_VAL 0x1 			  /*!< I2C nack value */

/**
 * @brief Configurate i2c with the parameter:
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 * @param mode the possibles i2c_mode_t values are: I2C_MODE_SLAVE, I2C_MODE_MASTER
 * @param gpio_sda number of pin for serial data
 * @param gpio_scl number of pin for serial clock
 * @param master_freq_Hz integer with the master frequency in Hz
 * @param slave_addr value of the slave address
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_i2c_config(i2c_port_t i2c_port, i2c_mode_t mode, int gpio_sda, int gpio_scl,
					 int master_freq_Hz, uint16_t slave_addr);

/**
 * @brief i2c master reads from a specific port
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 * @param addr value of the address to read from
 * @param data_rd pointer to the buffer to read the value
 * @param size maximum size to be read by the buffer
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_i2c_master_read(i2c_port_t i2c_port, uint16_t addr, uint8_t *data_rd, size_t size);

/**
 * @brief i2c master writes from a specific port
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 * @param addr value of the address to write into
 * @param data_wr pointer to the buffer to write the value
 * @param size maximum size to be written by the buffer
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_i2c_master_write(i2c_port_t i2c_port, uint16_t addr, uint8_t *data_wr, size_t size);

/**
 * @brief i2c slave reads from a specific port
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 * @param data_rd pointer to the buffer to read the value
 * @param size maximum size to be read by the buffer
 *
 * @return value with the number of bytes read or -1 in case of an error occurs
 */
size_t fw_i2c_slave_read(i2c_port_t i2c_port, uint8_t *data_rd, size_t size);

/**
 * @brief i2c slave writes to a specific port
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 * @param data_wr pointer to the buffer to write the value
 * @param size maximum size to be written by the buffer
 *
 * @return value with the number of bytes pushed to the i2c slave buffer or -1
 * if an error occurs
 */
size_t fw_i2c_slave_write(i2c_port_t i2c_port, uint8_t *data_wr, size_t size);

/**
 * @brief Free a specific i2c port
 *
 * @param i2c_port the possibles i2c_port_t values are: I2C_NUM_0, I2C_NUM_1
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs 
 */
bool fw_i2c_free(i2c_port_t i2c_port);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_I2C_H_
