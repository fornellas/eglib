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

void st7789_SetDisplayInversion(eglib_t *eglib, bool inversion);

void st7789_SetIdleMode(eglib_t *eglib, bool idle);

#endif