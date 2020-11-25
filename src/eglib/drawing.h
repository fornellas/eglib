#ifndef EGLIB_DRAWING_H
#define EGLIB_DRAWING_H

#include "../eglib.h"

/** Draw given pixel coordinates with given color. */
void eglib_DrawPixelColor(eglib_t *eglib, coordinate_t x, coordinate_t y, color_t color);

/** Draw given pixel coordinates using color from index 0.
 *
 * :See also: :c:func:`eglib_SetColor`.
 */
void eglib_DrawPixel(eglib_t *eglib, coordinate_t x, coordinate_t y);

/** Draw line from coordinates (`x1`, `y1`) to (`x2`, `y2`) using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetColor`.
 */
void eglib_DrawLine(eglib_t *eglib, coordinate_t x1, coordinate_t y1, coordinate_t x2, coordinate_t y2);

/** Draw horizontal line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetColor`.
 */
#define eglib_DrawHLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x + len, y);

/** Draw vertical line starting at (`x`, `y`) with length `len` using color from
 * index 0.
 *
 * :See also: :c:func:`eglib_SetColor`.
 */
#define eglib_DrawVLine(eglib, x, y, len) eglib_DrawLine(eglib, x, y, x, y + len);

#endif