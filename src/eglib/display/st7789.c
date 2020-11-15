#include "st7789.h"
#include "frame_buffer.h"

#define ST7789_RESX_TRW_MS 10 // Reset pulse duration
#define ST7789_RESX_TRT_MS 120 // Reset cancel

#define ST7789_SWRESET 0x01
#define ST7789_SWRESET_DELAY_MS 5
#define ST7789_SWRESET_DELAY_SLEEP_OUT_MS 120
#define ST7789_SLPOUT 0x11
#define ST7789_SLPOUT_DELAY_MS 5
#define ST7789_SLPOUT_DELAY_SLEEP_IN_MS 120
#define ST7789_COLMOD 0x3A
#define ST7789_COLMOD_RGB_65K (1<<6|1<<4)  // 0x50
#define ST7789_COLMOD_RGB_262K (1<<6|1<<5)  // 0x60
#define ST7789_COLMOD_COLOR_12BIT (1<<1|1)  // 0x03
#define ST7789_COLMOD_COLOR_16BIT (1<<2|1)  // 0x05
#define ST7789_COLMOD_COLOR_16BIT_WRITE (ST7789_COLMOD_RGB_65K|ST7789_COLMOD_COLOR_16BIT)
#define ST7789_COLMOD_COLOR_18BIT (1<<2|1<<1)  // 0x06
#define ST7789_COLMOD_COLOR_READ (ST7789_COLMOD_RGB_262K|ST7789_COLMOD_COLOR_18BIT)
#define ST7789_COLMOD_COLOR_16M (1<<2|1<<1|1)  // 0x07
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_DISPON 0x29
#define ST7789_NORON 0x13
#define ST7789_RAMWR 0x2C
#define ST7789_MADCTL 0x36
#define ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM 0
#define ST7789_MADCTL_PAGE_ADDRESS_ORDER_BOTTOM_TO_TOP (1<<7)
#define ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT 0
#define ST7789_MADCTL_COLUMN_ADDRESS_ORDER_RIGHT_TO_LEFT (1<<6)
#define ST7789_MADCTL_PAGE_COLUMN_ORDER_NORMAL 0
#define ST7789_MADCTL_PAGE_COLUMN_ORDER_REVERSE (1<<5)
#define ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM 0
#define ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_BOTTOM_TO_TOP (1<<4)
#define ST7789_MADCTL_ORDER_RGB 0
#define ST7789_MADCTL_ORDER_BGR (1<<3)
#define ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_LEFT_TO_RIGHT 0
#define ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_RIGHT_TO_LEFT 1

//
// Helpers
//

static void set_column_address(eglib_t *eglib, uint16_t x_start, uint16_t x_end) {
	uint8_t buff[4];

	hal_send_command_literal(eglib, ST7789_CASET);
	buff[0] = (x_start&0xFF00)>>8;
	buff[1] = x_start&0xFF;
	buff[2] = (x_end&0xFF00)>>8;
	buff[3] = x_end&0xFF;
	hal_send_data(eglib, buff, sizeof(buff));
}

static void set_row_address(eglib_t *eglib, uint16_t y_start, uint16_t y_end) {
	uint8_t buff[4];

	hal_send_command_literal(eglib, ST7789_RASET);
	buff[0] = (y_start&0xFF00)>>8;
	buff[1] = y_start&0xFF;
	buff[2] = (y_end&0xFF00)>>8;
	buff[3] = y_end&0xFF;
	hal_send_data(eglib, buff, sizeof(buff));
}

static void convert_to_16bit(color_t *color, uint8_t buff[2]) {
	uint8_t r, g, b;

	// 16 bit: RRRRRGGG GGGBBBBB
	buff[0] = 0;
	buff[1] = 0;
	r = color->r >> (8-5);
	buff[0] |= r << 3;
	g = color->g >> (8-6);
	buff[0] |= g>>3;
	buff[1] |= g<<5;
	b = color->b >> (8-5);
	buff[1] |= b&0x1F;
}

//
// Display
//

static void init(eglib_t *eglib) {
	st7789_config_t *display_config;

	display_config = display_config(eglib);

	// Hardware reset
	hal_set_reset(eglib, 0);
	hal_delay_ms(eglib, ST7789_RESX_TRW_MS);
	hal_set_reset(eglib, 1);
	hal_delay_ms(eglib, ST7789_RESX_TRT_MS);

	// Software reset
	hal_comm_begin(eglib);
	hal_send_command_literal(eglib, ST7789_SWRESET);
	hal_comm_end(eglib);
	hal_delay_ms(eglib, ST7789_SWRESET_DELAY_MS);

	// comm begin
	hal_comm_begin(eglib);

	// Out of sleep mode
	hal_send_command_literal(eglib, ST7789_SLPOUT);
	hal_delay_ms(eglib, ST7789_SLPOUT_DELAY_SLEEP_IN_MS);

	// Set color mode
	hal_send_command_literal(eglib, ST7789_COLMOD);
	hal_send_data_literal(eglib, ST7789_COLMOD_COLOR_16BIT_WRITE);

	// Memory Data Access Control
	hal_send_command_literal(eglib, ST7789_MADCTL);
	hal_send_data_literal(
		eglib,
		ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM |
		ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT |
		ST7789_MADCTL_PAGE_COLUMN_ORDER_NORMAL |
		ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM |
		ST7789_MADCTL_ORDER_RGB |
		ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_LEFT_TO_RIGHT
	);

	// Display inversion in practice works the opposite of what the datasheet
	// says: on is off and off is on.
	hal_send_command_literal(eglib, ST7789_INVON);
	// Datasheet states NORON should be the default after sw reset, but unless
	// we explicitly set it, INVON will have no effect.
	hal_send_command_literal(eglib, ST7789_NORON);

	// Clear RAM
	set_column_address(eglib, 0, display_config->width - 1);
	set_row_address(eglib, 0, display_config->height - 1);
	hal_send_command_literal(eglib, ST7789_RAMWR);
	for(uint32_t i=0, max=display_config->width * display_config->height * 2 ; i < max ; i++)
		hal_send_data_literal(eglib, 0x00);

	// Main screen turn on
	hal_send_command_literal(eglib, ST7789_DISPON);

	hal_comm_end(eglib);
};

static void sleep_in(eglib_t *eglib) {
	// TODO
	(void)eglib;
};

static void sleep_out(eglib_t *eglib) {
	// TODO
	(void)eglib;
};

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width, coordinate_t*height
) {
	st7789_config_t *display_config;

	display_config = display_config(eglib);

	*width = display_config->width;;
	*height = display_config->height;
};

static void get_color_depth(eglib_t *eglib, color_depth_t *color_depth) {
	(void)eglib;

	*color_depth = EGLIB_COLOR_DEPTH_18BIT_565_RGB;
}

static void draw_pixel_color(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y, color_t color
) {
	uint8_t color_16bit[2];

	hal_comm_begin(eglib);

	set_column_address(eglib, x, x);
	set_row_address(eglib, y, y);

	convert_to_16bit(&color, color_16bit);

	hal_send_command_literal(eglib, ST7789_RAMWR);
	for(uint8_t i=0 ; i < sizeof(color_16bit) ; i++)
		hal_send_data_literal(eglib, color_16bit[i]);

	hal_comm_end(eglib);
};

const display_t st7789 = {
	.comm = {
		.four_wire_spi = &((hal_four_wire_spi_config_comm_t){
	    .bit_numbering = EGLIB_HAL_MSB_FIRST,
	    .cs_setup_ns = 15,
	    .cs_hold_ns = 15,
	    .cs_disable_ns = 40,
	    .dc_setup_ns = 10,
	    .dc_hold_ns = 10,
	    .sck_cycle_ns = 66,
	    .mosi_setup_ns = 10,
	    .mosi_hold_ns = 10,
		}),
		.i2c = NULL,
	},
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = frame_buffer_send_18bit_565_rgb,
};