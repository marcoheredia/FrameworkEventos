#include "test_sistema_2_4.h"
#include "esp_log.h"
#include "fw_pwm.h"
#include "fw_defaultevents.h"
#include "fw_event.h"

int ciclo_pwm;

void handlerPWM(){
	if(ciclo_pwm>=100)
		ciclo_pwm=0;
	else
		ciclo_pwm=ciclo_pwm+10;
}

void vTask(void * pvParameters){
	bool check;
	while(true){
		check = fw_pwm_set(3, 500, ciclo_pwm);
		if (check==true)
			ESP_LOGI("task", "El porcentaje del ciclo PWM en el pin 3 es: %d",ciclo_pwm);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}

void test_sistema_2_4_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 2.4: PWM");
	ESP_LOGI("", "----------------------------------");
	ciclo_pwm=10;
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_PWM, handlerPWM, NULL);
	ESP_LOGI("init", "Se registro el handler para el evento PWM");
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}