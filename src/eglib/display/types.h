#ifndef EGLIB_DISPLAY_TYPES_H
#define EGLIB_DISPLAY_TYPES_H

#include <stdint.h>

typedef enum {
	EGLIB_COLOR_DEPTH_1BIT_PAGED,
	EGLIB_COLOR_DEPTH_18BIT_565_RGB,
	EGLIB_COLOR_DEPTH_24BIT_RGB,
	EGLIB_COLOR_DEPTH_COUNT,
} eglib_color_depth_t;

typedef uint8_t eglib_color_channel_t;

typedef struct {
	eglib_color_channel_t r;
	eglib_color_channel_t g;
	eglib_color_channel_t b;
} eglib_color_t;

typedef int16_t eglib_coordinate_t;

#endif