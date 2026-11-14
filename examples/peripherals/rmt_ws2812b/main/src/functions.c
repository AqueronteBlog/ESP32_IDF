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
 * @brief       void conf_rtm  ( rmt_channel_handle_t* , rmt_encoder_handle_t* )
 * @details     It configures the Remote Control Transceiver (RMT) to control a WS2812B pixel.
 *
 *
 * @param[in]    led_channel: RMT channel
 * @param[in]    led_encoder: RMT encoder
 * 
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/November/2026
 * @version     12/November/2026   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_rtm (rmt_channel_handle_t* led_channel, rmt_encoder_handle_t* led_encoder )
{
    // Configure RMT TX channel
    rmt_tx_channel_config_t tx_config = {
        .gpio_num           = RGB_CTRL,
        .clk_src            = RMT_CLK_SRC_DEFAULT,
        .resolution_hz      = 10000000,  // 10 MHz = 0.1 us per tick
        .mem_block_symbols  = 48,
        .trans_queue_depth  = 1,
    };

    rmt_new_tx_channel(&tx_config, led_channel);

    // WS2812B bit timing
    rmt_bytes_encoder_config_t encoder_config = {
        .bit0 = {
            .duration0  = 4,  // 0.4 us HIGH
            .level0     = 1,
            .duration1  = 8,  // 0.8 us LOW
            .level1     = 0,
        },
        .bit1 = {
            .duration0  = 8,  // 0.8 us HIGH
            .level0     = 1,
            .duration1  = 4,  // 0.4 us LOW
            .level1     = 0,
        },
        .flags.msb_first = 1,
    };

    rmt_new_bytes_encoder(&encoder_config, led_encoder);

    rmt_enable(*led_channel);
}