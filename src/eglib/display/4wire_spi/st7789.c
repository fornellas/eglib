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

static void set_column_address(const eglib_hal_4wire_spi_t *hal, void *hal_config, uint16_t x_start, uint16_t x_end) {
	uint8_t buff[4];

	buff[0] = (x_start&0xFF00)>>8;
	buff[1] = x_start&0xFF;
	buff[2] = (x_end&0xFF00)>>8;
	buff[3] = x_end&0xFF;

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_CASET);
	hal->set_dc(hal_config, 1);
	for(uint8_t i=0 ; i < sizeof(buff) ; i++)
		hal->send_byte(hal_config, buff[i]);
}

static void set_row_address(const eglib_hal_4wire_spi_t *hal, void *hal_config, uint16_t y_start, uint16_t y_end) {
	uint8_t buff[4];

	buff[0] = (y_start&0xFF00)>>8;
	buff[1] = y_start&0xFF;
	buff[2] = (y_end&0xFF00)>>8;
	buff[3] = y_end&0xFF;

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_RASET);
	hal->set_dc(hal_config, 1);
	for(uint8_t i=0 ; i < sizeof(buff) ; i++)
		hal->send_byte(hal_config, buff[i]);
}

static void convert_to_16bit(eglib_color_t *color, uint8_t buff[2]) {
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

static void init(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_st7789_config_t *display_config;

	display_config = (eglib_display_4wire_spi_st7789_config_t *)display_config_ptr;

	hal->set_reset(hal_config, 1);
	hal->set_dc(hal_config, 1);
	hal->set_cs(hal_config, 1);

	// Hardware reset
	hal->set_reset(hal_config, 0);
	hal->delay_ns(hal_config, ST7789_RESX_TRW_MS * 1000 * 1000);
	hal->set_reset(hal_config, 1);
	hal->delay_ns(hal_config, ST7789_RESX_TRT_MS * 1000 * 1000);

	// Software reset
	hal->set_cs(hal_config, 0);
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_SWRESET);
	hal->set_cs(hal_config, 1);
	hal->delay_ns(hal_config, ST7789_SWRESET_DELAY_MS * 1000 * 1000);

	hal->set_cs(hal_config, 0);

	// Out of sleep mode
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_SLPOUT);
	hal->delay_ns(hal_config, ST7789_SLPOUT_DELAY_SLEEP_IN_MS * 1000 * 1000);

	// Set color mode
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_COLMOD);
	hal->set_dc(hal_config, 1);
	hal->send_byte(hal_config, ST7789_COLMOD_COLOR_16BIT_WRITE);

	// Memory Data Access Control
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_MADCTL);
	hal->set_dc(hal_config, 1);
	hal->send_byte(
		hal_config,
		ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM |
		ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT |
		ST7789_MADCTL_PAGE_COLUMN_ORDER_NORMAL |
		ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM |
		ST7789_MADCTL_ORDER_RGB |
		ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_LEFT_TO_RIGHT
	);

	// Display inversion in practice works the opposite of what the datasheet
	// says: on is off and off is on.
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_INVON);
	// Datasheet states NORON should be the default after sw reset, but unless
	// we explicitly set it, INVON will have no effect.
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_NORON);

	// Clear RAM
	set_column_address(hal, hal_config, 0, display_config->width - 1);
	set_row_address(hal, hal_config, 0, display_config->height - 1);
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_RAMWR);
	hal->set_dc(hal_config, 1);
	for(uint32_t i=0, max=display_config->width * display_config->height * 2 ; i < max ; i++)
		hal->send_byte(hal_config, 0x00);

	// Main screen turn on
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_DISPON);

	hal->set_cs(hal_config, 1);
};

static void sleep_in(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	// TODO
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;
};

static void sleep_out(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	// TODO
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;
};

static void get_dimension(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	eglib_display_4wire_spi_st7789_config_t *display_config;

	(void)hal;
	(void)hal_config;

	display_config = (eglib_display_4wire_spi_st7789_config_t *)display_config_ptr;

	*width = display_config->width;;
	*height = display_config->height;
};

static void get_color_depth(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_color_depth_t *color_depth
) {
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;

	*color_depth = EGLIB_COLOR_DEPTH_18BIT_565_RGB;
}

static void draw_pixel_color(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {
	uint8_t color_16bit[2];

	(void)display_config_ptr;

	hal->set_cs(hal_config, 0);

	set_column_address(hal, hal_config, x, x);
	set_row_address(hal, hal_config, y, y);

	convert_to_16bit(&color, color_16bit);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, ST7789_RAMWR);
	hal->set_dc(hal_config, 1);
	for(uint8_t i=0 ; i < sizeof(color_16bit) ; i++)
		hal->send_byte(hal_config, color_16bit[i]);

	hal->set_cs(hal_config, 1);
};

const eglib_display_4wire_spi_t eglib_display_4wire_spi_st7789 = {
	.hal_4wire_spi_config_comm = {
	    .mode = 0,
	    .bit_numbering = EGLIB_HAL_4WIRE_SPI_MSB_FIRST,
	    .cs_setup_ns = 15,
	    .cs_hold_ns = 15,
	    .cs_disable_ns = 40,
	    .dc_setup_ns = 10,
	    .dc_hold_ns = 10,
	    .sck_cycle_ns = 66,
	    .mosi_setup_ns = 10,
	    .mosi_hold_ns = 10,
	},
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = eglib_display_4wire_spi_frame_buffer_send_buffer_18bit_565_rgb,
};