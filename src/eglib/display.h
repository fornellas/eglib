#ifndef EGLIB_DISPLAY_H
#define EGLIB_DISPLAY_H

struct _eglib_display_struct;
typedef struct _eglib_display_struct eglib_display_t;

#include "../eglib.h"
#include "hal.h"
#include "types.h"

struct _eglib_display_struct {
	struct {
		eglib_hal_four_wire_spi_config_comm_t *four_wire_spi;
		eglib_hal_three_wire_spi_config_comm_t *three_wire_spi;
		eglib_hal_i2c_config_comm_t *i2c;
	} comm;
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

#define eglib_display_i2c_get_7bit_slave_addr(eglib, dc) \
	(eglib->display->comm.i2c->get_7bit_slave_addr(eglib, dc))

#endif