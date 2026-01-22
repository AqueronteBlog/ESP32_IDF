/**
 * @brief       interrupts.c
 * @details     Interrupts soure file.
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
#include "interrupts.h"

/**
 * @brief       gpio_isr_handler  ( void* )
 * @details     GPIO ISR handler.
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
 * @date        20/January/2026
 * @version     20/January/2026     The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void gpio_isr_handler(void* arg)
{
    knob_int = 1UL;
}