/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: LEDC.
 *
 * 				An external LED is brightening up and down by LEDC peripheral.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        11/March/2026
 * @version     11/March/2026    The ORIGIN
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
static const char *TAG = "ledc";

#define LED_PERIOD      15UL
#define LEDC_FREQUENCY  5000UL   // Frequency in Hertz. Set frequency at 5khz
#define LEDC_DUTY       4095UL   // Set duty cycle to 50%. ((2^13) - 1)*50% = 4095. NOTE: 13-bit duty resolution

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
    uint32_t i = 0UL;

    conf_GPIO ();
    conf_LEDC (LEDC_FREQUENCY, LEDC_DUTY);

    while (1) {   
       /* LED brightness up   */  
       ESP_LOGI (TAG, "LED brightness up");   
       for (i = 0UL; i < LEDC_DUTY; i+= 30UL)
       {
         /* Set new duty cycle   */
         ledc_set_duty (LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);

         /* Update duty to apply the new value  */
         ledc_update_duty (LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

         vTaskDelay (LED_PERIOD/portTICK_PERIOD_MS);
       }

       /* LED brightness down   */     
       ESP_LOGI (TAG, "LED brightness down");
       for (i = LEDC_DUTY; i > 20UL; i-= 20UL)
       {
         /* Set new duty cycle   */
         ledc_set_duty (LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);

         /* Update duty to apply the new value  */
         ledc_update_duty (LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

         vTaskDelay (LED_PERIOD/portTICK_PERIOD_MS);
       }
    }
}
