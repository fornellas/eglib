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
	// HAL
	const hal_t *hal;
	void *hal_config_ptr;
	bool hal_comm_active : 1;
	uint8_t hal_i2c_send_slave_addr : 2;
	// Display
	const display_t *display;
	void *display_config_ptr;
	// Drawing
	struct {
		coordinate_t x;
		coordinate_t y;
		coordinate_t width;
		coordinate_t height;
	} clip;
	color_t color_index[4];
};

void eglib_Init(
	eglib_t *eglib,
	const hal_t *hal,
	void *hal_driver_config_ptr,
	const display_t *display,
	void *display_config_ptr
);

void eglib_SleepIn(eglib_t *eglib);
void eglib_SleepOut(eglib_t *eglib);

coordinate_t eglib_GetWidth(eglib_t *eglib);
coordinate_t eglib_GetHeight(eglib_t *eglib);

void eglib_SetClipRange(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

bool eglib_IsPixelClipped(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y
);

void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	color_channel_t r,
	color_channel_t g,
	color_channel_t b
);

// Drawing

#include "drawing.h"

#endif