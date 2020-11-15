#include "frame_buffer.h"
#include <stdlib.h>

static void get_color_depth(eglib_t *eglib, color_depth_t *color_depth);

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width, coordinate_t*height
);

//
// Helpers
//

// draw_to_buffer_*

static void draw_to_buffer_1bit_paged(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t color
) {
	uint8_t *buffer;
	uint8_t page;
	uint8_t bit;
	uint8_t *byte;

	(void)height;

	buffer = (uint8_t *)buffer_ptr;

	page = y / 8;
	bit = y % 8;

	byte = buffer + width * page + x;

	*byte = ((*byte)&~(1<<bit)) | (((color.r|color.g|color.b)&0x01)<<bit);
}

static void draw_to_buffer_18bit_565_rgb(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t color
) {
	(void)buffer_ptr;
	(void)width;
	(void)height;
	(void)x;
	(void)y;
	(void)color;
	// TODO
}

static void draw_to_buffer_24bit_rgb(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	(void)height;

	buffer += (width * y + x) * 3;
	*buffer = color.r;
	buffer++;
	*buffer = color.g;
	buffer++;
	*buffer = color.b;
}

static void (*draw_to_buffer[EGLIB_COLOR_DEPTH_COUNT])(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t color
) = {
	[EGLIB_COLOR_DEPTH_1BIT_PAGED] = &draw_to_buffer_1bit_paged,
	[EGLIB_COLOR_DEPTH_18BIT_565_RGB] = &draw_to_buffer_18bit_565_rgb,
	[EGLIB_COLOR_DEPTH_24BIT_RGB] = &draw_to_buffer_24bit_rgb,
};

static const uint8_t color_bits[EGLIB_COLOR_DEPTH_COUNT] = {
	[EGLIB_COLOR_DEPTH_1BIT_PAGED] = 1,
	[EGLIB_COLOR_DEPTH_18BIT_565_RGB] = 18,
	[EGLIB_COLOR_DEPTH_24BIT_RGB] = 24,
};

//
// display_t send_buffer() helpers
//

void frame_buffer_send_18bit_565_rgb(
       eglib_t *eglib,
       void *buffer_ptr,
       coordinate_t x, coordinate_t y,
       coordinate_t width, coordinate_t height
) {
       (void)eglib;
       (void)buffer_ptr;
       (void)x;
       (void)y;
       (void)width;
       (void)height;
       // TODO
}

void frame_buffer_send_24bit_rgb(
	eglib_t *eglib,
	void *buffer_ptr,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;
	color_t color;
	coordinate_t y_start, y_end, x_start, x_end;

	y_start = x;
	y_end = y + height;
	x_start = x;
	x_end = x + width;

	for(y = y_start; y <= y_end ; y++) {
		for(x = x_start; x <= x_end ; x++) {
			color.r = *buffer;
			buffer++;
			color.g = *buffer;
			buffer++;
			color.b = *buffer;
			buffer++;
			display_draw_pixel_color(
				eglib,
				x, y,
				color
			);
		}
	}
}

//
// Display
//

static void init(eglib_t *eglib) {
	frame_buffer_config_t *display_config;
	color_depth_t color_depth;
	coordinate_t width, height;

	display_config = display_get_config(eglib);

	get_color_depth(eglib, &color_depth);
	get_dimension(eglib, &width, &height);

	display_config->buffer = calloc(1, color_bits[color_depth] * width * height / 8 );

	if(display_config->buffer == NULL)
		// FIXME error reporting
		while(1);
};

static void sleep_in(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = display_get_config(eglib);

	display_config->eglib_buffered.display->sleep_in(
		&display_config->eglib_buffered
	);
};

static void sleep_out(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = display_get_config(eglib);

	display_config->eglib_buffered.display->sleep_out(
		&display_config->eglib_buffered
	);
};

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width, coordinate_t*height
) {
	frame_buffer_config_t *display_config;

	display_config = display_get_config(eglib);

	display_config->eglib_buffered.display->get_dimension(
		&display_config->eglib_buffered, width, height
	);
};

static void get_color_depth(eglib_t *eglib, color_depth_t *color_depth) {
	frame_buffer_config_t *display_config;

	display_config = display_get_config(eglib);

	display_config->eglib_buffered.display->get_color_depth(
		&display_config->eglib_buffered, color_depth
	);
}

static void draw_pixel_color(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y, color_t color
) {
	frame_buffer_config_t *display_config;
	color_depth_t color_depth;
	coordinate_t width, height;

	display_config = display_get_config(eglib);

	get_color_depth(eglib, &color_depth);
	get_dimension(eglib, &width, &height);

	(draw_to_buffer[color_depth])(
		display_config->buffer,
		width, height,
		x, y,
		color
	);
};

static void send_buffer(
	eglib_t *eglib,
	void *buffer,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
) {
	(void)eglib;
	(void)buffer;
	(void)x;
	(void)y;
	(void)width;
	(void)height;
};

//
// Extra
//

void eglib_Init_FrameBuffer(
	eglib_t *eglib,
	frame_buffer_config_t *frame_buffer_config,
	const hal_t *hal, void *hal_config_ptr,
	const display_t *display, void *display_config_ptr
) {
	display_t *frame_buffer;

	frame_buffer = &frame_buffer_config->frame_buffer;

	eglib_Init(
		&frame_buffer_config->eglib_buffered,
		hal, hal_config_ptr,
		display, display_config_ptr
	);

	frame_buffer->comm = display->comm;
	frame_buffer->init = init;
	frame_buffer->sleep_in = sleep_in;
	frame_buffer->sleep_out = sleep_out;
	frame_buffer->get_dimension = get_dimension;
	frame_buffer->get_color_depth = get_color_depth;
	frame_buffer->draw_pixel_color = draw_pixel_color;
	frame_buffer->send_buffer = send_buffer;

	frame_buffer_config->buffer = NULL;

	eglib_Init(
		eglib,
		hal, hal_config_ptr,
		frame_buffer, frame_buffer_config
	);
}

void eglib_FrameBuffer_Send(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
) {
	frame_buffer_config_t *display_config;

	display_config = display_get_config(eglib);

	display_config->eglib_buffered.display->send_buffer(
		&display_config->eglib_buffered,
		display_config->buffer,
		x, y,
		width, height
	);
}