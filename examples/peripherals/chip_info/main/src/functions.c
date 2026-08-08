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