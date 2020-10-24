#include "test_sistema_3_3.h"
#include "esp_log.h"
#include "fw_uart.h"
#include "fw_event.h"
#include "fw_defaultevents.h"

void handlerUART(){
	ESP_LOGI("HandlerUART", "Se envió mensaje por UART");
}

void vTask(void * pvParameters){
	while(true){
		fw_uart_write( UART_NUM_0, "Test",  4);
		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}
}

void test_sistema_3_3_init(){
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 3.3: UART");
	ESP_LOGI("", "----------------------------------");
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_UARTWRITE, handlerUART, NULL);
	fw_uart_configure( UART_NUM_0,  UART_DATA_8_BITS,  UART_STOP_BITS_2,  UART_PARITY_DISABLE,  92000);
	xTaskCreate(vTask, "tarea", 2048, NULL, 5, NULL);
}