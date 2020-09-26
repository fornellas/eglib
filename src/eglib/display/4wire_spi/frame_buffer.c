#include "frame_buffer.h"

static eglib_hal_4wire_spi_config_base_t *get_hal_4wire_spi_config_base(
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	return display_config->display->get_hal_4wire_spi_config_base(display_config->display_config);
}

static void init(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->init(hal, hal_config, display_config->display_config);
};

static void sleep_in(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->sleep_in(hal, hal_config, display_config->display_config);
};

static void sleep_out(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->sleep_out(hal, hal_config, display_config->display_config);
};

static void get_dimension(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->get_dimension(hal, hal_config, display_config->display_config, width, height);
};

static void get_color_depth(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_color_depth_t *color_depth
) {
	eglib_display_4wire_spi_frame_buffer_config_t *display_config;

	display_config = (eglib_display_4wire_spi_frame_buffer_config_t *)display_config_ptr;

	display_config->display->get_color_depth(hal, hal_config, display_config->display_config, color_depth);
}

static void draw_pixel(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {

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