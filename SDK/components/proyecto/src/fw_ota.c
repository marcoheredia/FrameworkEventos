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

/* ---------------------------- Public API ---------------------------------- */

bool fw_ota_init(const char *url,const char *cert_pem)
{
    if(FW_HARDWARE==FWHW_ESP32)
        return fw_esp32_ota_init(url,cert_pem);
    return false;
}