#include "eglib.h"

void eglib_Init(
	eglib_t *eglib,
	const eglib_hal_t *hal,
	void *hal_driver_config_ptr,
	const eglib_display_t *display,
	void *display_config_ptr
) {
	eglib->hal = hal;
	switch(hal->bus) {
		case EGLIB_HAL_BUS_FOUR_WIRE_SPI:
			eglib->hal_config.comm.four_wire_spi = display->comm.four_wire_spi;
			break;
		case EGLIB_HAL_BUS_I2C:
			eglib->hal_config.comm.i2c = display->comm.i2c;
			break;
	}
	eglib->hal_config.driver_config_ptr = hal_driver_config_ptr;

	eglib->display = display;
	eglib->display_config_ptr = display_config_ptr;

	eglib->clip.x = 0;
	eglib->clip.y = 0;

	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);

	for(size_t i=0 ; i < sizeof(eglib->color_index) / sizeof(*eglib->color_index) ; i++) {
		eglib->color_index[i].r = 0;
		eglib->color_index[i].g = 0;
		eglib->color_index[i].b = 0;
	}

	eglib->hal->init(eglib);
	eglib->display->init(eglib);
}

void eglib_SleepIn(eglib_t *eglib) {
	eglib->hal->sleep_in(eglib);
	eglib->display->sleep_in(eglib);
}

void eglib_SleepOut(eglib_t *eglib) {
	eglib->hal->sleep_out(eglib);
	eglib->display->sleep_out(eglib);
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

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