#include "test_sistema_4_1.h"
#include "esp_log.h"
#include "fw_spiffs.h"
#include <string.h>


void test_sistema_4_1_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 4.1: Manejo de Archivos: SPIFFS");
	ESP_LOGI("", "----------------------------------");
	char *texto=malloc(50);
	texto="Prueba de sistema para manejo de archivos SPIFFS.";
	fw_spiffs_create("/spiffs/prueba.txt");
	fw_spiffs_write("/spiffs/prueba.txt", texto, strlen(texto)+1);
	ESP_LOGI("init", "Se escribió en el archivo");
	bool b=fw_spiffs_rename("/spiffs/prueba.txt", "/spiffs/copia.txt");
	if (b==true)
		ESP_LOGI("init", "Archivo renombrado.");
	char *buf=malloc(50);
	buf=fw_spiffs_read("/spiffs/copia.txt", 50);
	ESP_LOGI("init", "Archivo copia: %s",buf);
	free(buf);
	
}