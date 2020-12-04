#include <eglib.h>
#include <eglib/display.h>
#include "draw_test.h"

void draw_test(eglib_t *eglib) {
  coordinate_t x, y;

  x = 50 - 14;
  y = 30 + 14 / 2;

  eglib_SetIndexColor(eglib, 0, 0, 0, 128);
  eglib_DrawLine(eglib, 0, y, 99, y);
  eglib_DrawLine(eglib, 0, y * 2, 99, y * 2);
  eglib_DrawLine(eglib, x, 0, x, 99);

  eglib_SetFont(eglib, &font_LiberationSans_Regular_20px);
  eglib_SetIndexColor(eglib, 0, 255, 255, 255);
  eglib_DrawGlyph(eglib, x, y, 'g');
  eglib_DrawGlyph(eglib, x, y * 2, 9999);  // Unsupported by font
}