#ifndef EGLIB_H
#define EGLIB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint8_t eglib_color_channel_t;

typedef struct {
	eglib_color_channel_t r;
	eglib_color_channel_t g;
	eglib_color_channel_t b;
} eglib_color_t;

typedef int16_t eglib_coordinate_t;

typedef struct {
	void (*power_up)(void *display_config); // optional
	void (*power_down)(void *display_config); // optional
	void (*get_dimension)(void *display_config, eglib_coordinate_t *width, eglib_coordinate_t*height); // required
	void (*draw_pixel)(void *display_config, eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color); // required
	// UCG_MSG_DRAW_L90FX
	// UCG_MSG_DRAW_L90SE
	// UCG_MSG_DRAW_L90SE
	// UCG_MSG_SET_CLIP_BOX
	// UCG_MSG_SEND_BUFFER
	// uint8_t (*rotate)(uint8_t pos);
} eglib_display_t;

typedef struct {
  void (*power_up)(void *comm_config); // optional
  void (*power_down)(void *comm_config); // optional
  void (*delay)(void *comm_config, uint16_t microseconds); // required
  void (*set_reset)(void *comm_config, uint8_t state); // required
  void (*set_cd)(void *comm_config, uint8_t state); // required
  void (*set_cs)(void *comm_config, uint8_t state); // required
  void (*send_byte)(void *comm_config, uint8_t byte); // required
  // void (*repeat_send_1_byte)(void *comm_config, uint16_t, uint8_t); // optional
  // void (*repeat_send_2_bytes)(void *comm_config, uint16_t, uint8_t[2]); // optional
  // void (*repeat_send_3_bytes)(void *comm_config, uint16_t, uint8_t[3]); // optional
  // void (*send_bytes)(void *comm_config, uint16_t, uint8_t *); // optional
  // void (*send_cd_data_sequence)(void *comm_config, uint16_t, uint8_t[]); // optional
} eglib_comm_t;

typedef struct {
	eglib_display_t display;
	void *display_config;
	eglib_comm_t comm;
	void *comm_config;
	struct {
		eglib_coordinate_t x;
		eglib_coordinate_t y;
		eglib_coordinate_t width;
		eglib_coordinate_t height;
	} clip;
	eglib_color_t color_index[4];
} eglib_t;

void eglib_Init(eglib_t *eglib, const eglib_display_t *display, void *display_config, const eglib_comm_t *comm, void *comm_config);

void eglib_PowerUp(eglib_t *eglib);
void eglib_PowerDown(eglib_t *eglib);

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib);
eglib_coordinate_t eglib_GetHeight(eglib_t *eglib);

void eglib_SetClipRange(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y, eglib_coordinate_t width, eglib_coordinate_t height);
bool eglib_IsPixelClipped(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y);

void eglib_SetColor(eglib_t *eglib, size_t idx, eglib_color_channel_t r, eglib_color_channel_t g, eglib_color_channel_t b);

#include "drawing.h"

#endif