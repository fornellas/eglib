#include <eglib.h>
#include "draw_test.h"

void draw_test(eglib_t *eglib) {
  eglib_ClearScreen(eglib);

  eglib_SetIndexColor(eglib, 0, 255, 0, 0);
  eglib_DrawFrame(eglib, 10, 20, 10, 20);

  eglib_SetIndexColor(eglib, 0, 0, 255, 0);
  eglib_DrawBox(eglib, 10, 50, 10, 20);

  eglib_SetIndexColor(eglib, 0, 255, 0, 0);
  eglib_SetIndexColor(eglib, 1, 0, 255, 0);
  eglib_SetIndexColor(eglib, 2, 0, 0, 255);
  eglib_SetIndexColor(eglib, 3, 255, 255, 255);
  eglib_DrawGradientFrame(eglib, 30, 20, 10, 20);

  eglib_DrawGradientBox(eglib, 30, 50, 10, 20);
}