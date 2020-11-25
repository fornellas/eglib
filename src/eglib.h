#ifndef EGLIB_H
#define EGLIB_H

#include "eglib/types.h"
#include "eglib/drawing.h"

struct _eglib_struct {
	// HAL
	const hal_t *hal;
	void *hal_config_ptr;
	// Set in between hal_begin and hal_end
	bool hal_comm_active : 1;
	// Whether hal_t send() must send slave address for I2C
	uint8_t hal_i2c_send_slave_addr : 2;

	// Display
	const display_t *display;
	void *display_config_ptr;
	bool display_refreshing : 1;

	// Drawing
	struct {
		coordinate_t x;
		coordinate_t y;
		coordinate_t width;
		coordinate_t height;
	} clip;
	color_t color_index[4];
};

/**
 * Initializer for :c:type:`eglib_t`. The given HAL driver must be of a bus that
 * the display driver supports.
 *
 * :param eglib: Pointer to :c:type:`eglib_t` to be initialized.
 * :param hal: Pointer to the HAL driver :c:type:`hal_t` to use.
 * :param hal_driver_config_ptr: Pointer to the HAL driver configuration.
 *  Please refer each HAL driver documentation for details.
 * :param display: Pointer to the display driver :c:type:`display_t` to use.
 * :param display_config_ptr: Pointer to the display driver configuration.
 *  Please refer each display driver documentation for details.
 */
void eglib_Init(
	eglib_t *eglib,
	const hal_t *hal,
	void *hal_driver_config_ptr,
	const display_t *display,
	void *display_config_ptr
);

/** Puts both HAL and display to sleep. See :c:func:`eglib_SleepOut`. */
void eglib_SleepIn(eglib_t *eglib);

/** Takes both HAL and display out of sleep. See :c:func:`eglib_SleepIn` */
void eglib_SleepOut(eglib_t *eglib);

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
 * Drawing functions often use colors defined by an index which can be defined
 * by this function.
 *
 * Please refer to drawing functions for appropriate values.
 */
void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	color_channel_t r,
	color_channel_t g,
	color_channel_t b
);

#endif