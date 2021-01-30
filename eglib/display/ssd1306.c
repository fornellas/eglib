#include "ssd1306.h"

#define SSD1306_RESET_PULSE_MS 3

// Fundamental Commands

#define SSD1306_SET_CONTRAST_CONTROL 0x81

#define SSD1306_OUTPUT_FOLLOWS_RAM 0xA4
#define SSD1306_OUTPUT_IGNORES_RAM 0xA5

#define SSD1306_NORMAL_DISPLAY 0xA6
#define SSD1306_INVERSE_DISPLAY 0xA7

#define SSD1306_DISPLAY_OFF 0xAE
#define SSD1306_DISPLAY_ON 0xAF

// Scrolling Commands

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27

#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_ACTIVATE_SCROLL 0x2F

#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3

// Addressing Setting Commands

#define SSD1306_SET_MEMORY_ADDRESSING_MODE 0x20
#define SSD1306_SET_MEMORY_ADDRESSING_MODE_HORIZONTAL 0x00
#define SSD1306_SET_MEMORY_ADDRESSING_MODE_VERTICAL 0x01
#define SSD1306_SET_MEMORY_ADDRESSING_MODE_PAGE 0x02

#define SSD1306_SET_COLMN_ADDRESS 0x21
#define SSD1306_SET_PAGE_ADDRESS 0x22

#define SSD1306_SET_PAGE_START_ADDRESS(addr) (0xB0&((addr)&0x0F))
#define SSD1306_SET_LOWER_COLUMN_START_ADDRESS(addr) (0x00&((addr)&0x0F))
#define SSD1306_SET_HIGHER_COLUMN_START_ADDRESS(addr) (0x10&((addr)&0x0F))

// Hardware Configuration (Panel resolution & layout related) Commands

#define SSD1306_SET_MULTIPLEX_RATIO 0xA8

#define SSD1306_SET_DISPLAY_OFFSET 0xD3

#define SSD1306_SET_DISPLAY_START_LINE(line) (0x40&((line)&0x3F))

#define SSD1306_SET_SEGMENT_REMAP_COLUMN_0_TO_SEG0 0xA0
#define SSD1306_SET_SEGMENT_REMAP_COLUMN_127_TO_SEG0 0xA1

#define SSD1306_SET_COM_OUTPUT_SCAN_NORMAL 0xC0
#define SSD1306_SET_COM_OUTPUT_SCAN_REMAPPED 0xC8

#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION 0xDA
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_SEQUENTIAL 0x00
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_ALTERNATIVE 0x01
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_LEFT_RIGHT_REMAP_DISABLE 0x00
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_LEFT_RIGHT_REMAP_ENABLE 0x01
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_ARG( \
	com_pin_configuration, \
	left_right_remap \
) ( \
	((((com_pin_configuration)) & 0x01) << 4) | \
	(((left_right_remap) & 0x01) << 5) \
)

// Timing & Driving Scheme Setting Commands

#define SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY 0xD5
#define SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG( \
	display_clock_divide_ratio, \
	oscillator_frequency \
) ( \
	(((oscillator_frequency)<<4)&0xF0) | \
	((display_clock_divide_ratio)&0x0F) \
)

#define SSD1306_SET_PRE_CHARGE_PERIOD 0xD9
#define SSD1306_SET_PRE_CHARGE_PERIOD_ARG( \
	phase_1_period, \
	phase_2_period \
)  ( \
	((phase_1_period)&0x0F) | \
	(((phase_2_period)<<4)&0xF0) \
)

#define SSD1306_SET_VCOMH_DESELECT_LEVEL 0xDB
#define SSD1306_SET_VCOMH_DESELECT_LEVEL_0_65_VCC 0x00
#define SSD1306_SET_VCOMH_DESELECT_LEVEL_0_77_VCC 0x20
#define SSD1306_SET_VCOMH_DESELECT_LEVEL_0_83_VCC 0x30

#define SSD1306_NOP 0xE3

// Charge Bump Setting

#define SSD1306_CHARGE_PUMP_SETTING 0x8D
#define SSD1306_CHARGE_PUMP_SETTING_ENABLE 0x14
#define SSD1306_CHARGE_PUMP_SETTING_DISABLE 0x10

//
// Display
//

static void power_up(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config
) {
	eglib_display_4wire_spi_ssd1306_config_t *config = (eglib_display_4wire_spi_ssd1306_config_t *)display_config;

	// Hardware reset
	hal->set_cs(hal_config, 1);
	hal->delay_ns(hal_config, SSD1306_RESET_PULSE_MS * 1000 * 1000);
	hal->set_reset(hal_config, 1);
	hal->set_cs(hal_config, 0);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_DISPLAY_OFF);

	if(config->rc_oscillator) {
		hal->set_dc(hal_config, 0);
		hal->send_byte(
			hal_config, SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY
		);
		hal->send_byte(
			hal_config,
			SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSCILLATOR_FREQUENCY_ARG(
				config->rc_oscillator_display_clock_divide_ratio,
				config->rc_oscillator_frequency
			)
		);
	}

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_MULTIPLEX_RATIO);
	hal->send_byte(hal_config, config->height - 1);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_DISPLAY_OFFSET);
	hal->send_byte(hal_config, 0);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_DISPLAY_START_LINE(0));

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_CHARGE_PUMP_SETTING);
	if(config->charge_pump_regulator)
		hal->send_byte(hal_config, SSD1306_CHARGE_PUMP_SETTING_ENABLE);
	else
		hal->send_byte(hal_config, SSD1306_CHARGE_PUMP_SETTING_DISABLE);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_MEMORY_ADDRESSING_MODE);
	hal->send_byte(hal_config, SSD1306_SET_MEMORY_ADDRESSING_MODE_HORIZONTAL);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_SEGMENT_REMAP_COLUMN_127_TO_SEG0);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_COM_OUTPUT_SCAN_REMAPPED);

	hal->set_dc(hal_config, 0);
	hal->send_byte(
		hal_config, SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION
	);
	hal->send_byte(
		hal_config,
		SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_ARG(
			SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_ALTERNATIVE,
			SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION_LEFT_RIGHT_REMAP_DISABLE
		)
	);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_CONTRAST_CONTROL);
	hal->send_byte(hal_config, 0x80);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_PRE_CHARGE_PERIOD);
	hal->send_byte(
		hal_config,
		SSD1306_SET_PRE_CHARGE_PERIOD_ARG(
			2,
			2
		)
	);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_SET_VCOMH_DESELECT_LEVEL);
	hal->send_byte(hal_config, SSD1306_SET_VCOMH_DESELECT_LEVEL_0_77_VCC);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_OUTPUT_FOLLOWS_RAM);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_NORMAL_DISPLAY);

	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_DEACTIVATE_SCROLL);

    for (uint8_t page = 0; page < (config->height / 8) - 1; page++) {
        hal->set_dc(hal_config, 0);
        // SH1106
		hal->send_byte(hal_config, SSD1306_SET_PAGE_START_ADDRESS(page));
		hal->send_byte(hal_config, SSD1306_SET_LOWER_COLUMN_START_ADDRESS(0));
		hal->send_byte(hal_config, SSD1306_SET_HIGHER_COLUMN_START_ADDRESS(0));
       	// SSD1306
        // i2c_send(0xB0 + page); // set page
        // i2c_send(0x21); // column address
        // i2c_send(0x00); // first column =0
        // i2c_send(width - 1); // last column

        hal->set_dc(hal_config, 1);
        for (uint_fast8_t column = 0; column < config->width; column++) {
            hal->send_byte(hal_config, 0xAA);
        }
    }

	hal->set_cs(hal_config, 1);
}

static void power_down(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config
) {
	(void)hal;
	(void)hal_config;
	(void)display_config;

	hal->set_cs(hal_config, 0);
	hal->set_dc(hal_config, 0);
	hal->send_byte(hal_config, SSD1306_DISPLAY_OFF);
	hal->set_cs(hal_config, 1);
}

static void get_dimension(
	eglib_hal_4wire_spi_t *hal, eglib_hal_4wire_spi_config_t *hal_config,
	void *display_config,
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	eglib_display_4wire_spi_ssd1306_config_t *config;

	(void)hal;
	(void)hal_config;

	config = (eglib_display_4wire_spi_ssd1306_config_t *)display_config;

	*width = config->width;;
	*height = config->height;
}

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
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	// hal->set_cs(hal_config, 0);

	// hal->set_dc(hal_config, 0);
	// hal->send_byte(hal_config, SSD1306_SET_MEMORY_ADDRESSING_MODE);
	// hal->send_byte(hal_config, SSD1306_SET_MEMORY_ADDRESSING_MODE_HORIZONTAL);

	// hal->send_byte(hal_config, SSD1306_SET_COLMN_ADDRESS);
	// hal->send_byte(hal_config, x);
	// hal->send_byte(hal_config, x);

	// hal->send_byte(hal_config, SSD1306_SET_PAGE_ADDRESS);
	// hal->send_byte(hal_config, y);
	// hal->send_byte(hal_config, y);

	// hal->set_dc(hal_config, 1);
	// hal->send_byte(hal_config, 0x00);

	// hal->set_cs(hal_config, 1);
}

const eglib_display_4wire_spi_t eglib_display_4wire_spi_ssd1306 = {
	.hal_config_base = {
	    .mode = 0,
	    .bit_numbering = EGLIB_HAL_4WIRE_SPI_MSB_FIRST,
	    .cs_setup_ns = 20,
	    .cs_hold_ns = 10,
	    .cs_disable_ns = 0,
	    .dc_setup_ns = 15,
	    .dc_hold_ns = 15,
	    .sck_cycle_ns = 100,
	    .mosi_setup_ns = 15,
	    .mosi_hold_ns = 15,
	},
	.power_up = power_up,
	.power_down = power_down,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel = draw_pixel,
};