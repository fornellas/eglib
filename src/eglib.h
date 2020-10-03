#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct _eglib_struct;
typedef struct _eglib_struct eglib_t;

// HAL

#include "eglib/hal/4wire_spi.h"

// Display

#include "eglib/display/types.h"
#include "eglib/display/4wire_spi.h"

// Eglib

struct _eglib_struct {
	// Drivers
	union {
		struct {
			const eglib_hal_4wire_spi_t *hal;
			eglib_hal_4wire_spi_config_t hal_config;
			const eglib_display_4wire_spi_t *display;
			void *display_config_ptr;
		} four_wire_spi;
	} drivers;
	// Common HAL driver interface wrappers
	struct {
		void (*init)(eglib_t *eglib);
		void (*sleep_in)(eglib_t *eglib);
		void (*sleep_out)(eglib_t *eglib);
	} hal;
	// Common Display driver interface wrappers
	struct {
		void (*init)(eglib_t *eglib);
		void (*sleep_in)(eglib_t *eglib);
		void (*sleep_out)(eglib_t *eglib);
		void (*get_dimension)(
			eglib_t *eglib,
			eglib_coordinate_t *width,
			eglib_coordinate_t *height
		);
		void (*get_color_depth)(
			eglib_t *eglib,
			eglib_color_depth_t *color_depth
		);
		void (*draw_pixel)(
			eglib_t *eglib,
			eglib_coordinate_t x,
			eglib_coordinate_t y,
			eglib_color_t color
		);
	} display;
	// Drawing
	struct {
		eglib_coordinate_t x;
		eglib_coordinate_t y;
		eglib_coordinate_t width;
		eglib_coordinate_t height;
	} clip;
	eglib_color_t color_index[4];
};

//  4WireSPI

void eglib_Init_4WireSPI(
	eglib_t *eglib,
	const eglib_hal_4wire_spi_t *hal,
	void *hal_config_driver_ptr,
	const eglib_display_4wire_spi_t *display,
	void *display_config_ptr
);

const eglib_hal_4wire_spi_t *eglib_Get4WireSPIHAL(eglib_t *eglib);
eglib_hal_4wire_spi_config_t *eglib_Get4WireSPIHALConfig(eglib_t *eglib);

const eglib_display_4wire_spi_t *eglib_Get4WireSPIDisplay(eglib_t *eglib);
void *eglib_Get4WireSPIDisplayConfig(eglib_t *eglib);

// Common

void eglib_SleepIn(eglib_t *eglib);
void eglib_SleepOut(eglib_t *eglib);

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib);
eglib_coordinate_t eglib_GetHeight(eglib_t *eglib);

void eglib_SetClipRange(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
);

bool eglib_IsPixelClipped(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y
);

void eglib_SetColor(
	eglib_t *eglib,
	size_t idx,
	eglib_color_channel_t r,
	eglib_color_channel_t g,
	eglib_color_channel_t b
);

// Drawing

#include "drawing.h"

#endif