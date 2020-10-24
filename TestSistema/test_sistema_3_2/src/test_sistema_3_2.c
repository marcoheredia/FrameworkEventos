#include "test_sistema_3_2.h"
#include "esp_log.h"
#include "fw_wifi.h"
#include "fw_mqtt.h"
#include "fw_event.h"
#include "fw_defaultevents.h"

#define WIFI_SSID "WiFi a7v9 2.4GHZ"
#define WIFI_PASS ""

int valor;

void handlerMQTT(){
	if(valor>=100)
		valor=10;
	else
		valor=valor+5;
	ESP_LOGI("HandlerMQTT", "Se modifica el valor a %d",valor);
}

void vTask(void * pvParameters){
	esp_mqtt_client_handle_t client=(esp_mqtt_client_handle_t) pvParameters;
	while(true){
		char *texto=malloc(50);
		snprintf(texto, 50, "{'Valor':%d}",valor);
		ESP_LOGI("vTask", "%s",texto);
		fw_mqtt_client_publish(client, "v1/devices/me/telemetry", texto, 0, 1);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		free(texto);
	}
}


void test_sistema_3_2_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 3.2: MQTT");
	ESP_LOGI("", "----------------------------------");
	valor=0;
	fw_wifi_connect(WIFI_SSID, WIFI_PASS);
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_MQTTPUBL, handlerMQTT, NULL);
	
	esp_mqtt_client_handle_t client = fw_mqtt_start_client("mqtt://0dEd5OqN2fuOpxyFOqeG@demo.thingsboard.io");
	xTaskCreate(vTask, "tarea", 2048, (void *) client, 5, NULL);
}