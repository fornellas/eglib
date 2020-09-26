#ifndef EGLIB_DISPLAY_4WIRE_SPI_SH1106_H
#define EGLIB_DISPLAY_4WIRE_SPI_SH1106_H

#include "../4wire_spi.h"
#include "../../../eglib.h"

#define SH1106_SEGMENT_REMAP_NORMAL 0
#define SH1106_SEGMENT_REMAP_REVERSE 1

#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_SEQUENTIAL 0
#define SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_ALTERNATIVE 1

#define SH1106_COMMON_OUTPUT_SCAN_DIRECTION_ASC 0
#define SH1106_COMMON_OUTPUT_SCAN_DIRECTION_DESC 1

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

#define SHH1106_DC_DC_6_4_V 0x0
#define SHH1106_DC_DC_7_4_V 0x1
#define SHH1106_DC_DC_8_0_V 0x2
#define SHH1106_DC_DC_9_0_V 0x3

typedef struct {
	//
	// Display physical construction
	//

	eglib_coordinate_t width;
	eglib_coordinate_t height;
	// Mirror horizontally: SH1106_SEGMENT_REMAP_*
	uint8_t segment_remap : 1;
	// SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_*
	uint8_t common_pads_hardware_configuration_mode : 1;
	// Mirror vertically: SH1106_COMMON_OUTPUT_SCAN_DIRECTION_*
	uint8_t common_output_scan_direction : 1;
	// Vertical offset
	uint8_t display_offset : 6;
	// Horizontal offset
	uint8_t column_offset;
	// Change period
	uint8_t pre_charge_period : 4;
	uint8_t dis_charge_period : 4;
	// VCOM deselect
	uint8_t vcom_deselect_level;  // POR 0x35
	// Internal display clocks
	uint8_t clock_divide : 4;  // 1-16
	uint8_t oscillator_frequency : 4;  // SH1106_OSCILLATOR_FREQUENCY_*
	// Charge Pump Regulator
	uint8_t dc_dc_enable : 1;
	uint8_t dc_dc_voltage : 2;  // SHH1106_DC_DC_*
} eglib_display_4wire_spi_sh1106_config_t;

// VDD1 = 1.65 - 3.5V, TA= +25°C
extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_1_65_v;
// VDD1 = 2.4 - 3.5V, TA= +25°C
extern const eglib_display_4wire_spi_t eglib_display_4wire_spi_sh1106_vdd1_2_4_v;

void eglib_display_4wire_spi_sh1106_set_start_line(eglib_t *eglib, uint8_t line);
void eglib_display_4wire_spi_sh1106_set_contrast(eglib_t *eglib, uint8_t contrast);
void eglib_display_4wire_spi_sh1106_entire_display_on(eglib_t *eglib, uint8_t entire_display_on);
void eglib_display_4wire_spi_sh1106_reverse(eglib_t *eglib, uint8_t reverse);

#endif