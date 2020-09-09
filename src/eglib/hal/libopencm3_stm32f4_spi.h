#ifndef EGLIB_COMM_LIBOPENCM3_STM32F4_H
#define EGLIB_COMM_LIBOPENCM3_STM32F4_H

#include "../../eglib.h"
#include <libopencm3/stm32/rcc.h>

typedef struct {
	// rst
	enum rcc_periph_clken rcc_rst;
	uint32_t port_rst;
	uint16_t gpio_rst;
	// cd
	enum rcc_periph_clken rcc_cd;
	uint32_t port_cd;
	uint16_t gpio_cd;
	// cs
	enum rcc_periph_clken rcc_cs;
	uint32_t port_cs;
	uint16_t gpio_cs;
	// spi
	enum rcc_periph_clken rcc_spi;
	uint32_t spi;
	uint32_t br;
	uint32_t cpol;
	uint32_t cpha;
	uint32_t dff;
	uint32_t lsbfirst ;
	// sck
	enum rcc_periph_clken rcc_sck;
	uint32_t port_sck;
	uint16_t gpio_sck;
	// mosi
	enum rcc_periph_clken rcc_mosi;
	uint32_t port_mosi;
	uint16_t gpio_mosi;
} eglib_hal_libopencm3_stm32f4_spi_config_t;

extern const eglib_hal_t eglib_hal_libopencm3_stm32f4_spi;

#endif