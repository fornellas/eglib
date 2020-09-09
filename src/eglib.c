#include "eglib.h"

//
// HAL
//

static void default_hal_power_up(void *hal_config) {
	(void)hal_config;
}

static void default_hal_power_down(void *hal_config) {
	(void)hal_config;
}

static void default_hal_delay_ms(void *hal_config, uint32_t ms) {
	(void)hal_config;
	(void)ms;
}

static void default_hal_set_reset(void *hal_config, uint8_t state) {
	(void)hal_config;
	(void)state;
}

static void default_hal_set_cd(void *hal_config, uint8_t state) {
	(void)hal_config;
	(void)state;
}

static void default_hal_set_cs(void *hal_config, uint8_t state) {
	(void)hal_config;
	(void)state;
}

static void default_hal_send_byte(void *hal_config, uint8_t state) {
	(void)hal_config;
	(void)state;
}

//
// Display
//

static void default_display_power_up(eglib_hal_t *hal, void *hal_config, void *display_config) {
	(void)hal;
	(void)hal_config;
	(void)display_config;
}

static void default_display_power_down(eglib_hal_t *hal, void *hal_config, void *display_config) {
	(void)hal;
	(void)hal_config;
	(void)display_config;
}

static void default_display_get_dimension(eglib_hal_t *hal, void *hal_config, void *display_config, eglib_coordinate_t *width, eglib_coordinate_t*height) {
	(void)hal;
	(void)hal_config;
	(void)display_config;
	(void)width;
	(void)height;
}
static void default_display_draw_pixel(eglib_hal_t *hal, void *hal_config, void *display_config, eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color) {
	(void)hal;
	(void)hal_config;
	(void)display_config;
	(void)x;
	(void)y;
	(void)color;
}

//
// Eglib
//

void eglib_Init(
	eglib_t *eglib,
	const eglib_hal_t *hal, void *hal_config,
	const eglib_display_t *display, void *display_config
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

	eglib->hal = *hal;
	eglib->hal_config = hal_config;
	if(NULL == eglib->hal.power_up)
		eglib->hal.power_up = default_hal_power_up;
	if(NULL == eglib->hal.power_down)
		eglib->hal.power_down = default_hal_power_down;
	if(NULL == eglib->hal.delay_ms)
		eglib->hal.delay_ms = default_hal_delay_ms;
	if(NULL == eglib->hal.set_reset)
		eglib->hal.set_reset = default_hal_set_reset;
	if(NULL == eglib->hal.set_cd)
		eglib->hal.set_cd = default_hal_set_cd;
	if(NULL == eglib->hal.set_cs)
		eglib->hal.set_cs = default_hal_set_cs;
	if(NULL == eglib->hal.send_byte)
		eglib->hal.send_byte = default_hal_send_byte;

	eglib->clip.x = 0;
	eglib->clip.y = 0;
	eglib->clip.width = eglib_GetWidth(eglib);
	eglib->clip.height = eglib_GetHeight(eglib);
}

void eglib_PowerUp(eglib_t *eglib) {
	eglib->hal.power_up(eglib->hal_config);
	eglib->display.power_up(&eglib->hal, eglib->hal_config, eglib->display_config);
}

void eglib_PowerDown(eglib_t *eglib) {
	eglib->hal.power_down(eglib->hal_config);
	eglib->display.power_down(&eglib->hal, eglib->hal_config, eglib->display_config);
}

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display.get_dimension(&eglib->hal, eglib->hal_config, eglib->display_config, &width, &heigh);
	return width;
}

eglib_coordinate_t eglib_GetHeight(eglib_t *eglib) {
	eglib_coordinate_t width, heigh;
	eglib->display.get_dimension(&eglib->hal, eglib->hal_config, eglib->display_config, &width, &heigh);
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