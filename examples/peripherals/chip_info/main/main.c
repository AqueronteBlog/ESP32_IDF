/**
 * @brief       main.c
 * @details     This example shows how to read the internal info from the MCU.
 *
 * 				The internal info is sent over the UART every 1s.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        08/August/2026
 * @version     08/August/2026    The ORIGIN
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
static const char *TAG = "chip_info";

#define NEW_DATA_PERIOD	1000

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void app_main(void)
{
	esp_chip_info_t chip_info;

    conf_GPIO ();

	/* Get the chip info: chip model, features, revision and cores	*/
	esp_chip_info(&chip_info);
	
	while (1) {    
		/* Show info on the terminal	*/
		ESP_LOGI(TAG, "\nModel: %d\nFeatures: %ld\nRevision: %d\nCores: %d\n", chip_info.model, chip_info.features, chip_info.revision, chip_info.cores);

		/* Delay: 1s	*/
		vTaskDelay (NEW_DATA_PERIOD / portTICK_PERIOD_MS);
    }
}
