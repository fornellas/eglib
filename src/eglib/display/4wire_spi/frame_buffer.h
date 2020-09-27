#ifndef EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H
#define EGLIB_DISPLAY_4WIRE_SPI_FRAME_BUFFER_H

#include "../4wire_spi.h"
#include "../../../eglib.h"

// eglib_display_4wire_spi_t send_buffer() helpers

void eglib_display_4wire_spi_frame_buffer_send_draw_pixel_1bit_paged(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display, void *display_config_ptr,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

void eglib_display_4wire_spi_frame_buffer_send_draw_pixel_18bit_565_rgb(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display, void *display_config_ptr,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

void eglib_display_4wire_spi_frame_buffer_send_draw_pixel_24bit_rgb(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display, void *display_config_ptr,
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

extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_frame_buffer;

void eglib_display_4wire_spi_frame_send_buffer(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

#endif