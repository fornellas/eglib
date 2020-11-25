#include "drawing.h"
#include "display.h"

void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color) {
  if(eglib_IsPixelClipped(eglib, x, y))
    return;
  eglib->display->draw_pixel_color(eglib, x, y, color);
}

void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y) {
	eglib_DrawPixelColor(eglib, x, y, eglib->color_index[0]);
}

static color_t get_next_color_index0(eglib_t *eglib) {
  return eglib->color_index[0];
}

static void draw_fast_90_line(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
    coordinate_t x,y;
    display_line_direction_t direction;
    coordinate_t length;

    x = x1 > x2 ? x2 : x1;
    y = y1 > y2 ? y2 : y1;

    if(x1==x2) {  // vertical
      length = y1 > y2 ? y1 - y2 : y2 - y1;
      if(y1 > y2)
        direction = DISPLAY_LINE_DIRECTION_UP;
      else
        direction = DISPLAY_LINE_DIRECTION_DOWN;
    } else {  // horizontal
      length = x1 > x2 ? x1 - x2 : x2 - x1;
      if(y1 > y2)
        direction = DISPLAY_LINE_DIRECTION_LEFT;
      else
        direction = DISPLAY_LINE_DIRECTION_RIGHT;
    }

    eglib->display->draw_line(
      eglib,
      x, y,
      direction,
      length,
      get_next_color_index0
    );
    return;
}

static void draw_generic_line(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
  coordinate_t tmp;
  coordinate_t x,y;
  coordinate_t dx, dy;
  coordinate_t err;
  coordinate_t ystep;
  coordinate_t x_arg, y_arg;
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

void eglib_DrawLine(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
  if((x1 == x2) || (y1 == y2))
    draw_fast_90_line(eglib, x1, y1, x2, y2);
  else
    draw_generic_line(eglib, x1, y1, x2, y2);
}