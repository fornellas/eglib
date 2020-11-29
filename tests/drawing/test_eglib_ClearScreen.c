#include <eglib.h>
#include <eglib/display.h>
#include "draw_test.h"

void draw_test(eglib_t *eglib) {
  eglib_SetIndexColor(eglib, 0, 0, 255, 0);
  eglib_DrawBox(eglib, 10, 10, 80, 80);
  eglib_SetClipRange(eglib, 20, 20, 60, 60);
  eglib_ClearScreen(eglib);
}