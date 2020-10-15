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

#include "fw_spiffs.h"

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
static void fw_spiffs_register()
{
	if(spiffs_registered==false){
		esp_vfs_spiffs_conf_t conf = {
	      	.base_path = "/spiffs",
	      	.partition_label = NULL,
	      	.max_files = 10,
	      	.format_if_mount_failed = true
	    };
	    esp_err_t err = esp_vfs_spiffs_register(&conf);
	    if (err == ESP_OK){
	    	spiffs_registered=true;
	    }
	}
}

/* ---------------------------- Public API ---------------------------------- */

bool *fw_spiffs_create(const char *filename)
{
	fw_spiffs_register();
	struct stat st;
	if (stat(filename, &st) == 0) {
		//File already exists
		return false;
	}	
	FILE *f = NULL;
	f = fopen(filename ,"a");
	fclose(f);
	return true;
}

size_t fw_spiffs_write(const char *filename, const char *buffer, size_t buffer_length)
{
	fw_spiffs_register();
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

char *fw_spiffs_read(const char *filename, size_t bytes_to_read)
{
    fw_spiffs_register();
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
    return NULL;	
}

bool fw_spiffs_rename(const char *filename, const char *newfilename)
{
	fw_spiffs_register();
	// Check if destination file exists before renaming
	struct stat st;
	if (stat(filename, &st) == 0) {
		return false;
	}
    // Rename original file
    if (rename(newfilename, filename) != 0) {
        return false;
    }
    return true;
}

void fw_spiffs_unregister()
{
	esp_vfs_spiffs_unregister(NULL);	
}
