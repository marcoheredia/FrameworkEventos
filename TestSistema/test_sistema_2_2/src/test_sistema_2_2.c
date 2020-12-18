#include "test_sistema_2_2.h"
#include "fw_defaultevents.h"
#include "fw_converter.h"
#include "fw_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void handlerADC(void *param){
	converter_config_t *adc_config= (converter_config_t *)param;
	ESP_LOGI("HandlerADC", "El valor medido es %d mV",adc_config->mv_value);
}

void vTask(void * pvParameters){
	converter_config_t *adc_config= (converter_config_t *)pvParameters;
	while(true){
		adc_config->mv_value=fw_converter_read(*adc_config);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	free(adc_config);
}

void test_sistema_2_2_init(){
	converter_config_t *adc_config=malloc(sizeof (converter_config_t *));
	adc_config->conversion=FW_ADC;
	adc_config->pin=32;
	adc_config->mv_value=0;
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.2: ADC");
	ESP_LOGI("", "----------------------------------");
	fw_event_handler_register(FW_EVENT_ADC, handlerADC, (void *) adc_config);
	fw_converter_enable(*adc_config);
	ESP_LOGI("init", "Se inicializó el ADC en el pin 32.");
	xTaskCreate(vTask, "tarea", 2048, (void *) adc_config, 5, NULL);
}