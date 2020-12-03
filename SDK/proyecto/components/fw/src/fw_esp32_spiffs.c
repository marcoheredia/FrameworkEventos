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

#include "fw_esp32_spiffs.h"

/* ------------------------- Static Variables ------------------------------- */
static bool spiffs_registered=false;

/* ------------------------- Static Functions ------------------------------- */

/*Returns the size of the file*/
static size_t fw_file_size(const char* filename)
{
    size_t size=0;
    FILE* fp = fopen(filename, "r");
    if(fp){
        rewind(fp);
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);
        fclose(fp);
        return size;
    }
    else{
        return -1;
    }

}

/* Register the spiffs partition */
static void fw_esp32_spiffs_register()
{
	if(spiffs_registered==false){
	    ESP_LOGI("fw_spiffs", "Initializing SPIFFS");
	    esp_vfs_spiffs_conf_t conf = {
	      .base_path = "/spiffs",
	      .partition_label = NULL,
	      .max_files = 5,
	      .format_if_mount_failed = true
	    };

	    esp_err_t err = esp_vfs_spiffs_register(&conf);

	    if (err != ESP_OK) {
	        if (err == ESP_FAIL) {
	            ESP_LOGE("fw_spiffs", "Failed to mount or format filesystem");
	        } else if (err == ESP_ERR_NOT_FOUND) {
	            ESP_LOGE("fw_spiffs", "Failed to find SPIFFS partition");
	        } else {
	            ESP_LOGE("fw_spiffs", "Failed to initialize SPIFFS (%s)", esp_err_to_name(err));
	        }
	        return;
	    }
	    else
	    	spiffs_registered=true;
	    
	    size_t total = 0, used = 0;
	    err = esp_spiffs_info(NULL, &total, &used);
	    if (err != ESP_OK) {
	        ESP_LOGE("fw_spiffs", "Failed to get SPIFFS partition information (%s)", esp_err_to_name(err));
	    } else {
	        ESP_LOGI("fw_spiffs", "Partition size: total: %d, used: %d", total, used);
	    }
	}
}

/* ---------------------------- Public API ---------------------------------- */

bool fw_esp32_spiffs_create(const char *filename)
{
	fw_esp32_spiffs_register();
	struct stat st;
	if (stat(filename, &st) == 0) {
		//File already exists
		unlink(filename);
	}	
	FILE *f = NULL;
	f = fopen(filename ,"x");
	fclose(f);
	ESP_LOGI("fw_spiffs", "Fin create");
	return true;
}

size_t fw_esp32_spiffs_write(const char *filename, const char *buffer, size_t buffer_length)
{
	fw_esp32_spiffs_register();
    if (spiffs_registered==true) {
	    FILE* fd = fopen(filename, "w");
	    if (fd == NULL) {
	        return 0;
	    }
	    size_t bytes_written=fwrite(buffer, buffer_length, sizeof(char *), fd);
	    fclose(fd);
	    return bytes_written;
	}
	return 0;
}

char *fw_esp32_spiffs_read(const char *filename, size_t bytes_to_read)
{
    fw_esp32_spiffs_register();
    FILE* fd;
    fd = fopen(filename, "r");
    if (fd == NULL) {
        return NULL;
    }
    char* buffer = NULL;
    size_t buffer_length=fw_file_size(filename);
    if(bytes_to_read>0)
    	buffer_length=  buffer_length > bytes_to_read ? bytes_to_read:buffer_length; 
    if((buffer=(char *) malloc(buffer_length))){
		fgets(buffer, buffer_length, fd);
    	if(buffer==NULL){
    		fclose(fd);
    		return NULL;
    	}
    	fclose(fd);
    	return buffer;
    }
    fclose(fd);
    free(buffer);
    return NULL;	
}

bool fw_esp32_spiffs_rename(const char *filename, const char *newfilename)
{
	// Check if destination file exists before renaming
	struct stat st;
	if (stat(newfilename, &st) == 0) {
		unlink(newfilename);
	}
    // Rename original file
    if (rename(filename, newfilename) != 0) {
        return false;
    }
    return true;
}

void fw_esp32_spiffs_unregister()
{
	esp_vfs_spiffs_unregister(NULL);	
}
