#ifndef EGLIB_HAL_I2C_LIBOPENCM3_STM32F4_H
#define EGLIB_HAL_I2C_LIBOPENCM3_STM32F4_H

#include "../../hal.h"
#include <libopencm3/stm32/rcc.h>

typedef struct {
	// rst
	enum rcc_periph_clken rcc_rst;
	uint32_t port_rst;
	uint16_t gpio_rst;
	// i2c
	enum rcc_periph_clken rcc_gpio_i2c;
	uint32_t port_i2c;
	uint16_t gpio_scl;
	uint16_t gpio_sda;
	enum rcc_periph_clken rcc_i2c;
	uint32_t i2c;
	uint32_t peripheral_clock_mhz;

	// TODO I2C Filter
} eglib_hal_i2c_libopencm3_stm32f4_config_t;

extern const eglib_hal_t eglib_hal_i2c_libopencm3_stm32f4;

#endif