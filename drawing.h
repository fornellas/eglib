#ifndef EGLIB_DRAWING_H
#define EGLIB_DRAWING_H

#include "core.h"

void eglib_DrawPixel(eglib_t *ucg, eglib_coordinate_t x, eglib_coordinate_t y);

void eglib_DrawLine(eglib_t *eglib, eglib_coordinate_t x1, eglib_coordinate_t y1, eglib_coordinate_t x2, eglib_coordinate_t y2);
#define eglib_DrawHLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x + len, y);
#define eglib_DrawVLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x, y + len);

#endif