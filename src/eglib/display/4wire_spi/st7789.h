#ifndef EGLIB_DISPLAY_4WIRE_SPI_ST7789_H
#define EGLIB_DISPLAY_4WIRE_SPI_ST7789_H

#include "../4wire_spi.h"

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;
} eglib_display_4wire_spi_st7789_config_t;

extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_st7789;

#endif