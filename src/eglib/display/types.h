#ifndef EGLIB_DISPLAY_TYPES_H
#define EGLIB_DISPLAY_TYPES_H

#include <stdint.h>

typedef enum {
	EGLIB_COLOR_DEPTH_1BIT,
	EGLIB_COLOR_DEPTH_2BIT,
	EGLIB_COLOR_DEPTH_12BIT,
	EGLIB_COLOR_DEPTH_16BIT,
	EGLIB_COLOR_DEPTH_18BIT,
	EGLIB_COLOR_DEPTH_24BIT,
} eglib_color_depth_t;

typedef uint8_t eglib_color_channel_t;

typedef struct {
	eglib_color_channel_t r;
	eglib_color_channel_t g;
	eglib_color_channel_t b;
} eglib_color_t;

typedef int16_t eglib_coordinate_t;

#endif