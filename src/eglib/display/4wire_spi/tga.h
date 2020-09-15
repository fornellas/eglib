#ifndef EGLIB_DISPLAY_4WIRE_SPI_TGA_H
#define EGLIB_DISPLAY_4WIRE_SPI_TGA_H

#include "../4wire_spi.h"

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;
} eglib_display_4wire_spi_tga_config_t;

extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_tga;

void eglib_display_4wire_spi_tga_save(eglib_display_4wire_spi_tga_config_t *config, char *path);

#endif