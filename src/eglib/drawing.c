#include "drawing.h"
#include "display.h"

//
// Clipping
//

void eglib_SetClipRange(
  eglib_t *eglib,
  coordinate_t x,
  coordinate_t y,
  coordinate_t width,
  coordinate_t height
) {
  eglib->clip.x = x;
  eglib->clip.y = y;
  eglib->clip.width = width;
  eglib->clip.height = height;
}

bool eglib_IsPixelClipped(
  eglib_t *eglib,
  coordinate_t x,
  coordinate_t y
) {
  if(x < eglib->clip.x)
    return true;
  if(x > (eglib->clip.x + eglib->clip.width))
    return true;
  if(y < eglib->clip.y)
    return true;
  if(y > (eglib->clip.y + eglib->clip.height))
    return true;
  return false;
}

//
// Color
//

void eglib_SetIndexColor(
  eglib_t *eglib,
  size_t idx,
  color_channel_t r,
  color_channel_t g,
  color_channel_t b
) {
  eglib->color_index[idx].r = r;
  eglib->color_index[idx].g = g;
  eglib->color_index[idx].b = b;
}

//
// Pixel
//

void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color) {
  if(eglib_IsPixelClipped(eglib, x, y))
    return;
  eglib->display->draw_pixel_color(eglib, x, y, color);
}

void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y) {
	eglib_DrawPixelColor(eglib, x, y, eglib->color_index[0]);
}

//
// Gradient
//

static void gradient_channel_begin(
  struct _gradient_channel_t *gradient_channel,
  color_channel_t color_channel_start,
  color_channel_t color_channel_end,
  coordinate_t steps
) {
  gradient_channel->color_channel = color_channel_start;
  gradient_channel->count = 0;
  gradient_channel->step = ((float)color_channel_end - (float)color_channel_start) / (float)steps;
}

static void gradient_begin(
  eglib_t *eglib,
  color_t color_start,
  color_t color_end,
  coordinate_t steps
) {
  gradient_channel_begin(&eglib->gradient.r, color_start.r, color_end.r, steps);
  gradient_channel_begin(&eglib->gradient.g, color_start.g, color_end.g, steps);
  gradient_channel_begin(&eglib->gradient.b, color_start.b, color_end.b, steps);
}

static color_channel_t get_gradient_channel_color(
  struct _gradient_channel_t *gradient_channel
) {
  return gradient_channel->color_channel + gradient_channel->step * ++gradient_channel->count;
}

static color_t get_gradient_color(eglib_t *eglib) {
  color_t color;

  color.r = get_gradient_channel_color(&eglib->gradient.r);
  color.g = get_gradient_channel_color(&eglib->gradient.g);
  color.b = get_gradient_channel_color(&eglib->gradient.b);

  return color;
}

//
// Line
//

static void draw_fast_90_line(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2,
  color_t (*get_next_color)(eglib_t *eglib)
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
      get_next_color
    );
    return;
}

// keep in sync with draw_generic_line()
static coordinate_t get_line_pixel_count(
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
  coordinate_t tmp;
  coordinate_t dx, dy;

  dx = x1 > x2 ? x1 - x2 : x2 - x1;
  dy = y1 > y2 ? y1 - y2 : y2 - y1;

  if (dy > dx) {
    tmp = dx; dx = dy; dy = tmp;
    tmp = x1; x1 = y1; y1 = tmp;
    tmp = x2; x2 = y2; y2 = tmp;
  }
  if (x1 > x2) {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }

  return x2 - x1 + 1;
}

// keep in sync with get_line_pixel_count()
static void draw_generic_line(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2,
  color_t (*get_next_color)(eglib_t *eglib)
) {
  coordinate_t tmp;
  coordinate_t x,y;
  coordinate_t dx, dy;
  coordinate_t err;
  coordinate_t ystep;
  coordinate_t x_arg, y_arg;
  uint8_t swapxy = 0;

  dx = x1 > x2 ? x1 - x2 : x2 - x1;
  dy = y1 > y2 ? y1 - y2 : y2 - y1;

  if(dy > dx) {
    swapxy = 1;
    tmp = dx; dx = dy; dy = tmp;
    tmp = x1; x1 = y1; y1 = tmp;
    tmp = x2; x2 = y2; y2 = tmp;
  }
  if(x1 > x2) {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  err = dx >> 1;
  ystep = y2 > y1 ? 1 : -1;
  y = y1;
  for( x = x1; x <= x2; x++) {
    if(swapxy == 0) {
      x_arg = x;
      y_arg = y;
    } else {
      x_arg = y;
      y_arg = x;
    }
    eglib_DrawPixelColor(eglib, x_arg, y_arg, get_next_color(eglib));
    err -= (uint8_t)dy;
    if(err < 0) {
      y += ystep;
      err += dx;
    }
  }
}

static void draw_line(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2,
  color_t (*get_next_color)(eglib_t *eglib)
) {
  if((x1 == x2) || (y1 == y2))
    draw_fast_90_line(eglib, x1, y1, x2, y2, get_next_color);
  else
    draw_generic_line(eglib, x1, y1, x2, y2, get_next_color);
}

static color_t get_color_index_0(eglib_t *eglib) {
  return eglib->color_index[0];
}

void eglib_DrawLine(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
  draw_line(eglib, x1, y1, x2, y2, get_color_index_0);
}

void eglib_DrawGradientLine(
  eglib_t *eglib,
  coordinate_t x1, coordinate_t y1,
  coordinate_t x2, coordinate_t y2
) {
  gradient_begin(
    eglib,
    eglib->color_index[0],
    eglib->color_index[1],
    get_line_pixel_count(x1, y1, x2, y2)
  );
  draw_line(eglib, x1, y1, x2, y2, get_gradient_color);
}