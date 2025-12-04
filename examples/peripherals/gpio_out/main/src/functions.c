/**
 * @brief       functions.c
 * @details     Functions soure file.
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
#include "functions.h"

/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIOs.
 *
 * 				- LED:
 * 					GPIO1:  IO1
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
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
void conf_GPIO (void)
{
    /* Reset the pin    */
    gpio_reset_pin (GPIO_NUM_1);

    /* Set GPIO as an output    */
    gpio_set_direction (GPIO_NUM_1, GPIO_MODE_OUTPUT);
}