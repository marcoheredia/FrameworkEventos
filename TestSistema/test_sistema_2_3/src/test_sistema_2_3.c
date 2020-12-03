#include "test_sistema_2_3.h"
#include "esp_log.h"
#include "fw_defaultevents.h"
#include "fw_converter.h"
#include "fw_event.h"

void handlerDAC(void *param){
	converter_config_t *dac_config= (converter_config_t *)param;
	if(dac_config->mv_value>=3000)
		dac_config->mv_value=100;
	else
		dac_config->mv_value=dac_config->mv_value+500;
	ESP_LOGI("HandlerDAC", "Se modifica el valor DAC a %d mV",dac_config->mv_value);
}

void vTask(void * pvParameters){
	converter_config_t *dac_config= (converter_config_t *)pvParameters;
	while(true){
		fw_converter_write(*dac_config);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
	free(dac_config);
}

void test_sistema_2_3_init(){
	
	converter_config_t *dac_config=malloc(sizeof (converter_config_t *));
	dac_config->conversion=FW_DAC;
	dac_config->pin=25;
	dac_config->mv_value=0;
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.3: DAC");
	ESP_LOGI("", "----------------------------------");
	bool check;
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_DAC, handlerDAC, (void *) dac_config);
	check = fw_converter_enable(*dac_config);
	if (check==true){
		ESP_LOGI("init", "Se inicializó el DAC en el pin 25.");
		xTaskCreate(vTask, "tarea", 2048, (void *) dac_config, 5, NULL);
	}
}