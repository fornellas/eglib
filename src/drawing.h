#ifndef EGLIB_DRAWING_H
#define EGLIB_DRAWING_H

#include "eglib.h"

void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color);
void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y);

void eglib_DrawLine(eglib_t *eglib, coordinate_t x1, coordinate_t y1, coordinate_t x2, coordinate_t y2);
#define eglib_DrawHLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x + len, y);
#define eglib_DrawVLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x, y + len);

#endif