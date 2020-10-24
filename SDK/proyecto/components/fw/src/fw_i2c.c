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

#include "fw_i2c.h"

/* ------------------------- Static Variables ------------------------------- */


/* ------------------------- Static Functions ------------------------------- */


/* ---------------------------- Public API ---------------------------------- */
bool fw_i2c_config(i2c_port_t i2c_port, i2c_mode_t mode, int gpio_sda, int gpio_scl, int master_freq_Hz, uint16_t slave_addr)
{
    if(i2c_port<0|| i2c_port>1 || mode<0 || mode>2 || master_freq_Hz<0)
    	return false;
    if (!GPIO_IS_VALID_GPIO(gpio_sda) || gpio_sda<0 || !GPIO_IS_VALID_GPIO(gpio_scl) || gpio_scl<0)
        return false;
    esp_err_t ret;
    i2c_config_t conf;
    if(mode==I2C_MODE_MASTER)
    {
    	conf.mode = I2C_MODE_MASTER;
	    conf.sda_io_num = gpio_sda;
	    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	    conf.scl_io_num = gpio_scl;
	    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	    conf.master.clk_speed = master_freq_Hz;
	    ret=i2c_param_config(i2c_port, &conf);
	    if(ret!=ESP_OK)
	    	return false;
	    ret=i2c_driver_install(i2c_port, conf.mode, 0, 0, 0);
	    if(ret!=ESP_OK)
	    	return false;
	    return true;
    }
    else if(mode==I2C_MODE_SLAVE)
    {
    	conf.sda_io_num = gpio_sda;
	    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	    conf.scl_io_num = gpio_scl;
	    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	    conf.mode = I2C_MODE_SLAVE;
	    conf.slave.addr_10bit_en = 0;
	    conf.slave.slave_addr = slave_addr;
	    ret=i2c_param_config(i2c_port, &conf);
	    if(ret!=ESP_OK)
	    	return false;
	    ret=i2c_driver_install(i2c_port, conf.mode, 1024, 1024, 0); //default buffer length for slave tx & rx 1024
	    if(ret!=ESP_OK)
	    	return false;
	    return true;
    }
    else
    	return false;
}

bool fw_i2c_master_read(i2c_port_t i2c_port, uint16_t addr, uint8_t *data_rd, size_t size)
{
	if(i2c_port<0|| i2c_port>2 || data_rd==NULL || size<1)
    	return false;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_READ, FW_ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, FW_ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, FW_NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if(ret!=ESP_OK)
	    return false;
	else{
		fw_event_post(FW_EVENT_I2CMASTERREAD, NULL, 0, portMAX_DELAY);
		return true;
	}
}

bool fw_i2c_master_write(i2c_port_t i2c_port, uint16_t addr, uint8_t *data_wr, size_t size)
{
	if(i2c_port<0|| i2c_port>2 || data_wr==NULL || size<1)
    	return false;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, FW_ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, FW_ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if(ret!=ESP_OK)
	    return false;
	else {
		fw_event_post(FW_EVENT_I2CMASTERWRITE, NULL, 0, portMAX_DELAY);
		return true;
	}
}

size_t fw_i2c_slave_read(i2c_port_t i2c_port, uint8_t *data_rd, size_t size)
{
	if(i2c_port<0|| i2c_port>2 || data_rd==NULL || size<1)
    	return -1;
    fw_event_post(FW_EVENT_I2CSLAVEREAD, NULL, 0, portMAX_DELAY);
	return i2c_slave_read_buffer(i2c_port, data_rd, size, 1000 / portTICK_RATE_MS);
}

size_t fw_i2c_slave_write(i2c_port_t i2c_port, uint8_t *data_wr, size_t size)
{
	if(i2c_port<0|| i2c_port>2 || data_wr==NULL || size<1)
    	return -1;
    fw_event_post(FW_EVENT_I2CSLAVEWRITE, NULL, 0, portMAX_DELAY);
	return i2c_slave_write_buffer(i2c_port, data_wr, size, 1000 / portTICK_RATE_MS);
}

bool fw_i2c_free(i2c_port_t i2c_port)
{
	if(i2c_port<0|| i2c_port>2)
    	return false;
	esp_err_t ret = i2c_driver_delete(i2c_port);
	if(ret!=ESP_OK)
	    return false;
	else 
		return true;
}
