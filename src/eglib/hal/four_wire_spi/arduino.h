#ifndef EGLIB_HAL_FOUR_WIRE_SPI_ARDUINO_H
#define EGLIB_HAL_FOUR_WIRE_SPI_ARDUINO_H

#include "../../hal.h"
#include "Arduino.h"

#include <SPI.h>

/**
 * Configuration
 * =============
 */

/**
 * Configuration for :c:data:`four_wire_spi_arduino`.
 *
 * :See also: :c:func:`eglib_Init`.
 * :See also: `libopencm3 <http://libopencm3.org/>`_ documentation.
 */
typedef struct {
	SPIClass spi;
} four_wire_spi_arduino_config_t;

/**
 * Driver
 * ======
 */

/**
 * 4-Wire SPI HAL driver for `Arduino <https://www.arduino.cc/>`_.
 *
 * :See also: :c:func:`eglib_Init`.
 */
extern const hal_t four_wire_spi_arduino;

#endif