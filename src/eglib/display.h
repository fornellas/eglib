#ifndef EGLIB_DISPLAY_H
#define EGLIB_DISPLAY_H

struct _display_struct;
typedef struct _display_struct display_t;

#include "../eglib.h"
#include "hal.h"
#include "types.h"

struct _display_struct {
	struct {
		hal_four_wire_spi_config_comm_t *four_wire_spi;
		hal_three_wire_spi_config_comm_t *three_wire_spi;
		hal_i2c_config_comm_t *i2c;
	} comm;
	void (*init)(eglib_t *eglib);
	void (*sleep_in)(eglib_t *eglib);
	void (*sleep_out)(eglib_t *eglib);
	void (*get_dimension)(
		eglib_t *eglib,
		coordinate_t *width,
		coordinate_t *height
	);
	void (*get_color_depth)(eglib_t *eglib, color_depth_t *color_depth);
	void (*draw_pixel_color)(
		eglib_t *eglib,
		coordinate_t x,
		coordinate_t y,
		color_t color
	);
	void (*send_buffer)(
		eglib_t *eglib,
		void *buffer,
		coordinate_t x, coordinate_t y,
		coordinate_t width, coordinate_t height
	);
};

#define display_get_i2c_7bit_slave_addr(eglib, dc) \
	(eglib->display->comm.i2c->get_7bit_slave_addr(eglib, dc))

#define display_config(eglib) (eglib->display_config_ptr)

#endif