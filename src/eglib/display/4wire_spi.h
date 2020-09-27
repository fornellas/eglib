#ifndef EGLIB_DISPLAY_4WIRE_SPI_H
#define EGLIB_DISPLAY_4WIRE_SPI_H

#include "../hal/4wire_spi.h"
#include "types.h"

typedef struct {
	eglib_hal_4wire_spi_config_base_t *(*get_hal_4wire_spi_config_base)(
		void *display_config_ptr
	);
	void (*init)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr
	);
	void (*sleep_in)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr
	);
	void (*sleep_out)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr
	);
	void (*get_dimension)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr,
		eglib_coordinate_t *width,
		eglib_coordinate_t *height
	);
	void (*get_color_depth)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr,
		eglib_color_depth_t *color_depth
	);
	void (*draw_pixel)(
		const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
		void *display_config_ptr,
		eglib_coordinate_t x,
		eglib_coordinate_t y,
		eglib_color_t color
	);
} eglib_display_4wire_spi_t;

#endif