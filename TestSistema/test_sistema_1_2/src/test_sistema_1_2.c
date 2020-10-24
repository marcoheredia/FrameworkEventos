#include "test_sistema_1_2.h"
#include "fw_event.h"
#include "esp_log.h"

#define EVENTO1 1

void handler1(){
	ESP_LOGI("Handler1", "Atendiendo evento!");
}

void handler2(){
	ESP_LOGI("Handler2", "Atendiendo evento!");
}

void vTask(void * pvParameters){
	while(true){
		ESP_LOGI("Task", "Se produce el evento!");
		fw_event_post(EVENTO1,NULL, 0, portMAX_DELAY);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}

void test_sistema_1_2_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 1.2: Eliminar Handler para un Evento");
	ESP_LOGI("", "----------------------------------");
	fw_event_loop_create();
	fw_event_handler_register(EVENTO1, handler1, NULL);
	fw_event_handler_register(EVENTO1, handler2, NULL);
	ESP_LOGI("init", "Se registraron ambos handler");
	fw_event_handler_unregister(EVENTO1,handler1);
	ESP_LOGI("init", "Se cancelo el registro del primer handler");
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}