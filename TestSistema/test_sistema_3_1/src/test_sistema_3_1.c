#include "test_sistema_3_1.h"
#include "esp_log.h"
#include "fw_wifi.h"
#include "fw_defaultevents.h"
#include "fw_event.h"


#define WIFI_SSID "ESP32"
#define WIFI_PASS "TestSistema31"

void handlerWIFI(){
	ESP_LOGI("handlerWIFI", "Se inicializó el AP con SSID: %s y contraseña %s",WIFI_SSID,WIFI_PASS);
}

void test_sistema_3_1_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 3.1: WIFI");
	ESP_LOGI("", "----------------------------------");
	fw_event_handler_register(FW_EVENT_WIFIAP, handlerWIFI, NULL);
	fw_wifi_setup_ap(WIFI_SSID, WIFI_PASS);
}