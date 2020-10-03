#include <eglib.h>
#include <eglib/hal/4wire_spi/libopencm3_stm32f4.h>
#include <eglib/display/4wire_spi/frame_buffer.h>
#include <eglib/display/4wire_spi/sh1106.h>
#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

int main(void) {
	eglib_t eglib_sh1106;
	eglib_display_4wire_spi_sh1106_config_t sh1106_config = {
		// Display physical construction
		.width = 128,
		.height = 64,
		.segment_remap = SH1106_SEGMENT_REMAP_REVERSE,
		.common_pads_hardware_configuration_mode = SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_ALTERNATIVE,
		.common_output_scan_direction = SH1106_COMMON_OUTPUT_SCAN_DIRECTION_DESC,
		.display_offset = 4,
		.column_offset = 2,

		// Change period
		.pre_charge_period = 2,
		.dis_charge_period = 2,

		// VCOM deselect
		.vcom_deselect_level = 0x35,

		// Internal display clocks
		.clock_divide = 0,
		.oscillator_frequency = SH1106_OSCILLATOR_FREQUENCY_PLUS_50_PCT,

		// Charge Pump Regulator
		.dc_dc_enable = true,
		.dc_dc_voltage = SHH1106_DC_DC_8_0_V,
	};

	eglib_t eglib;
	eglib_display_4wire_spi_t frame_buffer;
	eglib_display_4wire_spi_frame_buffer_config_t frame_buffer_config;

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

	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	eglib_Init_4WireSPI(
		&eglib_sh1106,
		&eglib_hal_4wire_spi_libopencm3_stm32f4, &hal_config_driver,
		&eglib_display_4wire_spi_sh1106_vdd1_2_4_v, &sh1106_config
	);

	eglib_4WireSPI_FrameBuffer_Init(
		&eglib,
		&frame_buffer, &frame_buffer_config,
		&eglib_sh1106
	);

	eglib_SetColor(&eglib, 0, 0xFF, 0xFF, 0xFF);

	eglib_DrawLine(&eglib,0, 0, sh1106_config.width-1, sh1106_config.height-1);
	eglib_DrawLine(&eglib,0, sh1106_config.height-1, sh1106_config.width-1, 0);

	eglib_4WireSPI_FrameBuffer_Send(&eglib, 0, 0, sh1106_config.width-1, sh1106_config.height-1);
}