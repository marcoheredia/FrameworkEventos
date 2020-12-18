#include "test_sistema_1_1.h"
#include "fw_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define EVENTO1 1

void handler(){
	ESP_LOGI("Handler", "Atendiendo evento!");
}

void vTask(void * pvParameters){
	while(true){
		ESP_LOGI("Task", "Se produce el evento!");
		fw_event_post(EVENTO1,NULL);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}


void test_sistema_1_1_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 1.1: Registrar Handler para un Evento");
	ESP_LOGI("", "----------------------------------");
	fw_event_handler_register(EVENTO1, handler, NULL);
	ESP_LOGI("init", "Se registro el handler");
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}