/**
 * @brief       main.c
 * @details     This example shows how to work with the internal temperature sensor.
 *
 * 				The temperature data is measured every second and send its value over the UART every 1s.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        05/June/2026
 * @version     05/June/2026    The ORIGIN
 * @pre         This firmware was tested on the ESP32-C3-LCDkit.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - X:       https://x.com/aqueronteblog
 */
#include "board.h"
#include "interrupts.h"
#include "functions.h"


/**@brief Constants.
 */
static const char *TAG = "internal_temperature_sensor";

#define UART1_BAUDRATE	9600
#define UART_BUFFER		(1024*2)

#define NEW_TEMPERATURE_DATA_PERIOD	1000

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
	static uint8_t myMessage[UART_BUFFER];

	temperature_sensor_handle_t temp_handle = NULL;
	float temperature;

    conf_GPIO ();
	conf_UART (UART1_BAUDRATE);
	conf_INTERNAL_TEMPERATURE_SENSOR (&temp_handle);

	/* Show the IDF version	*/
	sprintf((char*)myMessage, "\n[%s], IDF: %s\n", TAG, esp_get_idf_version());
	uart_write_bytes(UART_NUM_1, (const char*)myMessage, strlen((char*)myMessage));
	uart_wait_tx_idle_polling(UART_NUM_1);

	/* Enable temperature sensor	*/
	temperature_sensor_enable(temp_handle);
	
	while (1) {    
		/* Get temperature data		*/
		temperature_sensor_get_celsius(temp_handle, &temperature);

		/* Prepare the message to be sent over the UART	*/
		sprintf((char*)myMessage, "\n[%s], Temperature: %0.2f C\n", TAG, temperature);


		/* Send data over the UART	*/
		uart_write_bytes(UART_NUM_1, (const char*)myMessage, strlen((char*)myMessage));
		uart_wait_tx_idle_polling(UART_NUM_1);

		/* Delay: 1s	*/
		vTaskDelay (NEW_TEMPERATURE_DATA_PERIOD / portTICK_PERIOD_MS);
    }
}
