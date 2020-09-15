#ifndef EGLIB_DISPLAY_I2C_H
#define EGLIB_DISPLAY_I2C_H

#include "../hal/i2c.h"
#include "types.h"

typedef struct {
	void (*power_up)(
		eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
		void *display_i2c_config
	);
	void (*power_down)(
		eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
		void *display_i2c_config
	);
	void (*get_dimension)(
		eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
		void *display_i2c_config,
		eglib_coordinate_t *width,
		eglib_coordinate_t *height
	);
	void (*draw_pixel)(
		eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
		void *display_i2c_config,
		eglib_coordinate_t x,
		eglib_coordinate_t y,
		eglib_color_t color
	);
} eglib_display_i2c_t;

#endif