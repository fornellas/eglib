#include "libopencm3_stm32f4.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include "../common/libopencm3/stm32f4/delay.c"

//
// Helpers
//

static void set_cs(
	eglib_t *eglib,
	bool state
) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;
	hal_parallel_8_bit_8080_config_t *parallel_8_bit_8080_config_comm;

	config = eglib_GetHalConfig(eglib);
	parallel_8_bit_8080_config_comm = eglib_GetHalParallel8bit8080ConfigComm(eglib);

	if(state) {
		_delay_ns(parallel_8_bit_8080_config_comm->csx_hold_ns);
		gpio_set(
			config->port_csx,
			config->gpio_csx
		);
		_delay_ns(parallel_8_bit_8080_config_comm->csx_disable_ns);
	} else {
		gpio_clear(
			config->port_csx,
			config->gpio_csx
		);
		_delay_ns(parallel_8_bit_8080_config_comm->csx_setup_ns);
	}
}

static void set_dc(
	eglib_t *eglib,
	bool state
) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;
	hal_parallel_8_bit_8080_config_t *parallel_8_bit_8080_config_comm;

	config = eglib_GetHalConfig(eglib);
	parallel_8_bit_8080_config_comm = eglib_GetHalParallel8bit8080ConfigComm(eglib);

	if(state) {
		gpio_set(
			config->port_dcx,
			config->gpio_dcx
		);
		_delay_ns(parallel_8_bit_8080_config_comm->dcx_setup_ns);
	} else
		gpio_clear(
			config->port_dcx,
			config->gpio_dcx
		);
}

static void cycle_wrx(eglib_t * eglib) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;
	hal_parallel_8_bit_8080_config_t *parallel_8_bit_8080_config_comm;

	config = eglib_GetHalConfig(eglib);
	parallel_8_bit_8080_config_comm = eglib_GetHalParallel8bit8080ConfigComm(eglib);

	gpio_clear(
		config->port_wrx,
		config->gpio_wrx
	);
	_delay_ns(parallel_8_bit_8080_config_comm->wrx_low_ns);
	gpio_set(
		config->port_wrx,
		config->gpio_wrx
	);
	_delay_ns(
		parallel_8_bit_8080_config_comm->wrx_cycle_ns
		- parallel_8_bit_8080_config_comm->wrx_low_ns
	);
}

//
// Driver
//

static void init(
	eglib_t *eglib
) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;

	config = eglib_GetHalConfig(eglib);

	if(config->rcc_rst) {
		rcc_periph_clock_enable(config->rcc_rst);
		gpio_mode_setup(
			config->port_rst,
			GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE,
			config->gpio_rst
		);
	}

	if(config->rcc_busy) {
		rcc_periph_clock_enable(config->rcc_busy);
		gpio_mode_setup(
			config->port_busy,
			GPIO_MODE_INPUT,
			GPIO_PUPD_NONE,
			config->gpio_busy
		);
	}

	rcc_periph_clock_enable(config->rcc_csx);
	gpio_mode_setup(
		config->port_csx,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		config->gpio_csx
	);

	rcc_periph_clock_enable(config->rcc_dcx);
	gpio_mode_setup(
		config->port_dcx,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		config->gpio_dcx
	);

	rcc_periph_clock_enable(config->rcc_wrx);
	gpio_mode_setup(
		config->port_wrx,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		config->gpio_wrx
	);

	rcc_periph_clock_enable(config->rcc_data);
	gpio_mode_setup(
		config->port_data,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		GPIO0|GPIO1|GPIO2|GPIO3|GPIO4|GPIO5|GPIO6|GPIO7
	);

	set_cs(eglib, true);
}

static void sleep_in(
	eglib_t *eglib
) {
	(void)eglib;
}

static void sleep_out(
	eglib_t *eglib
) {
	(void)eglib;
}

static void delay_ns(
	eglib_t *eglib,
	volatile uint32_t ns
) {
	(void)eglib;

	_delay_ns(ns);
}

static void set_reset(
	eglib_t *eglib,
	bool state
) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;

	config = eglib_GetHalConfig(eglib);

	if(!(config->rcc_rst))
		return;

	if(state)
		gpio_set(config->port_rst, config->gpio_rst);
	else
		gpio_clear(config->port_rst, config->gpio_rst);
}

static bool get_busy(eglib_t *eglib) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;

	config = eglib_GetHalConfig(eglib);

	return gpio_get(config->port_busy, config->gpio_busy);
}

static void comm_begin(eglib_t *eglib) {
	set_cs(eglib, false);
}

static void send(
	eglib_t *eglib,
	enum hal_dc_t dc,
	uint8_t *bytes,
	uint32_t length
) {
	parallel_8_bit_8080_libopencm3_stm32f4_config_t *config;

	config = eglib_GetHalConfig(eglib);

	set_dc(eglib, dc);

	for(;length;bytes++,length--) {
		gpio_port_write(
			config->port_data,
			(gpio_port_read(config->port_data) & 0xff00) | (*bytes)
		);
		cycle_wrx(eglib);
	}
}

static void comm_end(eglib_t *eglib) {
	set_cs(eglib, true);
}

const hal_t parallel_8_bit_8080_libopencm3_stm32f4 = {
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.get_busy = get_busy,
	.comm_begin = comm_begin,
	.send = send,
	.comm_end = comm_end,
};