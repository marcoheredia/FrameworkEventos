#include "test_sistema_2_2.h"
#include "fw_defaultevents.h"
#include "fw_adc.h"
#include "fw_event.h"
#include "esp_log.h"

int valor_adc;

void handlerADC(){
	ESP_LOGI("HandlerADC", "El valor medido es %d mV",valor_adc);
}

void vTask(void * pvParameters){
	while(true){
		valor_adc=fw_adc_read_voltage(32);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void test_sistema_2_2_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.2: ADC");
	ESP_LOGI("", "----------------------------------");
	valor_adc=0;
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_ADC, handlerADC, NULL);
	fw_adc_enable(32);
	ESP_LOGI("init", "Se inicializó el ADC en el pin 32.");
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}