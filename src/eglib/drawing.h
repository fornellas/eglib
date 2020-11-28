#ifndef EGLIB_DRAWING_H
#define EGLIB_DRAWING_H

#include "../eglib.h"

/**
 * These are generic drawing functions.
 *
 * :See also: :c:func:`eglib_Init` or :c:func:`eglib_Init_FrameBuffer`.
 */

/**
 * Clipping
 * ========
 *
 * These functions allows restricting drawing functions to only work inside
 * a specified box.
 */

/**
 * Defines a rectangle to clip all drawing functions to.
 *
 * Any drawing function outside of these boundaries will have no effect.
 */
void eglib_SetClipRange(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Returns whether the pixel at given coordinate is clipped. See :c:func:`eglib_SetClipRange`.
 */
bool eglib_IsPixelClipped(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y
);

/**
 * Color
 * =====
 *
 * Various drawing functions do not take a color argument and instead use the
 * color from a previously defined index.
 */

/** Set color for given index, which other drawing functions may use. */
void eglib_SetIndexColor(
	eglib_t *eglib,
	size_t idx,
	color_channel_t r,
	color_channel_t g,
	color_channel_t b
);

/**
 * Pixel
 * =====
 */

/** Draw given pixel coordinates with given color. */
void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color);

/** Draw given pixel coordinates using color from index 0.
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y);

/**
 * Lines
 * =====
 */

/** Draw line from coordinates (`x1`, `y1`) to (`x2`, `y2`) using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawLine(eglib_t *eglib, coordinate_t x1, coordinate_t y1, coordinate_t x2, coordinate_t y2);

/** Draw horizontal line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
#define eglib_DrawHLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x + len, y);

/** Draw vertical line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
#define eglib_DrawVLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x, y + len);

#endif