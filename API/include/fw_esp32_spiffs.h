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

#ifndef FW_ESP32_SPIFFS_H_
#define FW_ESP32_SPIFFS_H_
#include <stdbool.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_spiffs.h"
#include "esp_log.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * @brief Creates a file
 *
 * @param filename name of the file to create
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_esp32_spiffs_create(const char *filename);

/**
 * @brief Writes the text of buffer in the file
 *
 * @param filename name of the file to write into
 * @param buffer pointer to the buffer with the message to write
 * @param buffer_length number of bytes from the buffer
 *
 * @return number of bytes writter in the file or -1 in case an error occurs
 */
size_t fw_esp32_spiffs_write(const char *filename, const char *buffer, size_t buffer_length);

/**
 * @brief Reads from the file a specific number of bytes and safe it into a buffer
 * It's important to free the buffer after using it
 *
 * @param filename name of the file to read
 * @param buffer_length maximum number of bytes to read
 *
 * @return char pointer with the text read from the file
 */
char *fw_esp32_spiffs_read(const char *filename, size_t bytes_to_read);

/**
 * @brief Change the name of a file
 *
 * @param filename name of the file to rename
 * @param newfilename the new name for the file
 *
 * @return 
 *  - true in case of success
 *	- false in case an error occurs
 */
bool fw_esp32_spiffs_rename(const char *filename, const char *newfilename);

/**
 * @brief Unregister the stiffs partition
 */
void fw_esp32_spiffs_unregister();


#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_ESP32_SPIFFS_H_
