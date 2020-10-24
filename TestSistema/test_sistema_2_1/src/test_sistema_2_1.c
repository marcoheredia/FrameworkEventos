#include "test_sistema_2_1.h"
#include "esp_log.h"
#include "fw_gpio.h"


void test_sistema_2_1_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.1: GPIO");
	ESP_LOGI("", "----------------------------------");
	bool check1, check2;
	check1 = fw_gpio_set_pull(1, GPIO_PULLDOWN_ONLY);
	check2 = fw_gpio_setup_output(1, 0);
	if ((check1 == true)&& (check2 == true))
		ESP_LOGI("init", "Se configuro en bajo el pin 1.");
	check1 = fw_gpio_set_pull(2, GPIO_PULLDOWN_ONLY);
	check2 = fw_gpio_setup_output(2, 1);
	if ((check1 == true)&& (check2 == true))
		ESP_LOGI("init", "Se configuro en alto el pin 2.");
}