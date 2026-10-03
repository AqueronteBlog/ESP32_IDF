/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: ADC.
 *
 * 				It gets a new measurement from the ADC (one-shot configuration) every 0.5s.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        03/September/2026
 * @version     03/September/2026    The ORIGIN
 * @pre         This firmware was tested on the ESP32-C3-LCDkit.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - X:       https://x.com/aqueronteblog
 */
#include "board.h"
#include "interrupts.h"
#include "functions.h"


/**@brief Constants.
 */
static const char *TAG = "adc_simple_one_shot";

#define NEW_DATA_SAMPLE		500
#define ADC_VREF_TYP		1100	// Vref (typ) = 1100mV
#define ADC_BITWIDTH_VALUE	4096	// Bitwidth: 12-bit -> 2^bitwidth = 2^12 = 4096

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
    adc_oneshot_unit_handle_t adc_handle;	// Create ADC unit
	int	adc_raw;
	int	adc_value;

    conf_gpio 	();
	conf_adc	(&adc_handle);

	
	while (1) {  
		/* Take new measurement	*/
        adc_oneshot_read (adc_handle, ADC_CHANNEL_0, &adc_raw);

		/* Show info on the terminal
				Vdata = Vref * data/[2^bitwidth - 1]
					- Vref: 1100mV (typ)	
		*/
		adc_value	=	ADC_VREF_TYP * adc_raw / (ADC_BITWIDTH_VALUE - 1);
		ESP_LOGI(TAG, "\nADC raw: %d\nADC value: %d mV", adc_raw, adc_value);

		/* Delay: 0.5s	*/
		vTaskDelay (NEW_DATA_SAMPLE / portTICK_PERIOD_MS);
    }
}
