#ifndef EGLIB_HAL_STDOUT_NONE_H
#define EGLIB_HAL_STDOUT_NONE_H

#include "../../hal.h"

/**
 * Driver
 * ======
 */

/**
 * 4-Wire SPI HAL driver that prints communication to stdout.
 *
 * This is useful for testing only.
 *
 * :See also: :c:func:`eglib_Init`.
 */
extern const hal_t four_wire_spi_stdout;

#endif