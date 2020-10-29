#ifndef EGLIB_HAL_FOUR_WIRE_SPI_LIBOPENCM3_STM32F4_H
#define EGLIB_HAL_FOUR_WIRE_SPI_LIBOPENCM3_STM32F4_H

#include "../../hal.h"
#include <libopencm3/stm32/rcc.h>

typedef struct {
	// rst
	enum rcc_periph_clken rcc_rst;
	uint32_t port_rst;
	uint16_t gpio_rst;
	// dc
	enum rcc_periph_clken rcc_dc;
	uint32_t port_dc;
	uint16_t gpio_dc;
	// cs
	enum rcc_periph_clken rcc_cs;
	uint32_t port_cs;
	uint16_t gpio_cs;
	// spi
	enum rcc_periph_clken rcc_spi;
	uint32_t spi;
	// sck
	enum rcc_periph_clken rcc_sck;
	uint32_t port_sck;
	uint16_t gpio_sck;
	// mosi
	enum rcc_periph_clken rcc_mosi;
	uint32_t port_mosi;
	uint16_t gpio_mosi;
} eglib_hal_four_wire_spi_libopencm3_stm32f4_config_t;

extern const eglib_hal_t eglib_hal_four_wire_spi_libopencm3_stm32f4;

#endif