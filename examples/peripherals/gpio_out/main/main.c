/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: GPIO as an output.
 *
 * 				One LED changes its state every 250ms.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        04/December/2025
 * @version     04/December/2025    The ORIGIN
 * @pre         This firmware was tested on the ESP32C3-LCDkit.
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
static const char *TAG = "gpio_out";

#define BLINK_LED_PERIOD   250

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
   uint32_t led_state = 0UL;

   conf_GPIO ();

   while (1){
      led_state   =  !led_state;
      gpio_set_level (GPIO_NUM_1, led_state);

      ESP_LOGI (TAG, "LED %s\n", led_state == 0UL ? "OFF" : "ON");

      vTaskDelay (BLINK_LED_PERIOD / portTICK_PERIOD_MS);
   }

}
