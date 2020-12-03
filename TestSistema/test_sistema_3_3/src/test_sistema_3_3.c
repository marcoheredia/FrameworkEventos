#include "test_sistema_3_3.h"
#include "esp_log.h"
#include "fw_serial.h"
#include "fw_event.h"
#include "fw_defaultevents.h"

void handlerUART(){
	ESP_LOGI("HandlerUART", "Se envió mensaje por UART");
}

void vTask(void * pvParameters){
	struct serial_config *uart_config= (struct serial_config *)pvParameters;
	while(true){
		fw_serial_write( uart_config, "Test",  4);
		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}
}

void test_sistema_3_3_init(){
	struct serial_config *uart_config=malloc(sizeof (struct serial_config *));
	uart_config->serial=FW_UART;
	uart_config->frequency=92000;
	uart_config->uart.port_num=UART_NUM_0;
	uart_config->uart.data_bit=UART_DATA_8_BITS;
	uart_config->uart.stop_bits=UART_STOP_BITS_2;
	uart_config->uart.parity_mode=UART_PARITY_DISABLE;
	ESP_LOGI("", "----------------------------------");
	ESP_LOGI("", "Test de Sistema 3.3: UART");
	ESP_LOGI("", "----------------------------------");
	fw_event_loop_create();
	fw_event_handler_register(FW_EVENT_UARTWRITE, handlerUART, NULL);
	fw_serial_configure(uart_config);
	xTaskCreate(vTask, "tarea", 2048, (void *) uart_config, 5, NULL);
}