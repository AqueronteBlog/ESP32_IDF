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


/**
 * @brief       void conf_LEDC  ( uint32_t, uint32_t )
 * @details     It configures LEDC peripheral.
 *
 * 				- LEDs:
 * 					External LED:  IO01
 *
 * @param[in]    ledc_freq: Frequency for LEDC peripheral.
 * @param[in]    ledc_duty: Maximum duty cycle for LEDC peripheral.
 * 
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/March/2026
 * @version     11/March/2026   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_LEDC (uint32_t ledc_freq, uint32_t ledc_duty)
{
    /* Prepare and then apply the LEDC PWM timer configuration  */
    ledc_timer_config_t ledc_timer = {
        .speed_mode         = LEDC_LOW_SPEED_MODE,
        .duty_resolution    = LEDC_TIMER_13_BIT,
        .timer_num          = LEDC_TIMER_0,
        .freq_hz            = ledc_freq,
        .clk_cfg            = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);


    /* Prepare and then apply the LEDC PWM channel configuration    */
    ledc_channel_config_t ledc_channel = {
        .gpio_num   = GPIO_NUM_1,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = ledc_duty,
        .hpoint     = 0
    };
    ledc_channel_config(&ledc_channel);
}