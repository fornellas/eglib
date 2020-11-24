#ifndef EGLIB_DISPLAY_H
#define EGLIB_DISPLAY_H

struct _display_struct;
typedef struct _display_struct display_t;

#include "../eglib.h"
#include "hal.h"
#include "types.h"

struct _display_struct {
	struct {
		hal_four_wire_spi_config_comm_t *four_wire_spi;
		hal_i2c_config_comm_t *i2c;
	} comm;
	void (*init)(eglib_t *eglib);
	void (*sleep_in)(eglib_t *eglib);
	void (*sleep_out)(eglib_t *eglib);
	void (*get_dimension)(
		eglib_t *eglib,
		coordinate_t *width,
		coordinate_t *height
	);
	void (*get_pixel_format)(eglib_t *eglib, pixel_format_t *pixel_format);
	void (*draw_pixel_color)(
		eglib_t *eglib,
		coordinate_t x,
		coordinate_t y,
		color_t color
	);
	void (*send_buffer)(
		eglib_t *eglib,
		void *buffer,
		coordinate_t x, coordinate_t y,
		coordinate_t width, coordinate_t height
	);
	bool (*refresh)(eglib_t *eglib);
};

#define display_GetConfig(eglib) ((eglib)->display_config_ptr)

#define display_GetHalFourWireSpiConfigComm(eglib) (\
	(eglib)->display->comm.four_wire_spi \
)
#define display_GetHalI2cConfigComm(eglib) (\
	(eglib)->display->comm.i2c \
)

#define display_GetI2c7bitSlaveAddr(eglib, dc) \
	(display_GetHalI2cConfigComm(eglib)->get_7bit_slave_addr(eglib, dc))

#define display_I2cSend(eglib, i2c_write, dc, bytes, length) \
	(display_GetHalI2cConfigComm(eglib)->send(eglib, i2c_write, dc, bytes, length))

#define display_GetDimension(eglib, width, height) ( \
	(eglib)->display->get_dimension(eglib, width, height) \
)
#define display_DrawPixelColor(eglib, x, y, color) ( \
	(eglib)->display->draw_pixel_color(eglib, x, y, color) \
)

#define eglib_Refresh(eglib) ((eglib)->display->refresh(eglib))

#endif