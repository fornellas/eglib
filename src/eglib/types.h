#ifndef EGLIB_TYPES_H
#define EGLIB_TYPES_H

#include <stdint.h>

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

#endif