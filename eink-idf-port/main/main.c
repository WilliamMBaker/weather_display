#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

void spi_task(void *pvParameters)
{
	// SPI communication code here
	while (1)
	{
		// Perform SPI communication
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void start_spi_task()
{
	    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000,           // Clock out at 1 MHz
        .mode = 0,                           // SPI mode 0
        .spics_io_num = PIN_NUM_CS,          // CS pin
        .queue_size = 7,                     // We want to be able to queue 7 transactions at a time
    };

    // Initialize the SPI bus
    esp_err_t ret = spi_bus_initialize(SPI1_HOST, &buscfg, 1);
    assert(ret == ESP_OK);

    // Attach the SPI device
    spi_device_handle_t handle;
    ret = spi_bus_add_device(SPI1_HOST, &devcfg, &handle);
    assert(ret == ESP_OK);

	xTaskCreate(spi_task, "spi_task", 2048, NULL, 5, NULL);
}

void app_main(void)
{
	start_spi_task();
}
