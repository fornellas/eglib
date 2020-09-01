#ifndef EGLIB_CORE_H
#define EGLIB_CORE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
  void (*power_up)(uint16_t clock_ns);
  void (*power_down)(void);
  // void (*delay)(eglib_t *, uint16_t);
  // void (*change_reset_line)(eglib_t *, uint8_t);
  // void (*change_cd_line)(eglib_t *, uint8_t);
  // void (*change_cs_line)(eglib_t *, uint8_t);
  // void (*send_byte)(eglib_t *, uint8_t);
  // void (*repeat_1_byte)(eglib_t *, uint16_t, uint8_t);
  // void (*repeat_2_bytes)(eglib_t *, uint16_t, uint8_t[2]);
  // void (*repeat_3_bytes)(eglib_t *, uint16_t, uint8_t[3]);
  // void (*send_str)(eglib_t *, uint16_t, uint8_t *);
  // void (*send_cd_data_sequence)(eglib_t *, uint16_t, uint8_t[]);
} eglib_comm_t;

typedef int16_t eglib_coordinate_t;

typedef uint8_t eglib_color_channel_t;

typedef struct {
	eglib_color_channel_t r;
	eglib_color_channel_t g;
	eglib_color_channel_t b;
} eglib_color_t;

typedef struct {
	uint16_t clock_ns;
	void (*power_up)(void);
	void (*power_down)(void);
	void (*get_dimension)(eglib_coordinate_t *width, eglib_coordinate_t*height);
	void (*draw_pixel)(eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color);
	// UCG_MSG_DRAW_L90FX
	// UCG_MSG_DRAW_L90SE
	// UCG_MSG_DRAW_L90SE
	// UCG_MSG_SET_CLIP_BOX
	// UCG_MSG_SEND_BUFFER
	// uint8_t (*rotate)(uint8_t pos);
} eglib_display_t;

typedef struct {
	const eglib_comm_t *comm;
	const eglib_display_t *display;
	struct {
		eglib_coordinate_t x;
		eglib_coordinate_t y;
		eglib_coordinate_t width;
		eglib_coordinate_t height;
	} clip;
	eglib_color_t color_index[4];
} eglib_t;

void eglib_Init(eglib_t *eglib, const eglib_display_t *display, const eglib_comm_t *comm);

void eglib_PowerUp(eglib_t *eglib);
void eglib_PowerDown(eglib_t *eglib);

eglib_coordinate_t eglib_GetWidth(eglib_t *eglib);
eglib_coordinate_t eglib_GetHeight(eglib_t *eglib);

void eglib_SetClipRange(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y, eglib_coordinate_t width, eglib_coordinate_t height);
bool eglib_IsPixelClipped(eglib_t *eglib, eglib_coordinate_t x, eglib_coordinate_t y);

void eglib_SetColor(eglib_t *eglib, size_t idx, eglib_color_channel_t r, eglib_color_channel_t g, eglib_color_channel_t b);

#endif