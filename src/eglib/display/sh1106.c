#include "sh1106.h"

//
// Defines from Datasheet
//

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
// Functions
//

// Helpers

static inline void set_column_address(
	eglib_t *eglib,
	eglib_coordinate_t column
) {
	eglib_display_sh1106_config_t *display_config;
	uint8_t buff[2];

	display_config = eglib->display_config_ptr;

	buff[0] = SH1106_SET_HIGHER_COLUMN_ADDRESS(column + display_config->column_offset);
	buff[1] = SH1106_SET_LOWER_COLUMN_ADDRESS(column + display_config->column_offset);
	eglib_hal_send_command(eglib, buff, sizeof(buff));
}

static inline void display_on(eglib_t *eglib) {
	uint8_t buff[] = {
		SH1106_DISPLAY_ON,
	};

	eglib_hal_send_command(eglib, buff, sizeof(buff));
	eglib_hal_delay_ms(eglib, SH1106_DISPLAY_ON_MS);
}

// eglib_display_t

static void init(eglib_t *eglib) {
	eglib_display_sh1106_config_t *display_config;

	display_config = eglib->display_config_ptr;

	// Hardware reset

	eglib_hal_set_reset(eglib, 0);
	eglib_hal_delay_ms(eglib, SH1106_RESET_LOW_MS);
	eglib_hal_set_reset(eglib, 1);
	eglib_hal_delay_ms(eglib, SH1106_RESET_HIGH_MS);

	// comm begin

	eglib_hal_comm_begin(eglib);


	uint8_t commands_init[] = {
		// Display physical construction

		SH1106_SET_SEGMENT_REMAP(display_config->segment_remap),

		SH1106_SET_MULTIPLEX_RATIO,
		SH1106_SET_MULTIPLEX_RATIO_ARG(display_config->height-1),

		SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET,
		SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_MODE_SET_ARG(display_config->common_pads_hardware_configuration_mode),

		SH1106_SET_COMMON_OUTPUT_SCAN_DIRECTION(display_config->common_output_scan_direction),	

		SH1106_SET_DISPLAY_OFFSET(display_config->display_offset),

		// Change period

		SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET,
		SH1106_DISCHARGE_PRECHARGE_PERIOD_MODE_SET_ARG(display_config->dis_charge_period, display_config->pre_charge_period),	

		// VCOM deselect

		SH1106_VCOM_DESELECT_LEVEL_MODE_SET,
		display_config->vcom_deselect_level,

		// Internal display clocks

		SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY,
		SH1106_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG(display_config->oscillator_frequency, display_config->clock_divide),	
	};

	eglib_hal_send_command(eglib, commands_init, sizeof(commands_init));


	// Charge Pump Regulator
	if(display_config->dc_dc_enable) {
		eglib_hal_send_command_literal(eglib, SH1106_DC_DC_CONTROL_MODE_SET);
		eglib_hal_send_command_literal(eglib, SH1106_DC_DC_ON);
		eglib_hal_send_command_literal(eglib, SHH1106_SET_PUMP_VOLTAGE(display_config->dc_dc_voltage));
	} else {
		eglib_hal_send_command_literal(eglib, SH1106_DC_DC_CONTROL_MODE_SET);
		eglib_hal_send_command_literal(eglib, SH1106_DC_DC_OFF);
	}

	// Clear RAM
	for(uint8_t page=0 ; page < (display_config->height / 8) ; page++) {
		eglib_hal_send_command_literal(eglib, SH1106_SET_PAGE_ADDRESS(page));
		set_column_address(eglib, 0);
		for(eglib_coordinate_t column=0 ; column < display_config->width ; column ++)
			eglib_hal_send_data_literal(eglib, 0x00);
	}

	// Set display on
	display_on(eglib);

	eglib_hal_comm_end(eglib);
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
	eglib_coordinate_t *width, eglib_coordinate_t*height
) {
	eglib_display_sh1106_config_t *display_config;

	display_config = eglib->display_config_ptr;

	*width = display_config->width;;
	*height = display_config->height;
};

static void get_color_depth(eglib_t *eglib, eglib_color_depth_t *color_depth) {
	(void)eglib;

	*color_depth = EGLIB_COLOR_DEPTH_1BIT_PAGED;
}

static void draw_pixel_color(
	eglib_t *eglib,
	eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color
) {
	(void)eglib;
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
	eglib_coordinate_t display_width, display_height;

	buffer = (uint8_t *)buffer_ptr;

	eglib->display->get_dimension(
		eglib,
		&display_width, &display_height
	);

	eglib_hal_comm_begin(eglib);
	for(uint8_t page=y/8 ; page < ((y+height)/8+1) ; page++) {
		eglib_hal_send_command_literal(eglib, SH1106_SET_PAGE_ADDRESS(page));
		set_column_address(eglib, 0);
		for(eglib_coordinate_t column=x ; column < (x+width) ; column ++)
			eglib_hal_send_data_literal(
				eglib,
				*(buffer + page * display_width + column)
			);
	}
	eglib_hal_comm_end(eglib);
}

// Custom Functions

void eglib_display_sh1106_set_start_line(
	eglib_t *eglib,
	uint8_t line
) {
	eglib_hal_comm_begin(eglib);
	eglib_hal_send_command_literal(eglib, SH1106_SET_DISPLAY_START_LINE(line));
	eglib_hal_comm_end(eglib);
}

void eglib_display_sh1106_set_contrast(
	eglib_t *eglib,
	uint8_t contrast
) {
	eglib_hal_comm_begin(eglib);
	eglib_hal_send_command_literal(eglib, SH1106_SET_CONTRAST_CONTROL_REGISTER);
	eglib_hal_send_command_literal(eglib, contrast);
	eglib_hal_comm_end(eglib);
}

void eglib_display_sh1106_entire_display_on(
	eglib_t *eglib,
	uint8_t entire_display_on
) {
	eglib_hal_comm_begin(eglib);
	if(entire_display_on)
		eglib_hal_send_command_literal(eglib, SH1106_SET_ENTIRE_DISPLAY_ON);
	else
		eglib_hal_send_command_literal(eglib, SH1106_SET_ENTIRE_DISPLAY_OFF);
	eglib_hal_comm_end(eglib);
}

void eglib_display_sh1106_reverse(
	eglib_t *eglib,
	uint8_t reverse
) {
	eglib_hal_comm_begin(eglib);
	if(reverse)
		eglib_hal_send_command_literal(eglib, SH1106_SET_REVERSE_DISPLAY);
	else
		eglib_hal_send_command_literal(eglib, SH1106_SET_NORMAL_DISPLAY);
	eglib_hal_comm_end(eglib);
}

//
// eglib_display_t
//

static eglib_hal_i2c_config_comm_t eglib_hal_i2c_config_comm = {
	.speed = EGLIB_HAL_I2C_400KHZ,
};

const eglib_display_t eglib_display_sh1106_vdd1_1_65_v = {
	.comm = {
		.four_wire_spi = &((eglib_hal_four_wire_spi_config_comm_t){
			.mode = 0,
			.bit_numbering = EGLIB_HAL_FOUR_WIRE_SPI_MSB_FIRST,
			.cs_setup_ns = 240,
			.cs_hold_ns = 120,
			.cs_disable_ns = 0,
			.dc_setup_ns = 300,
			.dc_hold_ns = 300,
			.sck_cycle_ns = 500,
			.mosi_setup_ns = 200,
			.mosi_hold_ns = 200,
		}),
		.i2c = &eglib_hal_i2c_config_comm,
	},
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = send_buffer,
};

const eglib_display_t eglib_display_sh1106_vdd1_2_4_v = {
	.comm = {
		.four_wire_spi = &((eglib_hal_four_wire_spi_config_comm_t){
			.mode = 0,
			.bit_numbering = EGLIB_HAL_FOUR_WIRE_SPI_MSB_FIRST,
			.cs_setup_ns = 120,
			.cs_hold_ns = 60,
			.cs_disable_ns = 0,
			.dc_setup_ns = 150,
			.dc_hold_ns = 150,
			.sck_cycle_ns = 250,
			.mosi_setup_ns = 100,
			.mosi_hold_ns = 100,
		}),
		.i2c = &eglib_hal_i2c_config_comm,
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
// eglib_display_sh1106_config_t
//

const eglib_display_sh1106_config_t eglib_display_sh1106_config_sparkfun_micro_oled = {
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