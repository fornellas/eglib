#ifndef EGLIB_TYPES_H
#define EGLIB_TYPES_H

#include <stdint.h>

typedef enum {
	EGLIB_COLOR_DEPTH_1BIT_PAGED,
	EGLIB_COLOR_DEPTH_18BIT_565_RGB,
	EGLIB_COLOR_DEPTH_24BIT_RGB,
	EGLIB_COLOR_DEPTH_COUNT,
} color_depth_t;

typedef uint8_t color_channel_t;

typedef struct {
	color_channel_t r;
	color_channel_t g;
	color_channel_t b;
} color_t;

typedef int16_t coordinate_t;

#endif