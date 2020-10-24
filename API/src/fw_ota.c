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

/* ------------------------- Static Functions ------------------------------- */

static bool fw_validate_binary(esp_app_desc_t *new_app_info){
    if (new_app_info == NULL) {
        return false;
    }
    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_app_desc_t running_app_info;
    if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK) {
        ESP_LOGI("fw_ota", "Versión actual del firmware: %s", running_app_info.version);
    }

    if (memcmp(new_app_info->version, running_app_info.version, sizeof(new_app_info->version)) == 0) {
        ESP_LOGI("fw_ota", "Firmware actual es igual al nuevo. Se cancela la actualización.");
        return false;
    }
    return true;
}


/* ---------------------------- Public API ---------------------------------- */

bool fw_ota_init(const char *url,const char *cert_pem)
{
    esp_http_client_config_t config = {
        .url = url,
        .cert_pem = cert_pem,
    };
    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };
    esp_https_ota_handle_t https_ota_handle = NULL;
    esp_err_t err = esp_https_ota_begin(&ota_config, &https_ota_handle);
    if (err != ESP_OK) {
        ESP_LOGE("fw_ota", "Fallo en la inicialización de OTA.");
        return false;
    }
    esp_app_desc_t app_desc;
    err = esp_https_ota_get_img_desc(https_ota_handle, &app_desc);
    if (err != ESP_OK) {
        ESP_LOGE("fw_ota", "Fallo con la lectura del binario.");
        return false;
    }
    bool bin=fw_validate_binary(&app_desc);
    if (bin==false)
        return false;

    while (1) {
        err = esp_https_ota_perform(https_ota_handle);
        if (err != ESP_ERR_HTTPS_OTA_IN_PROGRESS) {
            break;
        }
    }
    esp_err_t ota_finish_err = esp_https_ota_finish(https_ota_handle);
    if ((err == ESP_OK) && (ota_finish_err == ESP_OK)) {
        ESP_LOGI("fw_ota", "Actualización OTA exitosa.");
        esp_restart();
        return true;
    } else {
        ESP_LOGE("fw_ota", "Fallo en la actualización OTA.");
    }
    return false;
}