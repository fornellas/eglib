#include "frame_buffer.h"
#include <stdlib.h>

static void get_color_depth(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_color_depth_t *color_depth
);

static void get_dimension(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t *width, eglib_coordinate_t*height
);

//
// Helpers
//

// draw_to_buffer_*

static void draw_to_buffer_1bit_paged(
	void *buffer_ptr,
	eglib_coordinate_t width, eglib_coordinate_t height,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_color_t color
) {
	// TODO
}

static void draw_to_buffer_18bit_565_rgb(
	void *buffer_ptr,
	eglib_coordinate_t width, eglib_coordinate_t height,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_color_t color
) {
	// TODO
}

static void draw_to_buffer_24bit_rgb(
	void *buffer_ptr,
	eglib_coordinate_t width, eglib_coordinate_t height,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_color_t color
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	buffer += (width * y + x) * 3;
	*buffer = color.r;
	buffer++;
	*buffer = color.g;
	buffer++;
	*buffer = color.b;
}

static const void (*draw_to_buffer[EGLIB_COLOR_DEPTH_COUNT])(
	void *buffer_ptr,
	eglib_coordinate_t width, eglib_coordinate_t height,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_color_t color
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

// buffer_send_*

static void buffer_send_1bit_paged(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr,
	void *buffer_ptr
) {
	// TODO
}

static void buffer_send_18bit_565_rgb(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr,
	void *buffer_ptr
) {
	// TODO
}

static void buffer_send_24bit_rgb(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr,
	void *buffer_ptr
) {
	uint8_t *buffer = (uint8_t *)buffer_ptr;
	eglib_color_t color;
	eglib_coordinate_t width, height;

	display->get_dimension(hal, hal_config, display_config_ptr, &width, &height);

	for(eglib_coordinate_t y=0 ; y < height ; y++) {
		for(eglib_coordinate_t x=0 ; x < width ; x++) {
			color.r = *buffer;
			buffer++;
			color.g = *buffer;
			buffer++;
			color.b = *buffer;
			buffer++;
			display->draw_pixel(
				hal, hal_config, display_config_ptr,
				x, y,
				color
			);
		}
	}
}

static const void (*buffer_send[EGLIB_COLOR_DEPTH_COUNT])(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr,
	void *buffer_ptr
) = {
	[EGLIB_COLOR_DEPTH_1BIT_PAGED] = &buffer_send_1bit_paged,
	[EGLIB_COLOR_DEPTH_18BIT_565_RGB] = &buffer_send_18bit_565_rgb,
	[EGLIB_COLOR_DEPTH_24BIT_RGB] = &buffer_send_24bit_rgb,
};

//
// Display
//

static eglib_hal_4wire_spi_config_base_t *get_hal_4wire_spi_config_base(
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	return display_config->display->get_hal_4wire_spi_config_base(display_config->display_config_ptr);
}

static void init(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;
	eglib_color_depth_t color_depth;
	eglib_coordinate_t width, height;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	get_color_depth(hal, hal_config, display_config_ptr, &color_depth);
	get_dimension(hal, hal_config, display_config_ptr, &width, &height);

	display_config->buffer = calloc(1, color_bits[color_depth] * width * height / 8 );

	if(display_config->buffer == NULL)
		// FIXME error reporting
		while(1);

	display_config->display->init(hal, hal_config, display_config->display_config_ptr);
};

static void sleep_in(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->sleep_in(hal, hal_config, display_config->display_config_ptr);
};

static void sleep_out(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->sleep_out(hal, hal_config, display_config->display_config_ptr);
};

static void get_dimension(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->get_dimension(
		hal, hal_config,
		display_config->display_config_ptr,
		width, height
	);
};

static void get_color_depth(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_color_depth_t *color_depth
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->get_color_depth(
		hal, hal_config,
		display_config->display_config_ptr,
		color_depth
	);
}

static void draw_pixel(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;
	eglib_color_depth_t color_depth;
	eglib_coordinate_t width, height;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	get_color_depth(hal, hal_config, display_config_ptr, &color_depth);
	get_dimension(hal, hal_config, display_config_ptr, &width, &height);

	(draw_to_buffer[color_depth])(
		display_config->buffer,
		width, height,
		x, y,
		color
	);
};

const eglib_display_4wire_spi_t eglib_display_4wire_spi_frame_buffer = {
	.get_hal_4wire_spi_config_base = get_hal_4wire_spi_config_base,
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel = draw_pixel,
};

//
// Extra
//

void eglib_display_4wire_spi_frame_buffer_send(eglib_t *eglib) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;
	eglib_color_depth_t color_depth;
	eglib_coordinate_t width, height;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)eglib->drivers.four_wire_spi.display_config;
	eglib->display.get_color_depth(eglib, &color_depth);
	eglib->display.get_dimension(eglib, &width, &height);

	(buffer_send[color_depth])(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		display_config->display,
		display_config->display_config_ptr,
		display_config->buffer
	);
}