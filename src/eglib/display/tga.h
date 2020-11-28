#ifndef EGLIB_DISPLAY_TGA_H
#define EGLIB_DISPLAY_TGA_H

#include "../display.h"

/**
 * Driver
 * ======
 */

/**
 * Configuration for :c:data:`tga`.
 *
 * :See also: :c:func:`eglib_Init`.
 */
typedef struct {
	/** TGA width */
	coordinate_t width;
	/** TGA height */
	coordinate_t height;
	uint8_t *tga_data;
} tga_config_t;

/**
 * TGA display driver.
 *
 * Buffers image in memory which can be written to a file with
 * :c:func:`tga_Save`.
 *
 * This driver is mainly useful for testing.
 *
 * This driver supports the following data buses:
 *
 * - 4-Wire SPI.
 *
 * :See also: :c:func:`eglib_Init`.
 */
extern const display_t tga;

/**
 * Functions
 * =========
 *
 * These functions can be used exclusively with :c:type:`eglib_t` initialized
 * with :c:data:`tga`.
 */

/**
 * Saves TGA to given file path.
 *
 * :See also: :c:data:`tga`.
 */
void tga_Save(eglib_t *eglib, char *path);

#endif