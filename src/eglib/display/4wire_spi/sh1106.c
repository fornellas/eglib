#include "sh1106.h"

#define SH1106_SET_LOWER_COLUMN_START_ADDRESS(addr) (0x00&((addr)&0x0F))
#define SH1106_SET_HIGHER_COLUMN_START_ADDRESS(addr) (0x10&((addr)&0x0F))

#define SHH1106_PUMP_VOLTAGE_6_4 0x0
#define SHH1106_PUMP_VOLTAGE_7_4 0x1
#define SHH1106_PUMP_VOLTAGE_8_0 0x2
#define SHH1106_PUMP_VOLTAGE_9_0 0x3
#define SHH1106_SET_PUMP_VOLTAGE(voltage) (0x30&(voltage&0x3))

#define SH1106_SET_DISPLAY_START_LINE(line) (0x40&(line&0x3F))

#define SH1106_SET_CONTRAST_CONTROL_REGISTER 0x81

#define SH1106_SET_SEGMENT_REMAP_NORMAL 0xA0
#define SH1106_SET_SEGMENT_REMAP_REVERSE 0xA1

#define SH1106_SET_ENTIRE_DISPLAY_OFF 0xA4
#define SH1106_SET_ENTIRE_DISPLAY_ON 0xA5

#define SH1106_SET_NORMAL_DISPLAY 0xA6
#define SH1106_SET_REVERSE_DISPLAY 0xA7

#define SH1106_SET_MULTIPLEX_RATION 0xA8

#define SH1106_DC_DC_CONTROL_MODE_SET 0xAD
#define SH1106_DC_DC_OFF 0x8A
#define SH1106_DC_DC_ON 0x8B

#define SH1106_DISPLAY_OFF 0xAE
#define SH1106_DISPLAY_ON 0xAF

#define SH1106_SET_PAGE_ADDRESS(addr) (0xB0&(adddr&0x0F))

#define SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_ASC 0xC0
#define SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION_DESC 0xC8

#define SH1106_SET_DDISPLAY_OFFSET 0xD3

#define SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY 0xD5
#define SH1106_OSCILLATOR_FREQUENCY_MINUS_25_PCT 0
#define SH1106_OSCILLATOR_FREQUENCY_MINUS_20_PCT 1
#define SH1106_OSCILLATOR_FREQUENCY_MINUS_15_PCT 2
#define SH1106_OSCILLATOR_FREQUENCY_MINUS_10_PCT 3
#define SH1106_OSCILLATOR_FREQUENCY_MINUS_5_PCT 4
#define SH1106_OSCILLATOR_FREQUENCY__0_PCT 5
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_5_PCT 6
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_10_PCT 7
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_15_PCT 8
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_20_PCT 9
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_25_PCT 10
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_30_PCT 11
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_35_PCT 12
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_40_PCT 13
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_45_PCT 14
#define SH1106_OSCILLATOR_FREQUENCY_PLUS_50_PCT 15
#define SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG ( \
	oscillator_frequency, \
	divite_ratio \
) ( \
	(0xF0&(oscillator_frequency<<4)) | \
	(0xF&divite_ratio) \
)

#define SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET 0xD9
#define SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET_ARG ( \
	discharge_period, \
	precharge_period \
) ( \
	(0xF0&(discharge_period<<4)) | \
	(0xF&precharge_period) \
)

#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET 0xDA
#define SH1106_COMMON_PADS_SEQUENTIAL 0x02
#define SH1106_COMMON_PADS_ALTERNATIVE 0x12

#define SH1106_VCOM_DESSELECT_LEVEL_MODE_SET 0xDB

#define SH1106_READ_MODIFY_WRITE 0xE0

#define SH1106_END 0xEE

#define SH1106_NOP 0xE3

//
// Helpers
//



//
// Display
//


static void power_up(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config
) {
	// eglib_display_4wire_spi_sh1106_config_t *config = (eglib_display_4wire_spi_sh1106_config_t *)display_config;

};

static void power_down(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config
) {

};

static void get_dimension(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config,
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	(void)hal;
	(void)hal_config;

	eglib_display_4wire_spi_sh1106_config_t *config = (eglib_display_4wire_spi_sh1106_config_t *)display_config;

	*width = config->width;;
	*height = config->height;
};

static void get_color_depth(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config,
	eglib_color_depth_t *color_depth
) {
	(void)hal;
	(void)hal_config;

	*color_depth = EGLIB_COLOR_DEPTH_1BIT;
}

static void draw_pixel(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {

};

const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_1_65 = {
	.hal_config_base = {
	    .mode = 0,
	    .bit_numbering = EGLIB_HAL_4WIRE_SPI_MSB_FIRST,
	    .cs_setup_ns = 240,
	    .cs_hold_ns = 120,
	    .cs_disable_ns = 0,
	    .dc_setup_ns = 300,
	    .dc_hold_ns = 300,
	    .sck_cycle_ns = 500,
	    .mosi_setup_ns = 200,
	    .mosi_hold_ns = 200,
	},
	.power_up = power_up,
	.power_down = power_down,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel = draw_pixel,
};

const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_2_4 = {
	.hal_config_base = {
	    .mode = 0,
	    .bit_numbering = EGLIB_HAL_4WIRE_SPI_MSB_FIRST,
	    .cs_setup_ns = 120,
	    .cs_hold_ns = 60,
	    .cs_disable_ns = 0,
	    .dc_setup_ns = 150,
	    .dc_hold_ns = 150,
	    .sck_cycle_ns = 250,
	    .mosi_setup_ns = 100,
	    .mosi_hold_ns = 100,
	},
	.power_up = power_up,
	.power_down = power_down,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel = draw_pixel,
};