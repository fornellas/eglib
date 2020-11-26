#include "eglib.h"
#include "eglib/display.h"

void eglib_Init(
	eglib_t *eglib,
	const hal_t *hal,
	void *hal_driver_config_ptr,
	const display_t *display,
	void *display_config_ptr
) {
	eglib->hal = hal;
	eglib->hal_config_ptr = hal_driver_config_ptr;
	eglib->hal_comm_active = false;
	eglib->hal_i2c_send_slave_addr = 0;

	eglib->display = display;
	eglib->display_config_ptr = display_config_ptr;
	eglib->display_refreshing = false;

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