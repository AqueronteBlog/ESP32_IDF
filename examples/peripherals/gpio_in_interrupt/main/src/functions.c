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
 *              - Switch:
 *                  GPIO9:  KNOB_SW_D (I09)
 *s
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/December/2025
 * @version     20/January/2026    Switch (knob) interrupt was implemented
 *              15/December/2025   Switch (knob) was implemented
 *              04/December/2025   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO (void)
{
    /* Reset the pin    */
    gpio_reset_pin (GPIO_NUM_1);

    /* Set GPIO as an output    */
    gpio_set_direction (GPIO_NUM_1, GPIO_MODE_OUTPUT);

    /* LED off */
    gpio_set_level(GPIO_NUM_1, 0UL);

    /* Reset the pin    */
    gpio_reset_pin (KNOB_SW_D);

    /* Switch: Pull-up mode enabled */
    gpio_set_pull_mode (KNOB_SW_D, GPIO_PULLUP_ONLY);

    /* Set GPIO as an input    */
    gpio_set_direction (KNOB_SW_D, GPIO_MODE_INPUT);

    /* KNOB_SW_D interrupt falling edge type */
    gpio_set_intr_type (KNOB_SW_D, GPIO_INTR_NEGEDGE);

    /* KNOB_SW_D interrupt enabled */
    gpio_intr_enable (KNOB_SW_D);

    /*  Install gpio isr service    */
    gpio_install_isr_service(0);

    /*  Hook isr handler for specific gpio pin  */
    gpio_isr_handler_add(KNOB_SW_D, gpio_isr_handler, (void*) 0);
}