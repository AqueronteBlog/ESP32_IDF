/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: UART.
 *
 * 				The state of two LEDs change depends on the command sent over the UART:
 * 					- LED1 state. Serial command: '1'
 * 					- LED2 state. Serial command: '2'
 * 					- Both LEDs off. Another different serial command (LED ERROR!).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        08/April/2026
 * @version     08/April/2026    The ORIGIN
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
static const char *TAG = "uart";

#define UART1_BAUDRATE	9600
#define UART_BUFFER		(1024*2)

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
	uint32_t uart_data_len = 0UL;
	uint32_t led_red_state = 0UL, led_green_state = 0UL; 
	static uint8_t myMessage[UART_BUFFER];
	static uint8_t data[UART_BUFFER];

    conf_GPIO ();
	conf_UART (UART1_BAUDRATE);

	/* Show the IDF version	*/
	sprintf((char*)myMessage, "\n[%s], IDF: %s\n", TAG, esp_get_idf_version());
	uart_write_bytes(UART_NUM_1, (const char*)myMessage, strlen((char*)myMessage));
	uart_wait_tx_idle_polling(UART_NUM_1);

	/* Initialized the message	*/
	myMessage[0]	=	'L';
	myMessage[1]	=	'E';
	myMessage[2]	=	'D';
	myMessage[3]	=	' ';
	myMessage[4]	=	' ';
	myMessage[11]	=	'\n';
	myMessage[12]	=	'\0';

	/* Both LEDs off	*/
	gpio_set_level(GPIO_NUM_0, led_red_state);
	gpio_set_level(GPIO_NUM_7, led_green_state);


	while (1) {    
		/* Wait until there is data in RX buffer	*/
		do{
			uart_get_buffered_data_len(UART_NUM_1, (size_t*)&uart_data_len);
		}while(uart_data_len == 0U);

		if (uart_data_len > 0U)
		{
			/* Initialized the message	*/
			myMessage[5]	=	'T';
			myMessage[6]	=	'O';
			myMessage[7]	=	'G';
			myMessage[8]	=	'G';
			myMessage[9]	=	'L';
			myMessage[10]	=	'E';

			/* Read RX buffer	*/
			uart_data_len = uart_read_bytes(UART_NUM_1, data, 1UL, 0U);

			/* Do the action	*/
			switch (data[0])
			{
				case '1':
					/* Toggle red LED	*/
					led_red_state	=	!led_red_state;
					gpio_set_level(GPIO_NUM_0, led_red_state);
					myMessage[3]	=	'1';
					break;
				
				case '2':
					/* Toggle green LED	*/
					led_green_state	=	!led_green_state;
					gpio_set_level(GPIO_NUM_7, led_green_state);
					myMessage[3]	=	'2';
					break;
				
				default:
					/* Both LEDs off	*/
					led_red_state	=	0UL;
					led_green_state	=	0UL;
					gpio_set_level(GPIO_NUM_0, led_red_state);
					gpio_set_level(GPIO_NUM_7, led_green_state);

					/* Error message	*/
					myMessage[3]	=	' ';
					myMessage[5]	=	'E';
					myMessage[6]	=	'R';
					myMessage[7]	=	'R';
					myMessage[8]	=	'O';
					myMessage[9]	=	'R';
					myMessage[10]	=	'!';
					break;
			}

			/* Write the state of the LEDs	*/
			uart_write_bytes(UART_NUM_1, (const char*)myMessage, strlen((char*)myMessage));
			uart_wait_tx_idle_polling(UART_NUM_1);

			/* Clean the UART1 input buffer	*/
			uart_flush_input(UART_NUM_1);
		}
    }
}
