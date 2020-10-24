#include "test_sistema_2_3.h"
#include "esp_log.h"
#include "fw_defaultevents.h"
#include "fw_dac.h"
#include "fw_event.h"

int valor_dac;

void handlerDAC(){
	if(valor_dac>=3000)
		valor_dac=100;
	else
		valor_dac=valor_dac+500;
	ESP_LOGI("HandlerDAC", "Se modifica el valor DAC a %d mV",valor_dac);
}

void vTask(void * pvParameters){
	while(true){
		fw_dac_output_voltage(25, valor_dac);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}


void test_sistema_2_3_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.3: DAC");
	ESP_LOGI("", "----------------------------------");
	bool check;
	valor_dac=0;
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_DAC, handlerDAC, NULL);
	check = fw_dac_enable(25);
	if (check==true)
		ESP_LOGI("init", "Se inicializó el DAC en el pin 25.");
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}