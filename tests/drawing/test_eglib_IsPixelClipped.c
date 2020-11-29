#include <eglib.h>
#include <eglib/display.h>
#include "draw_test.h"
#include <assert.h>

void draw_test(eglib_t *eglib) {
	eglib_SetClipRange(eglib, 25, 25, 50, 50);
	assert(eglib_IsPixelClipped(eglib, 50, 24));
	assert(eglib_IsPixelClipped(eglib, 50, 76));
	assert(eglib_IsPixelClipped(eglib, 24, 50));
	assert(eglib_IsPixelClipped(eglib, 76, 50));
	assert(!eglib_IsPixelClipped(eglib, 50, 25));
	assert(!eglib_IsPixelClipped(eglib, 50, 75));
	assert(!eglib_IsPixelClipped(eglib, 25, 50));
	assert(!eglib_IsPixelClipped(eglib, 75, 50));
}