#ifndef EGLIB_DISPLAY_4WIRE_SPI_SSD1306_H
#define EGLIB_DISPLAY_4WIRE_SPI_SSD1306_H

#include "../4wire_spi.h"

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;

	// Whether CLS pin is:
	// HIGH (true): internal RC oscillator for CLK
	// LOW (false): CL pin for CLK
	uint8_t rc_oscillator : 1;
	uint8_t rc_oscillator_display_clock_divide_ratio : 4;
	uint8_t rc_oscillator_frequency : 4;

	uint8_t charge_pump_regulator : 1;
} eglib_display_4wire_spi_ssd1306_config_t;

extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_ssd1306;

#endif