#ifndef EGLIB_DISPLAY_FRAME_BUFFER_H
#define EGLIB_DISPLAY_FRAME_BUFFER_H

#include "../hal.h"
#include "../../eglib.h"

typedef struct {
	display_t frame_buffer;
	eglib_t eglib_buffered;
	void *buffer;
} frame_buffer_config_t;

void eglib_Init_FrameBuffer(
	eglib_t *eglib,
	frame_buffer_config_t *frame_buffer_config,
	const hal_t *hal,
	void *hal_config_ptr,
	const display_t *display,
	void *display_config_ptr
);

void eglib_FrameBuffer_Send(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
);

#endif