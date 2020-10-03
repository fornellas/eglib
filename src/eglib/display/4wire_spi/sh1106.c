#include "sh1106.h"

#define SH1106_RESET_LOW_MS 10
#define SH1106_RESET_HIGH_MS 2

#define SH1106_SET_LOWER_COLUMN_ADDRESS(addr) (0x00|((addr)&0x0F))
#define SH1106_SET_HIGHER_COLUMN_ADDRESS(addr) (0x10|((addr)>>4))

#define SHH1106_SET_PUMP_VOLTAGE(voltage) (0x30|((voltage)&0x3))

#define SH1106_SET_DISPLAY_START_LINE(line) (0x40|((line)&0x3F))

#define SH1106_SET_CONTRAST_CONTROL_REGISTER 0x81

#define SH1106_SET_SEGMENT_REMAP(dir) (0xA0|((dir)&0x1))

#define SH1106_SET_ENTIRE_DISPLAY_OFF 0xA4
#define SH1106_SET_ENTIRE_DISPLAY_ON 0xA5

#define SH1106_SET_NORMAL_DISPLAY 0xA6
#define SH1106_SET_REVERSE_DISPLAY 0xA7

#define SH1106_SET_MULTIPLEX_RATIO 0xA8
#define SH1106_SET_MULTIPLEX_RATIO_ARG(ratio) ((ratio)&0x3F)

#define SH1106_DC_DC_CONTROL_MODE_SET 0xAD
#define SH1106_DC_DC_OFF 0x8A
#define SH1106_DC_DC_ON 0x8B

#define SH1106_DISPLAY_OFF 0xAE
#define SH1106_DISPLAY_ON 0xAF
#define SH1106_DISPLAY_ON_MS 100

#define SH1106_SET_PAGE_ADDRESS(addr) (0xB0|((addr)&0x0F))

#define SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION(dir) (0xC0|(((dir)&0x1)<<3))

#define SH1106_SET_DISPLAY_OFFSET(value) (0xD3|((value)&0x3F))

#define SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY 0xD5
#define SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG( \
	oscillator_frequency, \
	divite_ratio \
) ( \
	(0xF0&((oscillator_frequency)<<4)) | \
	(0xF&(divite_ratio)) \
)

#define SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET 0xD9
#define SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET_ARG( \
	discharge_period, \
	precharge_period \
) ( \
	(0xF0&((discharge_period)<<4)) | \
	(0xF&(precharge_period)) \
)

#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET 0xDA
#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET_ARG(value) (0x02|(((value)&0x1)<<4))

#define SH1106_VCOM_DESELECT_LEVEL_MODE_SET 0xDB

#define SH1106_READ_MODIFY_WRITE 0xE0

#define SH1106_END 0xEE

#define SH1106_NOP 0xE3

//
// Config
//

const eglib_display_4wire_spi_sh1106_config_t eglib_display_4wire_spi_sh1106_config_sparkfun_micro_oled = {
	// Display physical construction
	.width = 64,
	.height = 48,
	.segment_remap = SH1106_SEGMENT_REMAP_REVERSE,
	.common_pads_hardware_configuration_mode = SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_ALTERNATIVE,
	.common_output_scan_direction = SH1106_COMMON_OUTPUT_SCAN_DIRECTION_ASC,
	.display_offset = 0,
	.column_offset = 0,

	// Change period
	.pre_charge_period = 1,
	.dis_charge_period = 15,

	// VCOM deselect
	.vcom_deselect_level = 0x40,

	// Internal display clocks
	.clock_divide = 0,
	.oscillator_frequency = SH1106_OSCILLATOR_FREQUENCY_PLUS_15_PCT,

	// Charge Pump Regulator
	.dc_dc_enable = true,
	.dc_dc_voltage = SHH1106_DC_DC_8_0_V,
};

//
// Helpers
//

static inline void set_column_address(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t column
) {
	eglib_display_4wire_spi_sh1106_config_t *display_config;

	display_config = (eglib_display_4wire_spi_sh1106_config_t *)display_config_ptr;

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SH1106_SET_HIGHER_COLUMN_ADDRESS(column + display_config->column_offset));
	hal->send_byte(hal_config, SH1106_SET_LOWER_COLUMN_ADDRESS(column + display_config->column_offset));
}

static inline void display_on(
	const eglib_hal_4wire_spi_t *hal,
	eglib_hal_4wire_spi_config_t *hal_config
) {
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SH1106_DISPLAY_ON);
	hal->delay_ns(hal_config, SH1106_DISPLAY_ON_MS * 1000 * 1000);
}

//
// Display
//

static void init(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	eglib_display_4wire_spi_sh1106_config_t *display_config = (eglib_display_4wire_spi_sh1106_config_t *)display_config_ptr;


	// Hardware reset

	hal->set_dc(hal_config, 1);
	hal->set_reset(hal_config, 0);
	hal->delay_ns(hal_config, SH1106_RESET_LOW_MS * 1000 * 1000);
	hal->set_reset(hal_config, 1);
	hal->delay_ns(hal_config, SH1106_RESET_HIGH_MS * 1000 * 1000);

	// Enable / command

	hal->set_cs(hal_config, 0);
	hal->set_dc(hal_config, 0);

	// Display physical construction

	hal->send_byte(hal_config, SH1106_SET_SEGMENT_REMAP(display_config->segment_remap));

	// hal->send_byte(hal_config, SH1106_SET_DISPLAY_START_LINE(display_config->display_start_line));

	hal->send_byte(hal_config, SH1106_SET_MULTIPLEX_RATIO);
	hal->send_byte(hal_config, SH1106_SET_MULTIPLEX_RATIO_ARG(display_config->height-1));

	hal->send_byte(hal_config, SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET);
	hal->send_byte(hal_config, SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET_ARG(display_config->common_pads_hardware_configuration_mode));

	hal->send_byte(hal_config, SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION(display_config->common_output_scan_direction));	

	hal->send_byte(hal_config, SH1106_SET_DISPLAY_OFFSET(display_config->display_offset));

	// Change period

	hal->send_byte(hal_config, SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET);
	hal->send_byte(hal_config, SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET_ARG(display_config->dis_charge_period, display_config->pre_charge_period));	

	// VCOM deselect

	hal->send_byte(hal_config, SH1106_VCOM_DESELECT_LEVEL_MODE_SET);
	hal->send_byte(hal_config, display_config->vcom_deselect_level);


	// Internal display clocks

	hal->send_byte(hal_config, SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY);
	hal->send_byte(hal_config, SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG(display_config->oscillator_frequency, display_config->clock_divide));	

	// Charge Pump Regulator
	if(display_config->dc_dc_enable) {
		hal->send_byte(hal_config, SH1106_DC_DC_CONTROL_MODE_SET);
		hal->send_byte(hal_config, SH1106_DC_DC_ON);
		hal->send_byte(hal_config, SHH1106_SET_PUMP_VOLTAGE(display_config->dc_dc_voltage));
	} else {
		hal->send_byte(hal_config, SH1106_DC_DC_CONTROL_MODE_SET);
		hal->send_byte(hal_config, SH1106_DC_DC_OFF);
	}

	// Clear RAM
	for(uint8_t page=0 ; page < (display_config->height / 8) ; page++) {
		hal->set_dc(hal_config, 0);
		hal->send_byte(hal_config, SH1106_SET_PAGE_ADDRESS(page));
		set_column_address(hal, hal_config, display_config, 0);
		hal->set_dc(hal_config, 1);
		for(eglib_coordinate_t column=0 ; column < display_config->width ; column ++)
			hal->send_byte(hal_config, 0x00);
	}

	// Set display on
	display_on(hal, hal_config);

	hal->set_cs(hal_config, 1);
};

static void sleep_in(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;
	// TODO
};

static void sleep_out(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr
) {
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;
	// TODO
};

static void get_dimension(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	(void)hal;
	(void)hal_config;

	eglib_display_4wire_spi_sh1106_config_t *display_config = (eglib_display_4wire_spi_sh1106_config_t *)display_config_ptr;

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

	*color_depth = EGLIB_COLOR_DEPTH_1BIT_PAGED;
}

static void draw_pixel_color(
	const eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {
	(void)hal;
	(void)hal_config;
	(void)display_config_ptr;
	(void)x;
	(void)y;
	(void)color;
};

static void send_buffer(
	eglib_t *eglib,
	void *buffer_ptr,
	eglib_coordinate_t x, eglib_coordinate_t y,
	eglib_coordinate_t width, eglib_coordinate_t height
) {
	uint8_t *buffer;
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;
	const eglib_display_4wire_spi_t *display;
	void *display_config_ptr;
	eglib_coordinate_t display_width, display_height;

	buffer = (uint8_t *)buffer_ptr;
	hal = eglib->drivers.four_wire_spi.hal;
	hal_config = &eglib->drivers.four_wire_spi.hal_config;
	display = eglib->drivers.four_wire_spi.display;
	display_config_ptr = eglib->drivers.four_wire_spi.display_config_ptr;

	display->get_dimension(
		hal, hal_config, display_config_ptr,
		&display_width, &display_height
	);

	hal->set_cs(hal_config, 0);
	for(uint8_t page=y/8 ; page < ((y+height)/8+1) ; page++) {
		hal->set_dc(hal_config, 0);
		hal->send_byte(hal_config, SH1106_SET_PAGE_ADDRESS(page));
		set_column_address(hal, hal_config, display_config_ptr, 0);
		hal->set_dc(hal_config, 1);
		for(eglib_coordinate_t column=x ; column < (x+width) ; column ++)
			hal->send_byte(
				hal_config,
				*(buffer + page * display_width + column)
			);
	}
	hal->set_cs(hal_config, 1);
}

const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_1_65_v = {
	.hal_4wire_spi_config_comm = {
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
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = send_buffer,
};

const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_2_4_v = {
	.hal_4wire_spi_config_comm = {
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
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = send_buffer,
};

//
// Extra
//

void eglib_display_4wire_spi_sh1106_set_start_line(
	eglib_t *eglib,
	uint8_t line
) {
	eglib_hal_4wire_spi_set_cs(eglib, 0);
	eglib_hal_4wire_spi_set_dc(eglib, 0);
	eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_DISPLAY_START_LINE(line));
	eglib_hal_4wire_spi_set_cs(eglib, 1);
}

void eglib_display_4wire_spi_sh1106_set_contrast(
	eglib_t *eglib,
	uint8_t contrast
) {
	eglib_hal_4wire_spi_set_cs(eglib, 0);
	eglib_hal_4wire_spi_set_dc(eglib, 0);
	eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_CONTRAST_CONTROL_REGISTER);
	eglib_hal_4wire_spi_send_byte(eglib, contrast);
	eglib_hal_4wire_spi_set_cs(eglib, 1);
}

void eglib_display_4wire_spi_sh1106_entire_display_on(
	eglib_t *eglib,
	uint8_t entire_display_on
) {
	eglib_hal_4wire_spi_set_cs(eglib, 0);
	eglib_hal_4wire_spi_set_dc(eglib, 0);
	if(entire_display_on)
		eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_ENTIRE_DISPLAY_ON);
	else
		eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_ENTIRE_DISPLAY_OFF);
	eglib_hal_4wire_spi_set_cs(eglib, 1);
}

void eglib_display_4wire_spi_sh1106_reverse(
	eglib_t *eglib,
	uint8_t reverse
) {
	eglib_hal_4wire_spi_set_cs(eglib, 0);
	eglib_hal_4wire_spi_set_dc(eglib, 0);
	if(reverse)
		eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_REVERSE_DISPLAY);
	else
		eglib_hal_4wire_spi_send_byte(eglib, SH1106_SET_NORMAL_DISPLAY);
	eglib_hal_4wire_spi_set_cs(eglib, 1);
}
