#include "drawing.h"
#include "display.h"
#include <math.h>

#define degrees_to_radians(degrees) ((degrees) * M_PI / 180.0)

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

void eglib_SetNoClip(eglib_t *eglib) {
  eglib_SetClipRange(
    eglib,
    0, 0,
    eglib_GetWidth(eglib), eglib_GetHeight(eglib)
  );
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
  struct _gradient_t *gradient,
  color_t color_start,
  color_t color_end,
  coordinate_t steps
) {
  gradient_channel_begin(&gradient->r, color_start.r, color_end.r, steps);
  gradient_channel_begin(&gradient->g, color_start.g, color_end.g, steps);
  gradient_channel_begin(&gradient->b, color_start.b, color_end.b, steps);
}

static color_channel_t get_gradient_channel_color(
  struct _gradient_channel_t *gradient_channel
) {
  return gradient_channel->color_channel + gradient_channel->step * ++gradient_channel->count;
}

static color_t get_next_gradient_color_eglib(eglib_t *eglib) {
  color_t color;

  color.r = get_gradient_channel_color(&eglib->gradient.r);
  color.g = get_gradient_channel_color(&eglib->gradient.g);
  color.b = get_gradient_channel_color(&eglib->gradient.b);

  return color;
}

static color_t get_next_gradient_color(struct _gradient_t *gradient) {
  color_t color;

  color.r = get_gradient_channel_color(&gradient->r);
  color.g = get_gradient_channel_color(&gradient->g);
  color.b = get_gradient_channel_color(&gradient->b);

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
    display_line_direction_t direction;
    coordinate_t length;
    coordinate_t clip_x_end;
    coordinate_t clip_y_end;

    if(x1==x2) {  // vertical
      length = y2 > y1 ? y2 - y1 : y1 - y2;
      if(y2 > y1)
        direction = DISPLAY_LINE_DIRECTION_DOWN;
      else
        direction = DISPLAY_LINE_DIRECTION_UP;
    } else if(y1==y2) {  // horizontal
      length = x2 > x1 ? x2 - x1 : x1 - x2;
      if(x2 > x1)
        direction = DISPLAY_LINE_DIRECTION_RIGHT;
      else
        direction = DISPLAY_LINE_DIRECTION_LEFT;
    } else
      while(true);

    clip_x_end = eglib->clip.x + eglib->clip.width;
    clip_y_end = eglib->clip.y + eglib->clip.height;

    switch(direction) {
      case DISPLAY_LINE_DIRECTION_RIGHT:
      case DISPLAY_LINE_DIRECTION_LEFT:
        if((y1 < eglib->clip.y) || (y1 > clip_y_end))
          return;
        break;
      case DISPLAY_LINE_DIRECTION_DOWN:
      case DISPLAY_LINE_DIRECTION_UP:
        if((x1 < eglib->clip.x) || (x1 > clip_x_end))
          return;
        break;
    }

    switch(direction) {
      case DISPLAY_LINE_DIRECTION_RIGHT:
        if(x1 < eglib->clip.x) {
          length -= eglib->clip.x - x1;
          x1 = eglib->clip.x;
        }
        if(x1 + length > clip_x_end)
          length -= (x1 + length) - (clip_x_end);
        break;
      case DISPLAY_LINE_DIRECTION_LEFT:
        if(x1 > clip_x_end) {
          length -= x1 - (clip_x_end);
          x1 = clip_x_end;
        }
        if(x1 - length < eglib->clip.x)
          length -= (x1 - length) - eglib->clip.x;
        break;
      case DISPLAY_LINE_DIRECTION_DOWN:
        if(y1 < eglib->clip.y) {
          length -= eglib->clip.y - y1;
          y1 = eglib->clip.y;
        }
        if(y1 + length > clip_y_end)
          length -= (y1 + length) - (clip_y_end);
        break;
      case DISPLAY_LINE_DIRECTION_UP:
        if(y1 > clip_y_end) {
          length -= y1 - (clip_y_end);
          y1 = clip_y_end;
        }
        if(y1 - length < eglib->clip.y)
          length -= (y1 - length) - eglib->clip.y;
        break;
    }

    if(length < 1)
      return;

    eglib->display->draw_line(
      eglib,
      x1, y1,
      direction,
      length,
      get_next_color
    );
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
  bool reversed = false;

  dx = x1 > x2 ? x1 - x2 : x2 - x1;
  dy = y1 > y2 ? y1 - y2 : y2 - y1;

  if(dy > dx) {
    swapxy = 1;
    tmp = dx; dx = dy; dy = tmp;
    tmp = x1; x1 = y1; y1 = tmp;
    tmp = x2; x2 = y2; y2 = tmp;
  }
  if(x1 > x2) {
    reversed = true;
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  err = dx >> 1;
  ystep = y2 > y1 ? 1 : -1;
  y = y1;
  if(reversed) {
    for( x = x2 ; x >= x1 ; x--) {
      x_arg = x;
      y_arg = y2;
      eglib_DrawPixelColor(eglib, x_arg, y_arg, get_next_color(eglib));
      err -= (uint8_t)dy;
      if(err < 0) {
        y2 -= ystep;
        err += dx;
      }
    }
  } else {
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
    &eglib->gradient,
    eglib->color_index[0], eglib->color_index[1],
    get_line_pixel_count(x1, y1, x2, y2)
  );
  draw_line(eglib, x1, y1, x2, y2, get_next_gradient_color_eglib);
}

//
// Boxes
//

void eglib_DrawFrame(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t width, coordinate_t height
) {
  eglib_DrawHLine(eglib, x, y, width);
  eglib_DrawHLine(eglib, x, y + height, width);
  eglib_DrawVLine(eglib, x, y, height);
  eglib_DrawVLine(eglib, x + width, y, height);
}

void eglib_DrawGradientFrame(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t width, coordinate_t height
) {
  color_t previous_color_index_0;
  color_t previous_color_index_1;

  previous_color_index_0 = eglib->color_index[0];
  previous_color_index_1 = eglib->color_index[1];

  eglib_DrawGradientHLine(eglib, x, y, width);
  eglib->color_index[0] = eglib->color_index[2];
  eglib->color_index[1] = eglib->color_index[3];
  eglib_DrawGradientHLine(eglib, x, y + height, width);
  eglib->color_index[0] = previous_color_index_0;
  eglib->color_index[1] = eglib->color_index[2];
  eglib_DrawGradientVLine(eglib, x, y, height);
  eglib->color_index[0] = previous_color_index_1;
  eglib->color_index[1] = eglib->color_index[3];
  eglib_DrawGradientVLine(eglib, x + width, y, height);

  eglib->color_index[0] = previous_color_index_0;
  eglib->color_index[1] = previous_color_index_1;
}

void eglib_DrawBox(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t width, coordinate_t height
) {
  for( ; height ; height--, y++)
    eglib_DrawHLine(eglib, x, y, width);
}

void eglib_DrawGradientBox(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t width, coordinate_t height
) {
  color_t previous_color_index_0;
  color_t previous_color_index_1;
  struct _gradient_t gradient_left;
  struct _gradient_t gradient_right;

  previous_color_index_0 = eglib->color_index[0];
  previous_color_index_1 = eglib->color_index[1];

  gradient_begin(
    &gradient_left,
    eglib->color_index[0], eglib->color_index[2],
    height
  );
  gradient_begin(
    &gradient_right,
    eglib->color_index[1], eglib->color_index[3],
    height
  );

  for( ; height ; height--, y++) {
    eglib->color_index[0] = get_next_gradient_color(&gradient_left);
    eglib->color_index[1] = get_next_gradient_color(&gradient_right);
    eglib_DrawGradientHLine(eglib, x, y, width);
  }

  eglib->color_index[0] = previous_color_index_0;
  eglib->color_index[1] = previous_color_index_1;
}

void eglib_ClearScreen(eglib_t *eglib) {
  color_t previous_color_index_0;
  struct _clip_t previous_clip;

  previous_color_index_0 = eglib->color_index[0];
  previous_clip = eglib->clip;

  eglib_SetNoClip(eglib);

  eglib_SetIndexColor(eglib, 0, 0, 0, 0);

  eglib_DrawBox(
    eglib,
    0, 0,
    eglib_GetWidth(eglib) - 1,
    eglib_GetHeight(eglib) - 1
  );

  eglib->color_index[0] = previous_color_index_0;
  eglib->clip = previous_clip;
}

//
// Arc
//

void eglib_DrawArc(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t radius,
  float start_angle,
  float end_angle
) {
  float angle_step;
  coordinate_t last_x=-1, last_y=-1;

  angle_step = degrees_to_radians((2.0 * M_PI * radius) / 360.0);
  start_angle = degrees_to_radians(start_angle - 90);
  end_angle = degrees_to_radians(end_angle - 90);

  for(float angle=start_angle ; angle <= end_angle ; angle+= angle_step) {
    coordinate_t curr_x, curr_y;

    curr_x = x + round(cos(angle) * radius);
    curr_y = y + round(sin(angle) * radius);

    if(curr_x == last_x && curr_y == last_y)
      continue;

    eglib_DrawPixel(eglib, curr_x, curr_y);

    last_x = curr_x;
    last_y = curr_y;
  }
}

void eglib_DrawFilledArc(
  eglib_t *eglib,
  coordinate_t x, coordinate_t y,
  coordinate_t radius,
  float start_angle,
  float end_angle
) {
  eglib_DrawPixel(eglib, x, y);

  for(coordinate_t r=1 ; r <= radius ; r++)
    eglib_DrawArc(eglib, x, y, r, start_angle, end_angle);
}