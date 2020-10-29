#include "drawing.h"

void eglib_DrawPixelColor(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color) {
  if(eglib_IsPixelClipped(eglib, x, y))
    return;
  eglib->display->draw_pixel_color(eglib, x, y, color);
}

void eglib_DrawPixel(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y) {
	eglib_DrawPixelColor(eglib, x, y, eglib->color_index[0]);
}

void eglib_DrawLine(eglib_t *eglib, eglib_coordinate_t x1, eglib_coordinate_t y1, eglib_coordinate_t x2, eglib_coordinate_t y2) {
  eglib_coordinate_t tmp;
  eglib_coordinate_t x,y;
  eglib_coordinate_t dx, dy;
  eglib_coordinate_t err;
  eglib_coordinate_t ystep;
  eglib_coordinate_t x_arg, y_arg;
  uint8_t swapxy = 0;
   
  if ( x1 > x2 ) dx = x1-x2; else dx = x2-x1;
  if ( y1 > y2 ) dy = y1-y2; else dy = y2-y1;

  if ( dy > dx ) {
    swapxy = 1;
    tmp = dx; dx =dy; dy = tmp;
    tmp = x1; x1 =y1; y1 = tmp;
    tmp = x2; x2 =y2; y2 = tmp;
  }
  if ( x1 > x2 ) {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  err = dx >> 1;
  if ( y2 > y1 ) ystep = 1; else ystep = -1;
  y = y1;
  for( x = x1; x <= x2; x++ ) {
    if ( swapxy == 0 ) {
      x_arg = x;
      y_arg = y;
    } else {
      x_arg = y;
      y_arg = x;
    }
    eglib_DrawPixel(eglib, x_arg, y_arg);
    err -= (uint8_t)dy;
    if ( err < 0 ) {
      y += ystep;
      err += dx;
    }
  }
}