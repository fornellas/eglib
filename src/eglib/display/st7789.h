#ifndef EGLIB_DISPLAY_ST7789_H
#define EGLIB_DISPLAY_ST7789_H

#include "../../eglib.h"
#include <stdbool.h>

//
// st7789_config_t
//

typedef enum {
	ST7789_COLOR_12_BIT,
	ST7789_COLOR_16_BIT,
	ST7789_COLOR_18_BIT,
} st7789_color_t;

typedef enum {
	ST7789_PAGE_ADDRESS_TOP_TO_BOTTOM,
	ST7789_PAGE_ADDRESS_BOTTOM_TO_TOP,
} st7789_page_address_t;

typedef enum {
	ST7789_COLUMN_ADDRESS_LEFT_TO_RIGHT,
	ST7789_COLUMN_ADDRESS_RIGHT_TO_LEFT,
} st7789_colum_address_t;

typedef enum {
	ST7789_PAGE_COLUMN_ORDER_NORMAL,
	ST7789_PAGE_COLUMN_ORDER_REVERSE,
} st7789_page_colum_order_t;

typedef enum {
	ST7789_VERTICAL_REFRESH_TOP_TO_BOTTOM,
	ST7789_VERTICAL_REFRESH_BOTTOM_TO_TOP,
} st7789_vertical_refresh_t;

typedef enum {
	ST7789_HORIZONTAL_REFRESH_LEFT_TO_RIGHT,
	ST7789_HORIZONTAL_REFRESH_RIGHT_TO_LEFT,
} st7789_horizontal_refresh_t;

typedef struct {
	coordinate_t width;
	coordinate_t height;
	st7789_color_t color : 2;
	st7789_page_address_t page_address : 1;
	st7789_colum_address_t colum_address : 1;
	st7789_page_colum_order_t page_column_order : 1;
	st7789_vertical_refresh_t vertical_refresh : 1;
	st7789_horizontal_refresh_t horizontal_refresh : 1;
} st7789_config_t;

//
// display_t
//

extern const display_t st7789;

//
// Custom functions
//

void st7789_set_display_inversion(eglib_t *eglib, bool inversion);

void st7789_set_idle_mode(eglib_t *eglib, bool idle);

// void st7789_write_display_brightness(eglib_t *eglib, uint8_t brightness);
// #define ST7789_WRITE_DISPLAY_BRIGHTNESS 0x51

// void st7789_set_brightness_control(
// 	eglib_t *eglib,
// 	bool brightness_control_block,
// 	bool display_dimming,
// 	bool backlight_control
// );
// #define ST7789_WRITE_CTRL_DISPLAY 0x53

// #define ST7789_WRITE_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL_AND_COLOR_ENHANCEMENT 0x55
// #define ST7789_WRITE_CABC_MINIMUM_BRIGHTNESS 0x5e

// #define ST7789_PARTIAL_DISPLAY_MODE_ON 0x12
// #define ST7789_NORMAL_DISPLAY_MODE_ON 0x13  // partial mode off
// #define ST7789_PARTIAL_AREA 0x30

// #define ST7789_VERTICAL_SCROLLING_DEFINITION 0x33
// #define ST7789_VERTICAL_SCROLL_START_ADDRESS_OF_RAM 0x37

// #define ST7789_TEARING_EFFECT_LINE_OFF 0x34
// #define ST7789_TEARING_EFFECT_LINE_ON 0x35
// #define ST7789_SET_TEAR_SCANLINE 0x44

// #define ST7789_GAMMA_SET 0x26

#endif