#include "eglib.h"

//
// HAL
//

// 4-Wire SPI

static void hal_power_up_4wire_spi(eglib_t *eglib) {
	((eglib_hal_4wire_spi_t *)eglib->hal)->power_up(&eglib->hal_config.four_wire_spi);
}

static void hal_power_down_4wire_spi(eglib_t *eglib) {
	((eglib_hal_4wire_spi_t *)eglib->hal)->power_down(&eglib->hal_config.four_wire_spi);
}

//
// Display
//

// 4-Wire SPI

static void display_power_up_4wire_spi(eglib_t *eglib) {
	((eglib_display_4wire_spi_t *)eglib->	display)->power_up(
		(eglib_hal_4wire_spi_t *)eglib->hal,
		&eglib->hal_config.four_wire_spi,
		eglib->display_config
	);
}

static void display_power_down_4wire_spi(eglib_t *eglib) {
	((eglib_display_4wire_spi_t *)eglib->display)->power_down(
		(eglib_hal_4wire_spi_t *)eglib->hal,
		&eglib->hal_config.four_wire_spi,
		eglib->display_config
	);
}

static void display_get_dimension_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	((eglib_display_4wire_spi_t *)eglib->display)->get_dimension(
		(eglib_hal_4wire_spi_t *)eglib->hal,
		&eglib->hal_config.four_wire_spi,
		eglib->display_config,
		width, height
	);
}

static void display_get_color_depth_4wire_spi(
	eglib_t *eglib,
	eglib_color_depth_t *color_depth
) {
	((eglib_display_4wire_spi_t *)eglib->display)->get_color_depth(
		(eglib_hal_4wire_spi_t *)eglib->hal,
		&eglib->hal_config.four_wire_spi,
		eglib->display_config,
		color_depth
	);
}

static void display_draw_pixel_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	((eglib_display_4wire_spi_t *)eglib->display)->draw_pixel(
		(eglib_hal_4wire_spi_t *)eglib->hal,
		&eglib->hal_config.four_wire_spi,
		eglib->display_config,
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
}

void eglib_Init_4wire_spi(
	eglib_t *eglib,
	const eglib_hal_4wire_spi_t *hal,
	void *hal_config_driver,
	const eglib_display_4wire_spi_t *display,
	void *display_config
) {
	eglib->hal = hal;
	eglib->hal_config.four_wire_spi.base = display->get_hal_4wire_spi_config_base(display_config);
	eglib->hal_config.four_wire_spi.driver = hal_config_driver;
	eglib->hal_power_up = hal_power_up_4wire_spi;
	eglib->hal_power_down = hal_power_down_4wire_spi;

	eglib->display = display;
	eglib->display_config = display_config;
	eglib->display_power_up = display_power_up_4wire_spi;
	eglib->display_power_down = display_power_down_4wire_spi;
	eglib->display_get_dimension = display_get_dimension_4wire_spi;
	eglib->display_get_color_depth = display_get_color_depth_4wire_spi;
	eglib->display_draw_pixel = display_draw_pixel_4wire_spi;

	eglib_Init(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->hal_power_up(eglib);
	eglib->display_power_up(eglib);
}

void eglib_PowerDown(eglib_t *eglib) {
	eglib->hal_power_down(eglib);
	eglib->display_power_down(eglib);
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display_get_dimension(eglib, &width, &heigh);

	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display_get_dimension(eglib, &width, &heigh);

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