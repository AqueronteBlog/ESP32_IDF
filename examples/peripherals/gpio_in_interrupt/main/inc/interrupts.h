/**
 * @brief       interrupts.h
 * @details     Interrupts header file.
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
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void gpio_isr_handler(void* );

/**@brief Constants.
 */


 /**@brief Variables.
 */
extern volatile uint32_t knob_int;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */