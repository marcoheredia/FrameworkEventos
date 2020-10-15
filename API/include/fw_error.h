//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FW_ERR_H_
#define FW_ERR_H_

typedef int32_t fw_err_t;

/* Definitions for error constants. */
#define FW_OK          0       /*!< esp_err_t value indicating success (no error) */
#define FW_FAIL        -1      /*!< Generic esp_err_t code indicating failure */

#define FW_ERR_NO_MEM              0x101   /*!< Out of memory */
#define FW_ERR_INVALID_ARG         0x102   /*!< Invalid argument */
#define FW_ERR_INVALID_STATE       0x103   /*!< Invalid state */
#define FW_ERR_INVALID_SIZE        0x104   /*!< Invalid size */
#define FW_ERR_NOT_FOUND           0x105   /*!< Requested resource not found */
#define FW_ERR_NOT_SUPPORTED       0x106   /*!< Operation or feature not supported */
#define FW_ERR_TIMEOUT             0x107   /*!< Operation timed out */
#define FW_ERR_INVALID_RESPONSE    0x108   /*!< Received response was invalid */
#define FW_ERR_INVALID_CRC         0x109   /*!< CRC or checksum was invalid */
#define FW_ERR_INVALID_VERSION     0x10A   /*!< Version was invalid */
#define FW_ERR_INVALID_MAC         0x10B   /*!< MAC address was invalid */

#define FW_ERR_WIFI_BASE           0x3000  /*!< Starting number of WiFi error codes */
#define FW_ERR_MESH_BASE           0x4000  /*!< Starting number of MESH error codes */

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_ERR_H_
