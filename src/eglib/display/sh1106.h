#ifndef EGLIB_DISPLAY_SH1106_H
#define EGLIB_DISPLAY_SH1106_H

#include "../hal.h"
#include "../../eglib.h"
#include <stdbool.h>

//
// Defines for sh1106_config_t
//

typedef enum {
	SH1106_SEGMENT_REMAP_NORMAL,
	SH1106_SEGMENT_REMAP_REVERSE,
} sh1106_segment_remap_t;

typedef enum {
	SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_SEQUENTIAL,
	SH1106_COMMON_PADS_HARDWARE_CONFIGURATION_ALTERNATIVE,
} sh1106_common_pads_hardware_configuration_t;

typedef enum {
	SH1106_COMMON_OUTPUT_SCAN_DIRECTION_ASC,
	SH1106_COMMON_OUTPUT_SCAN_DIRECTION_DESC,
} sh1106_common_output_scan_direction_t;

typedef enum {
	SH1106_OSCILLATOR_FREQUENCY_MINUS_25_PCT,
	SH1106_OSCILLATOR_FREQUENCY_MINUS_20_PCT,
	SH1106_OSCILLATOR_FREQUENCY_MINUS_15_PCT,
	SH1106_OSCILLATOR_FREQUENCY_MINUS_10_PCT,
	SH1106_OSCILLATOR_FREQUENCY_MINUS_5_PCT,
	SH1106_OSCILLATOR_FREQUENCY__0_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_5_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_10_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_15_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_20_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_25_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_30_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_35_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_40_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_45_PCT,
	SH1106_OSCILLATOR_FREQUENCY_PLUS_50_PCT,
} sh1106_oscillator_frequency_t;

typedef enum {
	SHH1106_DC_DC_6_4_V,
	SHH1106_DC_DC_7_4_V,
	SHH1106_DC_DC_8_0_V,
	SHH1106_DC_DC_9_0_V,
} sh1106_shh1106_dc_dc_t;

//
// sh1106_config_t
//

typedef struct {
	//
	// Display physical construction
	//

	coordinate_t width;
	coordinate_t height;
	// Mirror horizontally
	sh1106_segment_remap_t segment_remap : 1;
	// How rows (COM) and columns (SEG) are physically connected to the display.
	sh1106_common_pads_hardware_configuration_t common_pads_hardware_configuration : 1;
	// Mirror vertically
	sh1106_common_output_scan_direction_t common_output_scan_direction : 1;
	// Vertical offset
	uint8_t display_offset : 6;
	// Horizontal offset
	uint8_t column_offset;

	//
	// Change period
	//

	// 1-15 DCLKs ; POR: 2 CLKs
	uint8_t pre_charge_period : 4;
	// 1-15 DCLKs ; POR: 2 CLKs
	uint8_t dis_charge_period : 4;

	//
	// VCOM deselect
	//

	// POR: 0x35 (B=0x770)
	uint8_t vcom_deselect_level;

	//
	// Internal display clocks
	//

	// POR: 0x0 (divide ratio = 1)
	uint8_t clock_divide : 4;
	// POR: SH1106_OSCILLATOR_FREQUENCY__0_PCT
	sh1106_oscillator_frequency_t oscillator_frequency : 4;

	//
	// Charge Pump Regulator
	//

	bool dc_dc_enable : 1;
	// POR: SHH1106_DC_DC_8_0_V
	sh1106_shh1106_dc_dc_t dc_dc_voltage : 2;

	//
	// I2C
	//

	// Least significant bit of 7-bit slave address: 011110(sa0)
	bool sa0 : 1;
} sh1106_config_t;

// https://www.sparkfun.com/products/13003
// Values from https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library/blob/master/src/SFE_MicroOLED.cpp
extern const sh1106_config_t sh1106_config_sparkfun_micro_oled;

//
// display_t
//

// VDD1 = 1.65 - 3.5V, TA= +25°C
extern const display_t sh1106_vdd1_1_65_v;
// VDD1 = 2.4 - 3.5V, TA= +25°C
extern const display_t sh1106_vdd1_2_4_v;

//
// Custom Functions
//

void sh1106_SetStartLine(eglib_t *eglib, uint8_t line);

void sh1106_SetContrast(eglib_t *eglib, uint8_t contrast);

void sh1106_EntireDisplayOn(eglib_t *eglib, bool entire_display_on);

void sh1106_Reverse(eglib_t *eglib, bool reverse);

#endif