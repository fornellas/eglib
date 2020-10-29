#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct _eglib_struct;
typedef struct _eglib_struct eglib_t;

#include "eglib/hal.h"
#include "eglib/types.h"
#include "eglib/display.h"

// Eglib

struct _eglib_struct {
	// Drivers
	const eglib_hal_t *hal;
	eglib_hal_config_t hal_config;
	const eglib_display_t *display;
	void *display_config_ptr;
	// Drawing
	struct {
		eglib_coordinate_t x;
		eglib_coordinate_t y;
		eglib_coordinate_t width;
		eglib_coordinate_t height;
	} clip;
	eglib_color_t color_index[4];
};

void eglib_Init(
	eglib_t *eglib,
	const eglib_hal_t *hal,
	void *hal_driver_config_ptr,
	const eglib_display_t *display,
	void *display_config_ptr
);

void eglib_SleepIn(eglib_t *eglib);
void eglib_SleepOut(eglib_t *eglib);

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