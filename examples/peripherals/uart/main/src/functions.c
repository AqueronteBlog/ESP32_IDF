/**
 * @brief       functions.c
 * @details     Functions soure file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/April/2022
 * @version     10/April/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "functions.h"


/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIOs.
 *
 * 				- LEDs:
 * 					LED_RED:   IO0
 * 					LED_GREEN: IO7
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/April/2022
 * @version     10/April/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO ( void )
{
    /* Configure LEDs as output signals  */
    gpio_config_t leds_conf = {
        .pin_bit_mask   = ((1ULL << GPIO_NUM_0) | (1ULL << GPIO_NUM_7)),
        .mode           = GPIO_MODE_OUTPUT,
        .pull_up_en     = false,
        .pull_down_en   = false,
        .intr_type      = GPIO_INTR_DISABLE,
    };
    gpio_config(&leds_conf);
}


/**
 * @brief       void conf_UART1  ( uint32_t )
 * @details     It configures UART1.
 *
 *
 * @param[in]    baudrate: UART baudrate.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        08/April/2026
 * @version     08/April/2026   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_UART (uint32_t baudrate)
{
    const uint32_t uart_buffer_size = {1024*2};
    
    /* Configure UART1 */
    uart_config_t uart1_config = {
        .baud_rate  =   baudrate,
        .data_bits  =   UART_DATA_8_BITS,
        .parity     =   UART_PARITY_DISABLE,
        .stop_bits  =   UART_STOP_BITS_1,
        .flow_ctrl  =   UART_HW_FLOWCTRL_DISABLE,
        .source_clk =   UART_SCLK_APB
    };
    uart_param_config(UART_NUM_1, &uart1_config);

    /* Set UART pins: TX: TX1, RX: RX1, RTS: N/A, CTS: N/A  */
    uart_set_pin(UART_NUM_1, U1TXD, U1RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    /* UART1 mode: UART */
    uart_set_mode(UART_NUM_1, UART_MODE_UART);

    /* Install UART driver without an event queue   */
    uart_driver_install(UART_NUM_1, uart_buffer_size, uart_buffer_size, 0, NULL, 0);
}