/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: GPIO as an input using interrupts.
 *
 * 				      One LED changes its state every time we push the button (interrupt mode).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        22/January/2026
 * @version     22/January/2026    The ORIGIN
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
static const char *TAG = "gpio_in_interrupt";

#define KNOB_ANTIBOUNCING   200


/**@brief Variables.
 */
volatile uint32_t knob_int;

/**@brief Function for application main entry.
 */
void app_main(void)
{
  uint32_t led_state = 0UL;

  conf_GPIO ();

  knob_int = 0UL;


  while (1) {
    /* Wait until the knob is pushed  */
    if (knob_int == 1UL)
    {
      vTaskDelay(KNOB_ANTIBOUNCING / portTICK_PERIOD_MS); // Anti-bouncing delay

      led_state = !led_state;


      gpio_set_level(GPIO_NUM_1, led_state);

      knob_int = 0UL;
         
      ESP_LOGI(TAG, "LED %s\n", led_state == 1UL ? "ON" : "OFF");
    }
  }
}