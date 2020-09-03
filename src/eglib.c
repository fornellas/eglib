#include "eglib.h"

void eglib_Init(
	eglib_t *eglib,
	const eglib_display_t *display,
	void *display_config,
	const eglib_comm_t *comm,
	void *comm_config
) {
	eglib->display = *display;
	eglib->display_config = display_config;
	// TODO check for NULL function pointers and set default function

	eglib->comm = *comm;
	eglib->comm_config = comm_config;
	// TODO check for NULL function pointers and set default function

	eglib->clip.x = 0;
	eglib->clip.y = 0;
	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->comm.power_up(eglib->comm_config, eglib->display.clock_ns);
	eglib->display.power_up(eglib->display_config);
}

void eglib_PowerDown(eglib_t *eglib) {
	eglib->comm.power_down(eglib->comm_config);
	eglib->display.power_down(eglib->display_config);
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display.get_dimension(eglib->display_config, &width, &heigh);
	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display.get_dimension(eglib->display_config, &width, &heigh);
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
	eglib_color_channel_t b) {
	eglib->color_index[idx].r = r;
	eglib->color_index[idx].g = g;
	eglib->color_index[idx].b = b;
}