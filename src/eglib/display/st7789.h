#ifndef EGLIB_DISPLAY_ST7789_H
#define EGLIB_DISPLAY_ST7789_H

#include "../../eglib.h"
#include <stdbool.h>

typedef struct {
	coordinate_t width;
	coordinate_t height;
} st7789_config_t;

extern const display_t st7789;

#endif