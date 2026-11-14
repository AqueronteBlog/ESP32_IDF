#include "board.h"
#include "interrupts.h"
#include "functions.h"


/**@brief Constants.
 */
static const char *TAG = "rmt_ws2812b";

#define NEW_DATA_SAMPLE		500
#define	ADC_VREF_TYP		1100	//	Vref ~ 1100mV
#define ADC_BITWITDH_VALUE	4096	// Bitwidth: 12-bit -> 2^bitwidth = 2^12 = 4096


/**@brief Variables.
 */


 /**@brief Function prototypes.
 */
void set_pixel(rmt_channel_handle_t, rmt_encoder_handle_t, uint8_t , uint8_t , uint8_t );


/**@brief Function for application main entry.
 */
void app_main(void)
{
	rmt_channel_handle_t led_channel;
	rmt_encoder_handle_t led_encoder;

	conf_gpio 	();
	conf_rtm	(&led_channel, &led_encoder);

	
	while (1) {  
		set_pixel(led_channel, led_encoder, 255, 0, 0);   // Red
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_pixel(led_channel, led_encoder, 0, 255, 0);   // Green
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_pixel(led_channel, led_encoder, 0, 0, 255);   // Blue
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_pixel(led_channel, led_encoder, 255, 255, 255); // White
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_pixel(led_channel, led_encoder, 0, 0, 0);     // OFF
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}



// Send RGB colour to WS2812B
void set_pixel(rmt_channel_handle_t led_channel, rmt_encoder_handle_t led_encoder, uint8_t red, uint8_t green, uint8_t blue)
{
    // WS2812B expects GRB order, not RGB
    uint8_t pixel_data[] = {
        green,
        red,
        blue
    };

    rmt_transmit_config_t tx_config = {
        .loop_count = 0,
    };

    rmt_transmit(
            led_channel,
            led_encoder,
            pixel_data,
            sizeof(pixel_data),
            &tx_config
        );

    rmt_tx_wait_all_done(led_channel, -1);

    // Reset/latch time: keep data line LOW for >50 us
    vTaskDelay(pdMS_TO_TICKS(1));
}
