#ifndef EGLIB_DISPLAY_4WIRE_SPI_H
#define EGLIB_DISPLAY_4WIRE_SPI_H

#include "../hal/4wire_spi.h"
#include "types.h"

typedef struct {
	const eglib_hal_4wire_spi_config_base_t hal_config_base;
	void (*power_up)(
		eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config
	);
	void (*power_down)(
		eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config
	);
	void (*get_dimension)(
		eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config,
		eglib_coordinate_t *width,
		eglib_coordinate_t *height
	);
	void (*draw_pixel)(
		eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config,
		eglib_coordinate_t x,
		eglib_coordinate_t y,
		eglib_color_t color
	);
} eglib_display_4wire_spi_t;

#endif