#ifndef EGLIB_DISPLAY_FRAME_BUFFER_H
#define EGLIB_DISPLAY_FRAME_BUFFER_H

#include "../hal.h"
#include "../../eglib.h"

void eglib_display_frame_buffer_send_buffer_18bit_565_rgb(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

void eglib_display_frame_buffer_send_buffer_24bit_rgb(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

typedef struct {
	eglib_t eglib_buffered;
	void *buffer;
} eglib_display_frame_buffer_config_t;

void eglib_Init_FrameBuffer(
	eglib_t *eglib,
	eglib_display_t *frame_buffer,
	eglib_display_frame_buffer_config_t *frame_buffer_config,
	const eglib_hal_t *hal,
	void *hal_config_ptr,
	const eglib_display_t *display,
	void *display_config_ptr
);

void eglib_FrameBuffer_Send(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

#endif