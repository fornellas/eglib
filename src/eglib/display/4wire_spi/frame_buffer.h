#ifndef EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H
#define EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H

#include "../4wire_spi.h"
#include "../../../eglib.h"

void eglib_display_4wire_spi_frame_buffer_send_buffer_1bit_paged(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

void eglib_display_4wire_spi_frame_buffer_send_buffer_18bit_565_rgb(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

void eglib_display_4wire_spi_frame_buffer_send_buffer_24bit_rgb(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

typedef struct {
	// The display driver to frame buffer
	const eglib_display_4wire_spi_t *display;
	void *display_config_ptr;
	// Pointer to buffer, set to NULL
	void *buffer;
} eglib_display_4wire_spi_frame_buffer_config_t;

void eglib_display_4wire_spi_frame_buffer_display_init(
	eglib_display_4wire_spi_t *display_frame_buffer,
	const eglib_display_4wire_spi_t *display
);

void eglib_display_4wire_spi_frame_buffer_config_init(
	eglib_display_4wire_spi_frame_buffer_config_t *frame_buffer_config,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr
);

void eglib_display_4wire_spi_frame_buffer_send(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

#endif