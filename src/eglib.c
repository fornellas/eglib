#include "eglib.h"

//
// HAL
//

// 4-Wire SPI

static void hal_init_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.hal->init(&eglib->drivers.four_wire_spi.hal_config);
}

static void hal_sleep_in_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.hal->sleep_in(&eglib->drivers.four_wire_spi.hal_config);
}

static void hal_sleep_out_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.hal->sleep_out(&eglib->drivers.four_wire_spi.hal_config);
}

//
// Display
//

// 4-Wire SPI

static void display_init_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.display->init(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config
	);
}

static void display_sleep_in_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.display->sleep_in(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config
	);
}

static void display_sleep_out_4wire_spi(eglib_t *eglib) {
	eglib->drivers.four_wire_spi.display->sleep_out(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config
	);
}

static void display_get_dimension_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	eglib->drivers.four_wire_spi.display->get_dimension(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config,
		width, height
	);
}

static void display_get_color_depth_4wire_spi(
	eglib_t *eglib,
	eglib_color_depth_t *color_depth
) {
	eglib->drivers.four_wire_spi.display->get_color_depth(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config,
		color_depth
	);
}

static void display_draw_pixel_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	eglib->drivers.four_wire_spi.display->draw_pixel(
		eglib->drivers.four_wire_spi.hal,
		&eglib->drivers.four_wire_spi.hal_config,
		eglib->drivers.four_wire_spi.display_config,
		x, y, color
	);
}

//
// Eglib
//

static void eglib_Init(eglib_t *eglib) {
	eglib->clip.x = 0;
	eglib->clip.y = 0;

	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);

	for(int i=0 ; i < sizeof(eglib->color_index) / sizeof(*eglib->color_index) ; i++) {
		eglib->color_index[i].r = 0;
		eglib->color_index[i].g = 0;
		eglib->color_index[i].b = 0;
	}

	eglib->hal.init(eglib);
	eglib->display.init(eglib);
}

void eglib_Init_4wire_spi(
	eglib_t *eglib,
	const eglib_hal_4wire_spi_t *hal,
	void *hal_config_driver,
	const eglib_display_4wire_spi_t *display,
	void *display_config
) {
	eglib->drivers.four_wire_spi.hal = hal;
	eglib->drivers.four_wire_spi.hal_config.base = display->get_hal_4wire_spi_config_base(display_config);
	eglib->drivers.four_wire_spi.hal_config.driver = hal_config_driver;
	eglib->hal.init = hal_init_4wire_spi;
	eglib->hal.sleep_in = hal_sleep_in_4wire_spi;
	eglib->hal.sleep_out = hal_sleep_out_4wire_spi;

	eglib->drivers.four_wire_spi.display = display;
	eglib->drivers.four_wire_spi.display_config = display_config;
	eglib->display.init = display_init_4wire_spi;
	eglib->display.sleep_in = display_sleep_in_4wire_spi;
	eglib->display.sleep_out = display_sleep_out_4wire_spi;
	eglib->display.get_dimension = display_get_dimension_4wire_spi;
	eglib->display.get_color_depth = display_get_color_depth_4wire_spi;
	eglib->display.draw_pixel = display_draw_pixel_4wire_spi;

	eglib_Init(eglib);
}

void eglib_SleepIn(eglib_t *eglib) {
	eglib->hal.sleep_in(eglib);
	eglib->display.sleep_in(eglib);
}

void eglib_SleepOut(eglib_t *eglib) {
	eglib->hal.sleep_out(eglib);
	eglib->display.sleep_out(eglib);
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display.get_dimension(eglib, &width, &heigh);

	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display.get_dimension(eglib, &width, &heigh);

	return heigh;
}

void eglib_SetClipRange(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_coordinate_t width,
	eglib_coordinate_t height
) {
	eglib->clip.x = x;
	eglib->clip.y = y;
	eglib->clip.width = width;
	eglib->clip.height = height;
}

bool eglib_IsPixelClipped(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y
) {
	if(x < eglib->clip.x)
		return true;
	if(x > (eglib->clip.x + eglib->clip.width))
		return true;
	if(y < eglib->clip.y)
		return true;
	if(y > (eglib->clip.y + eglib->clip.height))
		return true;
	return false;
}

void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	eglib_color_channel_t r,
	eglib_color_channel_t g,
	eglib_color_channel_t b
) {
	eglib->color_index[idx].r = r;
	eglib->color_index[idx].g = g;
	eglib->color_index[idx].b = b;
}