#include "test_sistema_4_2.h"
#include "esp_log.h"
#include "fw_wifi.h"
#include "fw_ota.h"
#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"

#define WIFI_SSID "WiFi a7v9 2.4GHZ"
#define WIFI_PASS "marco15464527"
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");
const char *url="https://192.168.1.12:8070/hello-world.bin";

void test_sistema_4_2_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 4.2: OTA");
	ESP_LOGI("", "----------------------------------");
	fw_wifi_connect(WIFI_SSID, WIFI_PASS);
	fw_ota_init(url,(char *)server_cert_pem_start);
}