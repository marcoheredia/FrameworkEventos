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

#include "fw_spi.h"

/* ------------------------- Static Variables ------------------------------- */

/* ------------------------- Static Functions ------------------------------- */

/* ---------------------------- Public API ---------------------------------- */

bool fw_spi_initialize(int master_input_pin, int master_output_pin, int spi_clock_pin, int spi_cs_pin, int clk_out_mhz, spi_device_handle_t spi)
{
	if (!GPIO_IS_VALID_GPIO(master_output_pin) || master_output_pin<0 || !GPIO_IS_VALID_GPIO(spi_cs_pin) || spi_cs_pin<0)
        return false;
    if (!GPIO_IS_VALID_OUTPUT_GPIO(master_input_pin) || master_input_pin<0)
        return false;
    if(clk_out_mhz<0 ||clk_out_mhz>1000 || spi==NULL)
    	return false;
    spi_bus_config_t buscfg={
        .miso_io_num=master_input_pin,
        .mosi_io_num=master_output_pin,
        .sclk_io_num=spi_clock_pin,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=0
    };
    esp_err_t ret;
	ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    if(ret!=ESP_OK)
    	return false;

    spi_device_interface_config_t devcfg={
		.clock_speed_hz=clk_out_mhz*1000*1000,
        .mode=0,                                //SPI mode 0
        .spics_io_num=spi_cs_pin,               //CS pin
        .queue_size=7, 
    };
    
    ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    if(ret!=ESP_OK)
    	return false;
    else 
    	return true;
}

bool fw_spi_remove(spi_device_handle_t spi)
{
	if(spi==NULL)
		return false;
	esp_err_t ret;
	ret=spi_bus_remove_device(spi);
	if(ret!=ESP_OK)
    	return false;
	ret=spi_bus_free(1);
	if(ret!=ESP_OK)
    	return false;
    else 
    	return true;
}

/*Sends a message through the SPI device*/
int fw_spi_transmit(spi_device_handle_t spi, const uint8_t *data, int len)
{
	if(spi==NULL)
		return -1;
    esp_err_t ret;
    spi_transaction_t t;
    if (len==0) 
    	return 0;           
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    if(ret==ESP_OK){
        #ifdef FW_DEFAULTEVENTS
            fw_event_post(FW_EVENT_SPITRANSMIT, NULL, 0, portMAX_DELAY);
        #endif // #ifdef FW_DEFAULTEVENTS
    	return len*8;
    }
    else
    	return -1;
}
