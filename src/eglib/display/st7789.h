#ifndef EGLIB_DISPLAY_ST7789_H
#define EGLIB_DISPLAY_ST7789_H

#include "../../eglib.h"
#include <stdbool.h>

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;
} eglib_display_st7789_config_t;

extern const eglib_display_t eglib_display_st7789;

#endif