/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: GPTimer.
 *
 * 				An LED blinks every 0.5s.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        11/July/2026
 * @version     08/July/2026    The ORIGIN
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
static const char *TAG = "gptimer";

#define LED_PIN GPIO_NUM_2  // LED is connected to IO2 pin

/**@brief Variables.
 */



 /**@brief GPTimer callback.
 */
static bool IRAM_ATTR timer_callback (gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    static bool level = false;
    gpio_set_level (LED_PIN, level);
    level   =   !level;

    return false;
}

/**@brief Function for application main entry.
 */
void app_main(void)
{
    conf_GPIO ();

    /* GPTimer config   */
    gptimer_handle_t timer = NULL;
    gptimer_config_t config = {
        .clk_src    =   GPTIMER_CLK_SRC_DEFAULT,
        .direction  =   GPTIMER_COUNT_UP,
        .resolution_hz  =   1*1000000,  // 1MHz -> 1us per tick
        .intr_priority  =   1
    };
    gptimer_new_timer (&config, &timer);

    /* GPTimer: Register callback    */
    gptimer_event_callbacks_t cbs = {
        .on_alarm   =   timer_callback
    };
    gptimer_register_event_callbacks (timer, &cbs, NULL);

    /* GPTimer alarm. 0.5s, auto-reload */
    gptimer_alarm_config_t alarm_cfg = {
        .alarm_count    =   500000, // 5000000us = 0.5s
        .reload_count   =   0,
        .flags.auto_reload_on_alarm =   1
    };
    gptimer_set_alarm_action (timer, &alarm_cfg);

    /* GPTimer enable and start */
    gptimer_enable (timer);
    gptimer_start (timer);

    /* Program controlled by GPTimer    */
    ESP_LOGI (TAG, "GPTimer started, LED blinks every 0.5s");
}
