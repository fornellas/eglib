#include <eglib.h>
#include <eglib/display.h>
#include "draw_test.h"

void draw_test(eglib_t *eglib) {
	eglib_SetClipRange(eglib, 25, 25, 50, 50);
	eglib_SetIndexColor(eglib, 0, 255, 0, 0);
	eglib_DrawFrame(eglib, 24, 24, 52, 52);
	eglib_SetIndexColor(eglib, 0, 0, 255, 0);
	eglib_DrawFrame(eglib, 25, 25, 50, 50);
}