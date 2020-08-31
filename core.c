#include "core.h"

void eglib_Init(
	eglib_t *eglib,
	eglib_display_t *display,
	eglib_hardware_t *hardware
) {
	eglib->display = display;
	eglib->hardware = hardware;
	eglib->clip.x = 0;
	eglib->clip.y = 0;
	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->hardware->power_up(eglib->display->clock_ns);
	eglib->display->power_up();
}

void eglib_PowerDown(eglib_t *eglib) {
	eglib->hardware->power_down();
	eglib->display->power_down();
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display->get_dimension(&width, &heigh);
	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display->get_dimension(&width, &heigh);
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

void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	eglib_color_channel_t r,
	eglib_color_channel_t g,
	eglib_color_channel_t b) {
	eglib->color_index[idx].r = r;
	eglib->color_index[idx].g = g;
	eglib->color_index[idx].b = b;
}