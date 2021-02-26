#include "test_sistema_4_4.h"
#include "fw_timer.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void fw_timer_callback(void* arg){
	ESP_LOGI("timer_callback", "Se termino el timer!");
	fw_timer_delete();
    ESP_LOGI("timer_callback", "Se eliminó el timer");
}

void test_sistema_4_4_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 4.4: Configurar un timer");
	ESP_LOGI("", "----------------------------------");

	fw_timer_set(5000, NULL);
    ESP_LOGI("init", "Se registro el timer");	
}