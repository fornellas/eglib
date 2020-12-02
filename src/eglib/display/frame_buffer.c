#include "frame_buffer.h"
#include <stdlib.h>

static void get_pixel_format(eglib_t *eglib, enum pixel_format_t *pixel_format);

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
	color_t *color
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

	*byte = ((*byte)&~(1<<bit)) | (((color->r|color->g|color->b)&0x01)<<bit);
}

static void draw_to_buffer_12bit(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t *color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;
	uint32_t bit;

	(void)height;

	bit = ((uint32_t)width * y + x) * 12;
	buffer += bit / 8;

	if(bit % 8) {
		*buffer = (*buffer & 0xf0) | (color->r & 0xf0) >> 4;
		buffer++;
		*buffer = color->g & 0xf0;
		*buffer |= (color->b & 0xf0) >> 4;
	} else {
		*buffer = color->r & 0xf0;
		*buffer |= (color->g & 0xf0) >> 4;
		buffer++;
		*buffer = (color->b & 0xf0) | (*buffer & 0x0f);
	}
}

static void draw_to_buffer_16bit(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t *color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	(void)height;

	buffer += (width * y + x) * 2;
	*buffer = color->r & 0xf8;
	*buffer |= color->g >> 5;
	buffer++;
	*buffer = (color->g >> 2) << 5;
	*buffer |= color->b >> 3;
}

static void draw_to_buffer_18bit_rgb_24bit(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t *color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	(void)height;

	buffer += (width * y + x) * 3;
	*buffer = color->r & ~0x03;
	buffer++;
	*buffer = color->g & ~0x03;
	buffer++;
	*buffer = color->b & ~0x03;
}

static void draw_to_buffer_24bit_rgb(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t *color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	(void)height;

	buffer += (width * y + x) * 3;
	*buffer = color->r;
	buffer++;
	*buffer = color->g;
	buffer++;
	*buffer = color->b;
}

static void (*draw_to_buffer[PIXEL_FORMAT_COUNT])(
	void *buffer_ptr,
	coordinate_t width, coordinate_t height,
	coordinate_t x, coordinate_t y,
	color_t *color
) = {
	[PIXEL_FORMAT_1BIT_BW_PAGED] = &draw_to_buffer_1bit_paged,
	[PIXEL_FORMAT_12BIT_RGB] = &draw_to_buffer_12bit,
	[PIXEL_FORMAT_16BIT_RGB] = &draw_to_buffer_16bit,
	[PIXEL_FORMAT_18BIT_RGB_24BIT] = &draw_to_buffer_18bit_rgb_24bit,
	[PIXEL_FORMAT_24BIT_RGB] = &draw_to_buffer_24bit_rgb,
};

static const uint8_t color_bits[PIXEL_FORMAT_COUNT] = {
	[PIXEL_FORMAT_1BIT_BW_PAGED] = 1,
	[PIXEL_FORMAT_12BIT_RGB] = 12,
	[PIXEL_FORMAT_16BIT_RGB] = 16,
	[PIXEL_FORMAT_18BIT_RGB_24BIT] = 24,
	[PIXEL_FORMAT_24BIT_RGB] = 24,
};

//
// Display
//

static void init(eglib_t *eglib) {
	frame_buffer_config_t *display_config;
	enum pixel_format_t pixel_format;
	coordinate_t width, height;

	display_config = eglib_GetDisplayConfig(eglib);

	get_pixel_format(eglib, &pixel_format);
	get_dimension(eglib, &width, &height);

	display_config->buffer = calloc(1, (uint32_t)color_bits[pixel_format] * width * height / 8 );

	if(display_config->buffer == NULL)
		while(1);
};

static void sleep_in(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->eglib_buffered.display.driver->sleep_in(
		&display_config->eglib_buffered
	);
};

static void sleep_out(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->eglib_buffered.display.driver->sleep_out(
		&display_config->eglib_buffered
	);
};

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width, coordinate_t*height
) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->eglib_buffered.display.driver->get_dimension(
		&display_config->eglib_buffered, width, height
	);
};

static void get_pixel_format(eglib_t *eglib, enum pixel_format_t *pixel_format) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->eglib_buffered.display.driver->get_pixel_format(
		&display_config->eglib_buffered, pixel_format
	);
}

static void draw_pixel_color(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y, color_t color
) {
	frame_buffer_config_t *display_config;
	enum pixel_format_t pixel_format;
	coordinate_t width, height;

	display_config = eglib_GetDisplayConfig(eglib);

	get_pixel_format(eglib, &pixel_format);
	get_dimension(eglib, &width, &height);

	(draw_to_buffer[pixel_format])(
		display_config->buffer,
		width, height,
		x, y,
		&color
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

static bool refresh(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	return display_config->eglib_buffered.display.driver->refresh(
		&display_config->eglib_buffered
	);
}

//
// Extra
//

eglib_t *eglib_Init_FrameBuffer(
	eglib_t *eglib,
	frame_buffer_config_t *frame_buffer_config,
	const hal_t *hal_driver, void *hal_config_ptr,
	const display_t *display_driver, void *display_config_ptr
) {
	display_t *frame_buffer;

	frame_buffer = &frame_buffer_config->frame_buffer;

	eglib_Init(
		&frame_buffer_config->eglib_buffered,
		hal_driver, hal_config_ptr,
		display_driver, display_config_ptr
	);

	frame_buffer->comm = display_driver->comm;
	frame_buffer->init = init;
	frame_buffer->sleep_in = sleep_in;
	frame_buffer->sleep_out = sleep_out;
	frame_buffer->get_dimension = get_dimension;
	frame_buffer->get_pixel_format = get_pixel_format;
	frame_buffer->draw_pixel_color = draw_pixel_color;
	frame_buffer->draw_line = display_default_draw_line;
	frame_buffer->send_buffer = send_buffer;
	frame_buffer->refresh = refresh;

	frame_buffer_config->buffer = NULL;

	eglib_Init(
		eglib,
		hal_driver, hal_config_ptr,
		frame_buffer, frame_buffer_config
	);

	return &frame_buffer_config->eglib_buffered;
}

void eglib_FrameBuffer_Send(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->eglib_buffered.display.driver->send_buffer(
		&display_config->eglib_buffered,
		display_config->buffer,
		x, y,
		width, height
	);
}

void frame_buffer_Free(eglib_t *eglib) {
	frame_buffer_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	free(display_config->buffer);
}