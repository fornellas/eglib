#include <eglib.h>
#include <eglib/hal/four_wire_spi/libopencm3_stm32f4.h>
#include <eglib/display/il0373.h>
#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

int main(void) {
	eglib_t eglib;
	four_wire_spi_libopencm3_stm32f4_config_t  four_wire_spi_libopencm3_stm32f4_config = {
		// busy
		.rcc_busy = RCC_GPIOA,
		.port_busy = GPIOA,
		.gpio_busy = GPIO4,
		// cd
		.rcc_dc = RCC_GPIOA,
		.port_dc = GPIOA,
		.gpio_dc = GPIO3,
		// cs
		.rcc_cs = RCC_GPIOA,
		.port_cs = GPIOA,
		.gpio_cs = GPIO2,
		// spi
		.rcc_spi = RCC_SPI1,
		.spi = SPI1,
		// sck
		.rcc_sck = RCC_GPIOA,
		.port_sck = GPIOA,
		.gpio_sck = GPIO5,
		// mosi
		.rcc_mosi = RCC_GPIOA,
		.port_mosi = GPIOA,
		.gpio_mosi = GPIO7,
	};
	il0373_config_t il0373_config = {
		.width = 104,
		.height = 212,
	};

	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	eglib_Init(
		&eglib,
		&four_wire_spi_libopencm3_stm32f4, &four_wire_spi_libopencm3_stm32f4_config,
		&il0373, &il0373_config
	);

	eglib_SetColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib,0, 0, il0373_config.width-1, il0373_config.height-1);

	eglib_SetColor(&eglib, 0, 0, 0, 0);
	eglib_DrawLine(&eglib,0, il0373_config.height-1, il0373_config.width-1, 0);

	while(eglib_Refresh(&eglib));
}