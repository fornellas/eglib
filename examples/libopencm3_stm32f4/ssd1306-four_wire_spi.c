#include <eglib.h>
#include <eglib/hal/4wire_spi/libopencm3_stm32f4.h>
#include <eglib/display/4wire_spi/ssd1306.h>
#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

int main(void) {
	eglib_t eglib;
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t  hal_config_driver = {
		// rst
		.rcc_rst = RCC_GPIOA,
		.port_rst = GPIOA,
		.gpio_rst = GPIO4,
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
	eglib_display_4wire_spi_ssd1306_config_t display_config = {
		.width = 132,
		.height = 64,
		.rc_oscillator = true,
		.rc_oscillator_display_clock_divide_ratio = 0,
		.rc_oscillator_frequency = 15,
		.charge_pump_regulator = true,
	};

	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	eglib_Init_4wire_spi(
		&eglib,
		&eglib_hal_4wire_spi_libopencm3_stm32f4, &hal_config_driver,
		&eglib_display_4wire_spi_ssd1306, &display_config
	);
	eglib_PowerUp(&eglib);

	eglib_SetColor(&eglib, 0, 0, 255, 255);

	eglib_DrawLine(&eglib,0, 0, 239, 239);
}