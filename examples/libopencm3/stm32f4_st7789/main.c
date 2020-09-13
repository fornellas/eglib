#include <eglib.h>
#include <eglib/hal/libopencm3_stm32f4_spi.h>
#include <eglib/display/st7789.h>
#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

int main(void) {
	eglib_t eglib;
	eglib_hal_libopencm3_stm32f4_spi_config_t  eglib_hal_libopencm3_stm32f4_spi_config = {
		// rst
		.rcc_rst = RCC_GPIOA,
		.port_rst = GPIOA,
		.gpio_rst = GPIO4,
		// cd
		.rcc_cd = RCC_GPIOA,
		.port_cd = GPIOA,
		.gpio_cd = GPIO3,
		// cs
		.rcc_cs = RCC_GPIOA,
		.port_cs = GPIOA,
		.gpio_cs = GPIO2,
		// spi
		.rcc_spi = RCC_SPI1,
		.spi = SPI1,
		.br = SPI_CR1_BAUDRATE_FPCLK_DIV_4,
		.cpol = SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
		.cpha = SPI_CR1_CPHA_CLK_TRANSITION_1,
		.dff = SPI_CR1_DFF_8BIT,
		.lsbfirst  = SPI_CR1_MSBFIRST,
		// sck
		.rcc_sck = RCC_GPIOA,
		.port_sck = GPIOA,
		.gpio_sck = GPIO5,
		// mosi
		.rcc_mosi = RCC_GPIOA,
		.port_mosi = GPIOA,
		.gpio_mosi = GPIO7,
	};
	eglib_display_st7789_config_t eglib_display_st7789_config = {
		.width = 240,
		.height = 240,
	};

	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	eglib_Init(
		&eglib,
		&eglib_hal_libopencm3_stm32f4_spi, &eglib_hal_libopencm3_stm32f4_spi_config,
		&eglib_display_st7789, &eglib_display_st7789_config
	);
	eglib_PowerUp(&eglib);

	eglib_SetColor(&eglib, 0, 0, 0, 255);
	// eglib_SetColor(&eglib, 0, 255, 255, 255);

	eglib_DrawLine(&eglib,0, 0, 239, 239);

}