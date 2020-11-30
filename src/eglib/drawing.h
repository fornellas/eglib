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
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_SetClipRange.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_SetClipRange.png
 *   :width: 200
 */
void eglib_SetClipRange(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Disable clipping.
 *
 * :See also: :c:func:`eglib_SetClipRange`.
 */
void eglib_SetNoClip(eglib_t *eglib);

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

/**
 * Draw given pixel coordinates with given color.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawPixelColor.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawPixelColor.png
 *   :width: 200
 */
void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color);

/**
 * Draw given pixel coordinates using color from index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawPixel.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawPixel.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y);

/**
 * Lines
 * =====
 */

/**
 * Draw line from coordinates (`x1`, `y1`) to (`x2`, `y2`) using color from
 * index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawLine(eglib_t *eglib, coordinate_t x1, coordinate_t y1, coordinate_t x2, coordinate_t y2);

/**
 * Draw horizontal line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawHLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawHLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
#define eglib_DrawHLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x + len, y);

/**
 * Draw vertical line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawVLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawVLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
#define eglib_DrawVLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x, y + len);

/**
 * Draw line from coordinates (`x1`, `y1`) to (`x2`, `y2`).
 *
 * Line color will be a gradient from index 0 at (`x1`, `y1`) to color from index
 * 1 at (`x2`, `y2`).
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawGradientLine(
	eglib_t *eglib,
	coordinate_t x1, coordinate_t y1,
	coordinate_t x2, coordinate_t y2
);

/**
 * Draw horizontal gradient line from coordinates (`x`, `y`) to (`x + len`, `y`).
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientHLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientHLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_DrawGradientLine`.
 */
#define eglib_DrawGradientHLine(eglib, x, y, len) eglib_DrawGradientLine( \
	eglib, \
	x, y, \
	x + len, y \
)

/**
 * Draw vertical gradient line from coordinates (`x`, `y`) to (`x`, `y + len`).
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientVLine.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientVLine.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_DrawGradientLine`.
 */
#define eglib_DrawGradientVLine(eglib, x, y, len) eglib_DrawGradientLine( \
	eglib, \
	x, y, \
	x, y + len \
)

/**
 * Boxes
 * =====
 */

/**
 * Draw frame starting at ``(x, y)`` with ``width`` and ``height`` using color
 * from index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawFrame.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawFrame.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawFrame(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Draw frame starting at ``(x, y)`` with ``width`` and ``height``.
 *
 * Its colors will be a gradient:
 *
 * - Top left: color index 0.
 * - Top right: color index 1.
 * - Bottom left: color index 2.
 * - Bottom right: color index 3.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientFrame.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientFrame.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawGradientFrame(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Draw box starting at ``(x, y)`` with ``width`` and ``height`` using color
 * from index 0.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawBox.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawBox.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawBox(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Draw box starting at ``(x, y)`` with ``width`` and ``height``.
 *
 * Its colors will be a gradient:
 *
 * - Top left: color index 0.
 * - Top right: color index 1.
 * - Bottom left: color index 2.
 * - Bottom right: color index 3.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientBox.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientBox.png
 *   :width: 200
 *
 * :See also: :c:func:`eglib_SetIndexColor`.
 */
void eglib_DrawGradientBox(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

/**
 * Clear screen, all pixels black, just like after :c:func:`eglib_Init`.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_ClearScreen.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_ClearScreen.png
 *   :width: 200
 */
void eglib_ClearScreen(eglib_t *eglib);

/**
 * Arcs
 * ====
 */

/**
 * Draw an arc with color from index 0
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 * :param start_angle: Start angle from 0 to 360, where 0 is "up" and 90 is "right".
 * :param end_angle: End angle, bigger than ``start_angle`` and less or equal to 360.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawArc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawArc.png
 *   :width: 200
 */
void eglib_DrawArc(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t radius,
	float start_angle,
	float end_angle
);

/**
 * Draw an arc with color gradient from index 0 to index 1.
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 * :param start_angle: Start angle from 0 to 360, where 0 is "up" and 90 is "right".
 * :param end_angle: End angle, bigger than ``start_angle`` and less or equal to 360.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientArc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientArc.png
 *   :width: 200
 */
void eglib_DrawGradientArc(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t radius,
	float start_angle,
	float end_angle
);

/**
 * Draw an arc with color from index 0
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawCircle.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawCircle.png
 *   :width: 200
 */
#define eglib_DrawCircle(eglib, x, y, radius) eglib_DrawArc(eglib, x, y, radius, 0, 360);

/**
 * Draw a filled arc with color from index 0
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 * :param start_angle: Start angle from 0 to 360, where 0 is "up" and 90 is "right".
 * :param end_angle: End angle, bigger than ``start_angle`` and less or equal to 360.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawFilledArc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawFilledArc.png
 *   :width: 200
 */
void eglib_DrawFilledArc(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t radius,
	float start_angle,
	float end_angle
);

/**
 * Draw a filled arc with color gradient from index 0 at the center and index 1
 * at the radius.
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 * :param start_angle: Start angle from 0 to 360, where 0 is "up" and 90 is "right".
 * :param end_angle: End angle, bigger than ``start_angle`` and less or equal to 360.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientFilledArc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientFilledArc.png
 *   :width: 200
 */
void eglib_DrawGradientFilledArc(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t radius,
	float start_angle,
	float end_angle
);

/**
 * Draw a disc with color from index 0
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawDisc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawDisc.png
 *   :width: 200
 */
#define eglib_DrawDisc(eglib, x, y, radius) eglib_DrawFilledArc(eglib, x, y, radius, 0, 360)

/**
 * Draw a disc with color gradient from index 0 at the center and index 1 at the
 * radius.
 *
 * :param x: Center x.
 * :param y: Center y.
 * :param radius: Radius.
 *
 * Example:
 *
 * .. literalinclude:: ../../tests/drawing/test_eglib_DrawGradientDisc.c
 *   :language: C
 *
 * Output:
 *
 * .. image:: ../../tests/drawing/test_eglib_DrawGradientDisc.png
 *   :width: 200
 */
#define eglib_DrawGradientDisc(eglib, x, y, radius) eglib_DrawGradientFilledArc(eglib, x, y, radius, 0, 360)

#endif