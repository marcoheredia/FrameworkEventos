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

#include "fw_ota.h"

/* ------------------------- Static Variables ------------------------------- */

static char ota_write_data[BUFFSIZE + 1] = { 0 };

/* ------------------------- Static Functions ------------------------------- */


static void http_cleanup(esp_http_client_handle_t client)
{
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}

/* ---------------------------- Public API ---------------------------------- */

bool fw_ota_init(const char *url,const char *cert_pem)
{
	esp_err_t err;
    /* update handle : set by esp_ota_begin(), must be freed via esp_ota_end() */
    esp_ota_handle_t update_handle = 0 ;
    const esp_partition_t *update_partition = NULL;
    const esp_partition_t *configured_partition = esp_ota_get_boot_partition();
    const esp_partition_t *running_partition = esp_ota_get_running_partition();
    if (configured_partition != running_partition) {
        //This can happen if either the OTA boot data or preferred boot image become corrupted somehow.
        return false;
    }
	esp_http_client_config_t config = {
        .url = url,
        .cert_pem = cert_pem,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        return false;
    }
    err = esp_http_client_open(client, 0);
    if (err != ESP_OK) {
        return false;
    }
    esp_http_client_fetch_headers(client);
    update_partition = esp_ota_get_next_update_partition(NULL);
    assert(update_partition != NULL);
    err = esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &update_handle);
    if (err != ESP_OK) {
        http_cleanup(client);
        return false;
    }
    //esp_ota_begin succeeded.
    int binary_file_length = 0;
    /*deal with all receive packet*/
    while (1) {
        int data_read = esp_http_client_read(client, ota_write_data, BUFFSIZE);
        if (data_read < 0) {
            //SSL data read error
            http_cleanup(client);
            return false;
        } else if (data_read > 0) {
            err = esp_ota_write( update_handle, (const void *)ota_write_data, data_read);
            if (err != ESP_OK) {
                http_cleanup(client);
                return false;
            }
            binary_file_length += data_read;
        } else if (data_read == 0) {
            //All data received
            break;
        }
    }
    if (esp_ota_end(update_handle) != ESP_OK) {
        //esp_ota_end failed
        http_cleanup(client);
        return false;
    }
    if (esp_partition_check_identity(esp_ota_get_running_partition(), update_partition) == true) {
        //The current running firmware is same as the firmware just downloaded");
        return false;
    }
    err = esp_ota_set_boot_partition(update_partition);
    if (err != ESP_OK) {
        //esp_ota_set_boot_partition failed
        http_cleanup(client);
        return false;
    }
    //Prepare to restart system
	esp_restart();
    return true;
}