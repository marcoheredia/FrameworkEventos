#include "test_sistema_3_1.h"
#include "esp_log.h"
#include "fw_wifi.h"
#include "fw_defaultevents.h"
#include "fw_event.h"

char *wifi_ssid="ESP32";
char *wifi_pass="TestSistema31";

void handlerWIFI(){
	ESP_LOGI("handlerWIFI", "Se inicializó el AP con SSID: %s y contraseña %s",wifi_ssid,wifi_pass);
}

void test_sistema_3_1_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 3.1: WIFI");
	ESP_LOGI("", "----------------------------------");
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_WIFIAP, handlerWIFI, NULL);
	fw_wifi_setup_ap(wifi_ssid, wifi_pass);
}