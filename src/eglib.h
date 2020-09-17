#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// HAL

#include "eglib/hal/4wire_spi.h"

// Display

#include "eglib/display/types.h"
#include "eglib/display/4wire_spi.h"

// Eglib

struct eglib_struct_t {
	// HAL
	const void *hal;
	void *hal_config_driver;
	void (*hal_power_up)(struct eglib_struct_t *eglib);
	void (*hal_power_down)(struct eglib_struct_t *eglib);

	// Display
	const void *display;
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

	// Drawing
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
	const eglib_hal_4wire_spi_t *hal,
	void *hal_config_driver,
	const eglib_display_4wire_spi_t *display,
	void *display_config
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