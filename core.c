#include "core.h"

void eglib_Init(
	eglib_t *eglib,
	const eglib_display_t *display,
	const eglib_comm_t *comm
) {
	eglib->display = display;
	eglib->comm = comm;
	eglib->clip.x = 0;
	eglib->clip.y = 0;
	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->comm->power_up(eglib->display->clock_ns);
	eglib->display->power_up();
}

void eglib_PowerDown(eglib_t *eglib) {
	eglib->comm->power_down();
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