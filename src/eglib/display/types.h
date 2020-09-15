#ifndef EGLIB_DISPLAY_TYPES_H
#define EGLIB_DISPLAY_TYPES_H

#include <stdint.h>

typedef uint8_t eglib_color_channel_t;

typedef struct {
	eglib_color_channel_t r;
	eglib_color_channel_t g;
	eglib_color_channel_t b;
} eglib_color_t;

typedef int16_t eglib_coordinate_t;

#endif