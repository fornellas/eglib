#include "st7789.h"
#include "frame_buffer.h"

//
// Timings
//

#define ST7789_RESX_PULSE_MS 10
#define ST7789_RESX_CANCEL_MS 120

//
// Commands
//

#define ST7789_NO_OPERATION 0x00

#define ST7789_SOFTWARE_RESET 0x01
#define ST7789_SOFTWARE_RESET_DELAY_MS 5
#define ST7789_SOFTWARE_RESET_SLEEP_MODE_DELAY_MS 120

#define ST7789_READ_DISPLAY_ID 0x04

#define ST7789_READ_DISPLAY_STATUS 0x09

#define ST7789_READ_DISPLAY_POWER_MODE 0x0a

#define ST7789_READ_DISPLAY_MADCTL 0x0b

#define ST7789_READ_DISPLAY_PIXEL_FORMAT 0x0c

#define ST7789_READ_DISPLAY_IMAGE_MODE 0x0d

#define ST7789_READ_DISPLAY_SIGNAL_MODE 0x0e

#define ST7789_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT 0x0f

#define ST7789_SLEEP_IN 0x10
#define ST7789_SLEEP_IN_DELAY_MS 5

#define ST7789_SLEEP_OUT 0x11
#define ST7789_SLEEP_OUT_DELAY_MS 120

#define ST7789_PARTIAL_DISPLAY_MODE_ON 0x12

#define ST7789_NORMAL_DISPLAY_MODE_ON 0x13

#define ST7789_DISPLAY_INVERSION_OFF 0x20

#define ST7789_DISPLAY_INVERSION_ON 0x21

#define ST7789_GAMMA_SET 0x26

#define ST7789_DISPLAY_OFF 0x28

#define ST7789_DISPLAY_ON 0x29

#define ST7789_COLUMN_ADDRESS_SET 0x2a

#define ST7789_ROW_ADDRESS_SET 0x2b

#define ST7789_MEMORY_WRITE 0x2c

#define ST7789_MEMORY_READ 0x2e

#define ST7789_PARTIAL_AREA 0x30

#define ST7789_VERTICAL_SCROLLING_DEFINITION 0x33

#define ST7789_TEARING_EFFECT_LINE_OFF 0x34

#define ST7789_TEARING_EFFECT_LINE_ON 0x35

#define ST7789_MEMORY_DATA_ACCESS_CONTROL 0x36
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_ADDRESS_TOP_TO_BOTTOM (0<<7)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_ADDRESS_BOTTOM_TO_TOP (1<<7)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_COLUMN_ADDRESS_LEFT_TO_RIGHT (0<<6)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_COLUMN_ADDRESS_RIGHT_TO_LEFT (1<<6)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_COLUMN_ORDER_NORMAL (0<<5)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_COLUMN_ORDER_REVERSE (1<<5)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM (0<<4)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_LINE_ADDRESS_ORDER_LCD_REFRESH_BOTTOM_TO_TOP (1<<4)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_RGB (0<<3)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_BGR (1<<3)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_DISPLAY_DATA_LATCH_DATA_ORDER_LCD_REFRESH_LEFT_TO_RIGHT (0<<0)
#define ST7789_MEMORY_DATA_ACCESS_CONTROL_DISPLAY_DATA_LATCH_DATA_ORDER_LCD_REFRESH_RIGHT_TO_LEFT (1<<0)

#define ST7789_VERTICAL_SCROLL_START_ADDRESS_OF_RAM 0x37

#define ST7789_IDLE_MODE_OFF 0x38

#define ST7789_IDLE_MODE_ON 0x39

#define ST7789_INTERFACE_PIXEL_FORMAT 0x3a
#define ST7789_INTERFACE_PIXEL_FORMAT_RGB_INTERFACE_BIT 4
#define ST7789_INTERFACE_PIXEL_FORMAT_RGB_INTERFACE_65K (5<<ST7789_INTERFACE_PIXEL_FORMAT_RGB_INTERFACE_BIT)
#define ST7789_INTERFACE_PIXEL_FORMAT_RGB_INTERFACE_262K (6<<ST7789_INTERFACE_PIXEL_FORMAT_RGB_INTERFACE_BIT)
#define ST7789_INTERFACE_PIXEL_FORMAT_COLOR_BIT 0
#define ST7789_INTERFACE_PIXEL_FORMAT_COLOR_12BIT (3<<ST7789_INTERFACE_PIXEL_FORMAT_COLOR_BIT)
#define ST7789_INTERFACE_PIXEL_FORMAT_COLOR_16BIT (5<<ST7789_INTERFACE_PIXEL_FORMAT_COLOR_BIT)
#define ST7789_INTERFACE_PIXEL_FORMAT_COLOR_18BIT (6<<ST7789_INTERFACE_PIXEL_FORMAT_COLOR_BIT)
#define ST7789_INTERFACE_PIXEL_FORMAT_COLOR_24BIT_TRUNCATED (7<<ST7789_INTERFACE_PIXEL_FORMAT_COLOR_BIT)

#define ST7789_WRITE_MEMORY_CONTINUE 0x3c

#define ST7789_READ_MEMORY_CONTINUE 0x3e

#define ST7789_SET_TEAR_SCANLINE 0x44

#define ST7789_GET_SCANLINE 0x45

#define ST7789_WRITE_DISPLAY_BRIGHTNESS 0x51

#define ST7789_READ_DISPLAY_BRIGHTNESS_VALUE 0x52

#define ST7789_WRITE_CTRL_DISPLAY 0x53
#define ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_BIT 5
#define ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_OFF (0<<ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_BIT)
#define ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_ON (1<<ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_BIT)
#define ST7789_WRITE_CTRL_DISPLAY_DIMMING_BIT 3
#define ST7789_WRITE_CTRL_DISPLAY_DIMMING_OFF (0<<ST7789_WRITE_CTRL_DISPLAY_DIMMING_BIT)
#define ST7789_WRITE_CTRL_DISPLAY_DIMMING_ON (1<<ST7789_WRITE_CTRL_DISPLAY_DIMMING_BIT)
#define ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_BIT 2
#define ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_OFF (0<<ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_BIT)
#define ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_ON (1<<ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_BIT)

#define ST7789_READ_CTRL_VALUE_DISPLAY 0x54

#define ST7789_WRITE_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL_AND_COLOR_ENHANCEMENT 0x55

#define ST7789_READ_CONTENT_ADAPTIVE_BRIGHTNESS_CONTROL_ 0x56

#define ST7789_WRITE_CABC_MINIMUM_BRIGHTNESS 0x5e

#define ST7789_READ_CABC_MINIMUM_BRIGHTNESS 0x5f

#define ST7789_READ_AUTOMATIC_BRIGHTNESS_CONTROL_SELF_DIAGNOSTIC_RESULT 0x68

#define ST7789_READ_ID1 0xda

#define ST7789_READ_ID2 0xdb

#define ST7789_READ_ID3 0xdc

//
// Helpers
//

static void set_interface_pixel_format(eglib_t *eglib) {
	st7789_config_t *display_config;
	uint8_t interface_pixel_format;

	display_config = display_get_config(eglib);

	interface_pixel_format = 0;
	switch(display_config->color) {
		case ST7789_COLOR_12_BIT:
			interface_pixel_format |= ST7789_INTERFACE_PIXEL_FORMAT_COLOR_12BIT;
			break;
		case ST7789_COLOR_16_BIT:
			interface_pixel_format |= ST7789_INTERFACE_PIXEL_FORMAT_COLOR_16BIT;
			break;
		case ST7789_COLOR_18_BIT:
			interface_pixel_format |= ST7789_INTERFACE_PIXEL_FORMAT_COLOR_18BIT;
			break;
	}
	hal_send_command_byte(eglib, ST7789_INTERFACE_PIXEL_FORMAT);
	hal_send_data_byte(eglib, interface_pixel_format);
}

static void set_memory_data_access_control(eglib_t *eglib) {
	st7789_config_t *display_config;
	uint8_t memory_data_access_control;

	display_config = display_get_config(eglib);

	memory_data_access_control = 0;
	switch(display_config->page_address) {
		case ST7789_PAGE_ADDRESS_TOP_TO_BOTTOM:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_ADDRESS_TOP_TO_BOTTOM;
			break;
		case ST7789_PAGE_ADDRESS_BOTTOM_TO_TOP:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_ADDRESS_BOTTOM_TO_TOP;
			break;
	}
	switch(display_config->colum_address) {
		case ST7789_COLUMN_ADDRESS_LEFT_TO_RIGHT:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_COLUMN_ADDRESS_LEFT_TO_RIGHT;
			break;
		case ST7789_COLUMN_ADDRESS_RIGHT_TO_LEFT:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_COLUMN_ADDRESS_RIGHT_TO_LEFT;
			break;
	}
	switch(display_config->page_column_order) {
		case ST7789_PAGE_COLUMN_ORDER_NORMAL:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_COLUMN_ORDER_NORMAL;
			break;
		case ST7789_PAGE_COLUMN_ORDER_REVERSE:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_PAGE_COLUMN_ORDER_REVERSE;
			break;
	}
	switch(display_config->vertical_refresh) {
		case ST7789_VERTICAL_REFRESH_TOP_TO_BOTTOM:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM;
			break;
		case ST7789_VERTICAL_REFRESH_BOTTOM_TO_TOP:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_LINE_ADDRESS_ORDER_LCD_REFRESH_BOTTOM_TO_TOP;
			break;
	}
	memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_RGB;
	switch(display_config->horizontal_refresh) {
		case ST7789_HORIZONTAL_REFRESH_LEFT_TO_RIGHT:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_DISPLAY_DATA_LATCH_DATA_ORDER_LCD_REFRESH_LEFT_TO_RIGHT;
			break;
		case ST7789_HORIZONTAL_REFRESH_RIGHT_TO_LEFT:
			memory_data_access_control |= ST7789_MEMORY_DATA_ACCESS_CONTROL_DISPLAY_DATA_LATCH_DATA_ORDER_LCD_REFRESH_RIGHT_TO_LEFT;
			break;
	}
	hal_send_command_byte(eglib, ST7789_MEMORY_DATA_ACCESS_CONTROL);
	hal_send_data_byte(eglib, memory_data_access_control);
}

static void set_column_address(eglib_t *eglib, uint16_t x_start, uint16_t x_end) {
	uint8_t buff[4];

	hal_send_command_byte(eglib, ST7789_COLUMN_ADDRESS_SET);
	buff[0] = (x_start&0xFF00)>>8;
	buff[1] = x_start&0xFF;
	buff[2] = (x_end&0xFF00)>>8;
	buff[3] = x_end&0xFF;
	hal_send_data(eglib, buff, sizeof(buff));
}

static void set_row_address(eglib_t *eglib, uint16_t y_start, uint16_t y_end) {
	uint8_t buff[4];

	hal_send_command_byte(eglib, ST7789_ROW_ADDRESS_SET);
	buff[0] = (y_start&0xFF00)>>8;
	buff[1] = y_start&0xFF;
	buff[2] = (y_end&0xFF00)>>8;
	buff[3] = y_end&0xFF;
	hal_send_data(eglib, buff, sizeof(buff));
}

static uint8_t get_bits_per_pixel(eglib_t *eglib) {
	st7789_config_t *display_config;

	display_config = display_get_config(eglib);

	switch(display_config->color) {
		case ST7789_COLOR_12_BIT:
			return 12;
			break;
		case ST7789_COLOR_16_BIT:
			return 16;
			break;
		case ST7789_COLOR_18_BIT:
			return 24;
			break;
		default:
			while(true);
	}
}

static void clear_memory(eglib_t *eglib) {
	st7789_config_t *display_config;
	uint32_t memory_size;

	display_config = display_get_config(eglib);

	memory_size = display_config->width * display_config->height * get_bits_per_pixel(eglib) / 8;

	set_column_address(eglib, 0, display_config->width - 1);
	set_row_address(eglib, 0, display_config->height - 1);
	hal_send_command_byte(eglib, ST7789_MEMORY_WRITE);
	for(uint32_t addr=0 ; addr < memory_size ; addr++)
		hal_send_data_byte(eglib, 0x00);
}

//
// Display
//

static void init(eglib_t *eglib) {
	// Hardware reset
	hal_set_reset(eglib, 0);
	hal_delay_ms(eglib, ST7789_RESX_PULSE_MS);
	hal_set_reset(eglib, 1);
	hal_delay_ms(eglib, ST7789_RESX_CANCEL_MS);

	// Software reset
	hal_comm_begin(eglib);
	hal_send_command_byte(eglib, ST7789_SOFTWARE_RESET);
	hal_comm_end(eglib);
	hal_delay_ms(eglib, ST7789_SOFTWARE_RESET_DELAY_MS);

	// comm begin
	hal_comm_begin(eglib);

	// Out of sleep mode
	hal_send_command_byte(eglib, ST7789_SLEEP_OUT);
	hal_delay_ms(eglib, ST7789_SLEEP_OUT_DELAY_MS);

	// Set color mode
	set_interface_pixel_format(eglib);

	// Memory Data Access Control
	set_memory_data_access_control(eglib);

	// Display inversion in practice works the opposite of what the datasheet
	// says: on is off and off is on.
	hal_send_command_byte(eglib, ST7789_DISPLAY_INVERSION_ON);
	// Datasheet states ST7789_NORMAL_DISPLAY_MODE_ON should be the default
	// after sw reset, but unless we explicitly set it,
	// ST7789_DISPLAY_INVERSION_ON will have no effect.
	hal_send_command_byte(eglib, ST7789_NORMAL_DISPLAY_MODE_ON);

	// Clear RAM
	clear_memory(eglib);

	// Main screen turn on
	hal_send_command_byte(eglib, ST7789_DISPLAY_ON);

	hal_comm_end(eglib);
};

static void sleep_in(eglib_t *eglib) {
	hal_comm_begin(eglib);
	hal_send_command_byte(eglib, ST7789_SLEEP_IN);
	hal_comm_end(eglib);
	hal_delay_ms(eglib, ST7789_SLEEP_IN_DELAY_MS);
};

static void sleep_out(eglib_t *eglib) {
	hal_comm_begin(eglib);
	hal_send_command_byte(eglib, ST7789_SLEEP_OUT);
	hal_comm_end(eglib);
	hal_delay_ms(eglib, ST7789_SLEEP_OUT_DELAY_MS);
};

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width, coordinate_t*height
) {
	st7789_config_t *display_config;

	display_config = display_get_config(eglib);

	*width = display_config->width;;
	*height = display_config->height;
};

static void get_pixel_format(eglib_t *eglib, pixel_format_t *pixel_format) {
	st7789_config_t *display_config;

	display_config = display_get_config(eglib);

	switch(display_config->color) {
		case ST7789_COLOR_12_BIT:
			*pixel_format = PIXEL_FORMAT_12BIT_RGB;
			break;
		case ST7789_COLOR_16_BIT:
			*pixel_format = PIXEL_FORMAT_16BIT_RGB;
			break;
		case ST7789_COLOR_18_BIT:
			*pixel_format = PIXEL_FORMAT_18BIT_RGB_24BIT;
			break;
		default:
			while(true);
	}
}

static void draw_pixel_color(
	eglib_t *eglib,
	coordinate_t x, coordinate_t y, color_t color
) {
	st7789_config_t *display_config;
	uint8_t buff[3];

	display_config = display_get_config(eglib);

	hal_comm_begin(eglib);

	set_column_address(eglib, x, x);
	set_row_address(eglib, y, y);

	hal_send_command_byte(eglib, ST7789_MEMORY_WRITE);

	switch(display_config->color) {
		case ST7789_COLOR_12_BIT:
			buff[0] = color.r & 0xf0;
			buff[0] |= (color.g & 0xf0) >> 4;
			buff[1] = color.b & 0xf0;
			for(uint8_t i=0 ; i < 2 ; i++)
				hal_send_data_byte(eglib, buff[i]);
			break;
		case ST7789_COLOR_16_BIT:
			buff[0] = color.r & 0xf8;
			buff[0] |= color.g >> 5;
			buff[1] = (color.g >> 2) << 5;
			buff[1] |= color.b >> 3;
			for(uint8_t i=0 ; i < 2 ; i++)
				hal_send_data_byte(eglib, buff[i]);
			break;
		case ST7789_COLOR_18_BIT:
			buff[0] = color.r & ~0x03;
			buff[1] = color.g & ~0x03;
			buff[2] = color.b & ~0x03;
			for(uint8_t i=0 ; i < 3 ; i++)
				hal_send_data_byte(eglib, buff[i]);
			break;
		default:
			while(true);
	}

	hal_comm_end(eglib);
};

static void send_buffer(
	eglib_t *eglib,
	void *buffer_ptr,
	coordinate_t x, coordinate_t y,
	coordinate_t width, coordinate_t height
) {
	st7789_config_t *display_config;
	uint8_t *buffer = (uint8_t *)buffer_ptr;

	display_config = display_get_config(eglib);

	if((uint32_t)x * get_bits_per_pixel(eglib) % 8)
		x -= 1;

	hal_comm_begin(eglib);
	set_column_address(eglib, x, x + width);
	for(coordinate_t v=y ; v < y + height ; v++) {
		set_row_address(eglib, v, v);
		hal_send_command_byte(eglib, ST7789_MEMORY_WRITE);
		hal_send_data(
			eglib,
			buffer + (
				display_config->width * v + x
			) * get_bits_per_pixel(eglib) / 8,
			(uint32_t)width * get_bits_per_pixel(eglib) / 8
		);
	}
	hal_comm_end(eglib);
}

static bool refresh(eglib_t *eglib) {
	(void)eglib;
	return false;
}

const display_t st7789 = {
	.comm = {
		.four_wire_spi = &((hal_four_wire_spi_config_comm_t){
		    .bit_numbering = EGLIB_HAL_MSB_FIRST,
		    .cs_setup_ns = 15,
		    .cs_hold_ns = 15,
		    .cs_disable_ns = 40,
		    .dc_setup_ns = 10,
		    .dc_hold_ns = 10,
		    .sck_cycle_ns = 66,  // 15.1MHz Datasheet
		    // .sck_cycle_ns = 47, // 21.2MHz Overclock
		}),
		.i2c = NULL,
	},
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_pixel_format = get_pixel_format,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = send_buffer,
	.refresh = refresh,
};

//
// Custom functions
//

void st7789_set_display_inversion(eglib_t *eglib, bool inversion) {
	hal_comm_begin(eglib);
	if(inversion)
		hal_send_command_byte(eglib, ST7789_DISPLAY_INVERSION_OFF);
	else
		hal_send_command_byte(eglib, ST7789_DISPLAY_INVERSION_ON);
	hal_comm_end(eglib);
}

void st7789_set_idle_mode(eglib_t *eglib, bool idle) {
	hal_comm_begin(eglib);
	if(idle)
		hal_send_command_byte(eglib, ST7789_IDLE_MODE_ON);
	else
		hal_send_command_byte(eglib, ST7789_IDLE_MODE_OFF);
	hal_comm_end(eglib);
}

// void st7789_write_display_brightness(eglib_t *eglib, uint8_t brightness) {
// 	hal_comm_begin(eglib);
// 	hal_send_command_byte(eglib, ST7789_WRITE_DISPLAY_BRIGHTNESS);
// 	hal_send_data_byte(eglib, brightness);
// 	hal_comm_end(eglib);
// }

// void st7789_set_brightness_control(
// 	eglib_t *eglib,
// 	bool brightness_control_block,
// 	bool display_dimming,
// 	bool backlight_control
// ) {
// 	uint8_t ctrl_display=0;

// 	if(brightness_control_block)
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_ON;
// 	else
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_BRIGHTNESS_CONTROL_BLOCK_OFF;
// 	if(display_dimming)
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_DIMMING_ON;
// 	else
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_DIMMING_OFF;
// 	if(backlight_control)
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_ON;
// 	else
// 		ctrl_display |= ST7789_WRITE_CTRL_DISPLAY_BACKLIGHT_CONTROL_OFF;

// 	hal_comm_begin(eglib);
// 	hal_send_command_byte(eglib, ST7789_WRITE_CTRL_DISPLAY);
// 	hal_send_data_byte(eglib, ctrl_display);
// 	hal_comm_end(eglib);
// }
// #define ST7789_WRITE_CTRL_DISPLAY 0x53