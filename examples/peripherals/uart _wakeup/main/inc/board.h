/**
 * @brief       board.h
 * @details     It defines the board ( for this example ): ESP32_C3_LCDKIT_BOAR.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/December/2025
 * @version     04/December/2025   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "sdkconfig.h"

#ifndef ESP32_C3_LCDKIT_BOARD_H_
#define ESP32_C3_LCDKIT_BOARD_H_


#ifdef __cplusplus
extern "C" {
#endif

/**@brief UART1.
 */
typedef enum{
  U1RXD  = GPIO_NUM_20,		    /*!<   RXD0: IO20        */
  U1TXD  = GPIO_NUM_21		    /*!<   TXD0: IO21        */
} esp32_c3_lcdkit_board_uart1_t;


#ifdef __cplusplus
}
#endif

#endif /* ESP32_C3_LCDKIT_BOARD_H_ */