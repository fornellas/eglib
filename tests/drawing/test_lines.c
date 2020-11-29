#include <eglib.h>
#include <eglib/display.h>
#include "draw_test.h"

void draw_test(eglib_t *eglib) {
	coordinate_t width, height;

	width = eglib_GetWidth(eglib);
	height = eglib_GetHeight(eglib);

	eglib_SetIndexColor(eglib, 0, 0, 0, 0);
	for(coordinate_t v=0 ; (v < width) && (v < height) ; v++ )
		eglib_DrawPixel(eglib, v, v);

	eglib_SetClipRange(eglib, 0, 0, width / 2, height / 2);

	eglib_SetIndexColor(eglib, 0, 255, 0, 0);
	eglib_DrawLine(eglib, 0, 0, width - 1, 0);

	eglib_SetIndexColor(eglib, 0, 0, 255, 0);
	eglib_DrawLine(eglib, 0, height - 1, 0, 0);

	eglib_SetIndexColor(eglib, 0, 0, 0, 255);
	eglib_DrawLine(eglib, 0, 0, width - 1, height - 1);

	eglib_SetIndexColor(eglib, 0, 0, 255, 255);
	eglib_SetIndexColor(eglib, 1, 255, 0, 0);
	eglib_DrawGradientLine(eglib, 0, 0, width / 4, height / 2);

	eglib_SetIndexColor(eglib, 0, 255, 0, 255);
	eglib_SetIndexColor(eglib, 1, 0, 255, 0);
	eglib_DrawGradientLine(eglib, 0, 0, width / 2, height / 4);
}