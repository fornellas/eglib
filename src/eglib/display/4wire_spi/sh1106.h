#ifndef EGLIB_DISPLAY_4WIRE_SPI_SH1106_H
#define EGLIB_DISPLAY_4WIRE_SPI_SH1106_H

#include "../4wire_spi.h"

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;
} eglib_display_4wire_spi_sh1106_config_t;

// VDD1 = 1.65 - 3.5V, TA= +25°C
extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_1_65;
// VDD1 = 2.4 - 3.5V, TA= +25°C
extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_2_4;

#endif