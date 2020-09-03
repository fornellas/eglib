#include "eglib.h"

static void default_display_power_up(void *display_config) {}
static void default_display_power_down(void *display_config) {}
static void default_display_get_dimension(void *display_config, eglib_coordinate_t *width, eglib_coordinate_t*height) {}
static void default_display_draw_pixel(void *display_config, eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color) {}

static void default_comm_power_up(void *comm_config) {}
static void default_comm_power_down(void *comm_config) {}
static void default_comm_delay(void *comm_config, uint16_t microseconds) {}
static void default_comm_set_reset(void *comm_config, uint8_t state) {}
static void default_comm_set_cd(void *comm_config, uint8_t state) {}
static void default_comm_set_cs(void *comm_config, uint8_t state) {}
static void default_comm_send_byte(void *comm_config, uint8_t state) {}

void eglib_Init(
	eglib_t *eglib,
	const eglib_display_t *display,
	void *display_config,
	const eglib_comm_t *comm,
	void *comm_config
) {
	eglib->display = *display;
	eglib->display_config = display_config;
	if(NULL == eglib->display.power_up)
		eglib->display.power_up = default_display_power_up;
	if(NULL == eglib->display.power_down)
		eglib->display.power_down = default_display_power_down;
	if(NULL == eglib->display.get_dimension)
		eglib->display.get_dimension = default_display_get_dimension;
	if(NULL == eglib->display.draw_pixel)
		eglib->display.draw_pixel = default_display_draw_pixel;

	eglib->comm = *comm;
	eglib->comm_config = comm_config;
	if(NULL == eglib->comm.power_up)
		eglib->comm.power_up = default_comm_power_up;
	if(NULL == eglib->comm.power_down)
		eglib->comm.power_down = default_comm_power_down;
	if(NULL == eglib->comm.delay)
		eglib->comm.delay = default_comm_delay;
	if(NULL == eglib->comm.set_reset)
		eglib->comm.set_reset = default_comm_set_reset;
	if(NULL == eglib->comm.set_cd)
		eglib->comm.set_cd = default_comm_set_cd;
	if(NULL == eglib->comm.set_cs)
		eglib->comm.set_cs = default_comm_set_cs;
	if(NULL == eglib->comm.send_byte)
		eglib->comm.send_byte = default_comm_send_byte;

	eglib->clip.x = 0;
	eglib->clip.y = 0;
	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->comm.power_up(eglib->comm_config);
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