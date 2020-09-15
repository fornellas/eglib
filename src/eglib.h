#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// HAL

#include "eglib/hal/4wire_spi.h"
#include "eglib/hal/i2c.h"

// Display

#include "eglib/display/types.h"
#include "eglib/display/4wire_spi.h"
#include "eglib/display/i2c.h"

// Eglib

struct eglib_struct_t {
	void *hal;
	void *hal_config;
	void (*hal_power_up)(struct eglib_struct_t *eglib);
	void (*hal_power_down)(struct eglib_struct_t *eglib);

	void *display;
	void *display_config;
	void (*display_power_up)(struct eglib_struct_t *eglib);
	void (*display_power_down)(struct eglib_struct_t *eglib);
	void (*display_get_dimension)(
		struct eglib_struct_t *eglib,
		eglib_coordinate_t *width,
		eglib_coordinate_t *height
	);
	void (*display_draw_pixel)(
		struct eglib_struct_t *eglib,
		eglib_coordinate_t x,
		eglib_coordinate_t y,
		eglib_color_t color
	);

	struct {
		eglib_coordinate_t x;
		eglib_coordinate_t y;
		eglib_coordinate_t width;
		eglib_coordinate_t height;
	} clip;

	eglib_color_t color_index[4];
} eglib_struct_t;

typedef struct eglib_struct_t eglib_t;

// Init

void eglib_Init_4wire_spi(
	eglib_t *eglib,
	const eglib_hal_4wire_spi_t *hal_4wire_spi, void *hal_4wire_spi_config,
	const eglib_display_4wire_spi_t *display_4wire_spi, void *display_4wire_spi_config
);

void eglib_Init_i2c(
	eglib_t *eglib,
	const eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
	const eglib_display_i2c_t *display_i2c, void *display_i2c_config
);

// Common

void eglib_PowerUp(eglib_t *eglib);
void eglib_PowerDown(eglib_t *eglib);

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib);
eglib_coordinate_t eglib_GetHeight(eglib_t *eglib);

void eglib_SetClipRange(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

bool eglib_IsPixelClipped(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y
);

void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	eglib_color_channel_t r,
	eglib_color_channel_t g,
	eglib_color_channel_t b
);

// Drawing

#include "drawing.h"

#endif