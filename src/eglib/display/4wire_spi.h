#ifndef EGLIB_DISPLAY_4WIRE_SPI_H
#define EGLIB_DISPLAY_4WIRE_SPI_H

struct _eglib_display_4wire_spi_struct;
typedef struct _eglib_display_4wire_spi_struct eglib_display_4wire_spi_t;

#include "../../eglib.h"
#include "../hal/4wire_spi.h"
#include "types.h"

struct _eglib_display_4wire_spi_struct {
	eglib_hal_4wire_spi_config_comm_t hal_4wire_spi_config_comm;
	void (*init)(eglib_t *eglib);
	void (*sleep_in)(eglib_t *eglib);
	void (*sleep_out)(eglib_t *eglib);
	void (*get_dimension)(
		eglib_t *eglib,
		eglib_coordinate_t *width,
		eglib_coordinate_t *height
	);
	void (*get_color_depth)(eglib_t *eglib, eglib_color_depth_t *color_depth);
	void (*draw_pixel_color)(
		eglib_t *eglib,
		eglib_coordinate_t x,
		eglib_coordinate_t y,
		eglib_color_t color
	);
	void (*send_buffer)(
		eglib_t *eglib,
		void *buffer,
		eglib_coordinate_t x, eglib_coordinate_t y,
		eglib_coordinate_t width, eglib_coordinate_t height
	);
};

#endif