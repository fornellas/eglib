#include "eglib.h"

//
// HAL
//

// 4-Wire SPI

static void hal_power_up_4wire_spi(eglib_t *eglib) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)(eglib->hal);

	hal_4wire_spi->power_up(eglib->hal_config);
}

static void hal_power_down_4wire_spi(eglib_t *eglib) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)(eglib->hal);

	hal_4wire_spi->power_down(eglib->hal_config);
}

// I2C

static void hal_power_up_i2c(eglib_t *eglib) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)(eglib->hal);
	display_i2c = (eglib_display_i2c_t *)(eglib->display);

	display_i2c->power_up(hal_i2c, eglib->hal_config, eglib->display_config);
}

static void hal_power_down_i2c(eglib_t *eglib) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)(eglib->hal);
	display_i2c = (eglib_display_i2c_t *)(eglib->display);

	display_i2c->power_down(hal_i2c, eglib->hal_config, eglib->display_config);
}

//
// Display
//

// 4-Wire SPI

static void display_power_up_4wire_spi(eglib_t *eglib) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;
	eglib_display_4wire_spi_t *display_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)eglib->hal;
	display_4wire_spi = (eglib_display_4wire_spi_t *)eglib->display;

	display_4wire_spi->power_up(
		hal_4wire_spi, eglib->hal_config,
		eglib->display_config
	);
}

static void display_power_down_4wire_spi(eglib_t *eglib) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;
	eglib_display_4wire_spi_t *display_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)eglib->hal;
	display_4wire_spi = (eglib_display_4wire_spi_t *)eglib->display;

	display_4wire_spi->power_down(
		hal_4wire_spi, eglib->hal_config,
		eglib->display_config
	);
}

static void display_get_dimension_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;
	eglib_display_4wire_spi_t *display_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)eglib->hal;
	display_4wire_spi = (eglib_display_4wire_spi_t *)eglib->display;

	display_4wire_spi->get_dimension(
		hal_4wire_spi, eglib->hal_config,
		eglib->display_config,
		width, height
	);
}

static void display_draw_pixel_4wire_spi(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	eglib_hal_4wire_spi_t *hal_4wire_spi;
	eglib_display_4wire_spi_t *display_4wire_spi;

	hal_4wire_spi = (eglib_hal_4wire_spi_t *)eglib->hal;
	display_4wire_spi = (eglib_display_4wire_spi_t *)eglib->display;

	display_4wire_spi->draw_pixel(
		hal_4wire_spi, eglib->hal_config,
		eglib->display_config,
		x, y, color
	);
}

// I2C

static void display_power_up_i2c(eglib_t *eglib) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)eglib->hal;
	display_i2c = (eglib_display_i2c_t *)eglib->display;

	display_i2c->power_up(
		hal_i2c, eglib->hal_config,
		eglib->display_config
	);
}

static void display_power_down_i2c(eglib_t *eglib) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)eglib->hal;
	display_i2c = (eglib_display_i2c_t *)eglib->display;

	display_i2c->power_down(
		hal_i2c, eglib->hal_config,
		eglib->display_config
	);
}

static void display_get_dimension_i2c(
	eglib_t *eglib,
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)eglib->hal;
	display_i2c = (eglib_display_i2c_t *)eglib->display;

	display_i2c->get_dimension(
		hal_i2c, eglib->hal_config,
		eglib->display_config,
		width, height
	);
}

static void display_draw_pixel_i2c(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	eglib_hal_i2c_t *hal_i2c;
	eglib_display_i2c_t *display_i2c;

	hal_i2c = (eglib_hal_i2c_t *)eglib->hal;
	display_i2c = (eglib_display_i2c_t *)eglib->display;

	display_i2c->draw_pixel(
		hal_i2c, eglib->hal_config,
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
	const eglib_hal_4wire_spi_t *hal_4wire_spi, void *hal_4wire_spi_config,
	const eglib_display_4wire_spi_t *display_4wire_spi, void *display_4wire_spi_config
) {
	eglib->hal = (void *)hal_4wire_spi;
	eglib->hal_config = hal_4wire_spi_config;
	eglib->hal_power_up = hal_power_up_4wire_spi;
	eglib->hal_power_down = hal_power_down_4wire_spi;

	eglib->display = (void *)display_4wire_spi;
	eglib->display_config = display_4wire_spi_config;
	eglib->display_power_up = display_power_up_4wire_spi;
	eglib->display_power_down = display_power_down_4wire_spi;
	eglib->display_get_dimension = display_get_dimension_4wire_spi;
	eglib->display_draw_pixel = display_draw_pixel_4wire_spi;

	eglib_Init(eglib);
}

void eglib_Init_i2c(
	eglib_t *eglib,
	const eglib_hal_i2c_t *hal_i2c, void *hal_i2c_config,
	const eglib_display_i2c_t *display_i2c, void *display_i2c_config
) {
	eglib->hal = (void *)hal_i2c;
	eglib->hal_config = hal_i2c_config;
	eglib->hal_power_up = hal_power_up_i2c;
	eglib->hal_power_down = hal_power_down_i2c;

	eglib->display = (void *)display_i2c;
	eglib->display_config = display_i2c_config;
	eglib->display_power_up = display_power_up_i2c;
	eglib->display_power_down = display_power_down_i2c;
	eglib->display_get_dimension = display_get_dimension_i2c;
	eglib->display_draw_pixel = display_draw_pixel_i2c;

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