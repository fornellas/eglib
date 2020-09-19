#ifndef EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H
#define EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H

#include "../4wire_spi.h"

typedef struct {
	const eglib_display_4wire_spi_t *display;
	void *display_config;
	void *buffer;
} eglib_display_4wire_spi_frame_buffer_config_t;

extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_frame_buffer;

#endif