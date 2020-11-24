#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	// 1bit per pixel where each number of bytes equal to the display width
	// is a page: MSB bits are the upper line, LSB bits are the lower line.
	PIXEL_FORMAT_1BIT_BW_PAGED,
	// RRRRGGGG BBBBRRRR GGGGBBBB
	PIXEL_FORMAT_12BIT_RGB,
	// RRRRRGGG GGGBBBBB
	PIXEL_FORMAT_16BIT_RGB,
	// RRRRRRxx GGGGGGxx BBBBBBxx
	PIXEL_FORMAT_18BIT_RGB_24BIT,
	// RRRRRRRR GGGGGGGG BBBBBBBB
	PIXEL_FORMAT_24BIT_RGB,
	PIXEL_FORMAT_COUNT,
} pixel_format_t;

typedef uint8_t color_channel_t;

typedef struct {
	color_channel_t r;
	color_channel_t g;
	color_channel_t b;
} color_t;

typedef int16_t coordinate_t;

struct _eglib_struct;
typedef struct _eglib_struct eglib_t;

#include "eglib/hal.h"
#include "eglib/display.h"

// Eglib

struct _eglib_struct {
	// HAL
	const hal_t *hal;
	void *hal_config_ptr;
	// Set in between hal_begin and hal_end
	bool hal_comm_active : 1;
	// Whether hal_t send() must send slave address for I2C
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