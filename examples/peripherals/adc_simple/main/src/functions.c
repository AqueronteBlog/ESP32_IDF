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
 * @brief       void conf_gpio  ( void )
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
void conf_gpio ( void )
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
 * @brief       void conf_adc  ( void )
 * @details     It configures ADC.
 *
 * 				- ADC1:
 * 					ADC Channel:        GPIO0 (ADC channel 0)
 * 					ADC attenuation:    12dB
 *                  ADC bitwidth:       12-bit
 *                  ADC mode:           One-shot mode
 *
 *
 * @param[in]    adc_handle:    ADC one-shot handle.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/October/2026
 * @version     03/October/2026   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_adc ( adc_oneshot_unit_handle_t* adc_handle )
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_config, adc_handle);

    /* Configure ADC channel    */
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_oneshot_config_channel(*adc_handle, ADC_CHANNEL_0, &config); // ESP32-C3 ADC1 channel 0 = GPIO0
}