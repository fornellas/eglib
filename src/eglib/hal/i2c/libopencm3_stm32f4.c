#include "libopencm3_stm32f4.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include "../common/libopencm3/stm32f4/delay.c"

//
// Helpers
//

static void init_io(eglib_t *eglib) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	rcc_periph_clock_enable(config->rcc_gpio_i2c);

	gpio_mode_setup(
		config->port_i2c,
		GPIO_MODE_AF,
		GPIO_PUPD_PULLUP,
		config->gpio_scl | config->gpio_sda
	);
	gpio_set_output_options(
		config->port_i2c,
		GPIO_OTYPE_OD,
		GPIO_OSPEED_50MHZ,
		config->gpio_scl | config->gpio_sda
	);
	gpio_set_af(
		config->port_i2c,
		GPIO_AF4,
		config->gpio_scl | config->gpio_sda
	);
}

static void init_peripheral(eglib_t *eglib) {
	i2c_libopencm3_stm32f4_config_t *config;
	enum i2c_speeds speed = i2c_speed_sm_100k;

	config = hal_get_config(eglib);

	rcc_periph_clock_enable(config->rcc_i2c);

	i2c_peripheral_disable(config->i2c);

	i2c_reset(config->i2c);

	switch(display_get_hal_i2c_config_comm(eglib)->speed) {
		case EGLIB_HAL_I2C_100KHZ:
			speed = i2c_speed_sm_100k;
			break;
		case EGLIB_HAL_I2C_400KHZ:
			speed = i2c_speed_fm_400k;
			break;
	}

	i2c_set_speed(config->i2c, speed, config->peripheral_clock_mhz);

	// TODO
	// I2C_FLTR(config->i2c) = (I2C_FLTR(config->i2c) & ~I2C_FLTR_DNF_MASK) | (15<<I2C_FLTR_DNF_SHIFT);

	i2c_peripheral_enable(config->i2c);
}

static bool i2c_has_error(eglib_t *eglib) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	if(
		I2C_SR1(config->i2c) & (
			I2C_SR1_BERR
			| I2C_SR1_ARLO
			| I2C_SR1_AF
			| I2C_SR1_OVR
			| I2C_SR1_PECERR
			| I2C_SR1_TIMEOUT
			| I2C_SR1_SMBALERT
		)
	) {
		init_peripheral(eglib);
		return true;
	}
	return false;
}

static void send_slave_address(eglib_t *eglib, hal_dc_t dc) {
	i2c_libopencm3_stm32f4_config_t *config;
	uint8_t seven_bit_slave_addr;

	config = hal_get_config(eglib);

	// write in the DR register with the Slave address
	seven_bit_slave_addr = display_get_i2c_7bit_slave_addr(eglib, dc);
	i2c_send_7bit_address(config->i2c, seven_bit_slave_addr, I2C_WRITE);

	// As soon as the address byte is sent
	// The ADDR bit is set by hardware and an interrupt is generated if the
	// ITEVFEN bit is set.
	// Then the master waits for a read of the SR1 register
	while(!(I2C_SR1(config->i2c) & I2C_SR1_ADDR))
		if(i2c_has_error(eglib))
			return;

	// followed by a read of the SR2 register
	(void)I2C_SR2(config->i2c);
}

static void i2c_write(eglib_t *eglib, uint8_t byte) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	i2c_send_data(config->i2c, byte);
	while (!(I2C_SR1(config->i2c) & (I2C_SR1_BTF)))
		if(i2c_has_error(eglib))
			return;
}

//
// Driver
//

static void init(
	eglib_t *eglib
) {
	init_io(eglib);
	init_peripheral(eglib);
}

static void sleep_in(
	eglib_t *eglib
) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	i2c_peripheral_disable(config->i2c);
}

static void sleep_out(
	eglib_t *eglib
) {
	init_peripheral(eglib);
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
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	if(state)
		gpio_set(
			config->port_rst,
			config->gpio_rst
		);
	else
		gpio_clear(
			config->port_rst,
			config->gpio_rst
		);
}

static void comm_begin(eglib_t *eglib) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	// Setting the START bit
	i2c_send_start(config->i2c);
	// when the BUSY bit is cleared
	if(!hal_comm_active(eglib))
		while((I2C_SR2(config->i2c) & I2C_SR2_BUSY))
			if(i2c_has_error(eglib))
				return;
	// causes the interface to switch to Master mode (MSL bit set)
	while(!(I2C_SR2(config->i2c) & I2C_SR2_MSL))
		if(i2c_has_error(eglib))
			return;
	// causes the interface to generate a Start condition
	// master waits for a read of the SR1
	while(!(I2C_SR1(config->i2c) & I2C_SR1_SB))
		if(i2c_has_error(eglib))
			return;
}

static void send(
	eglib_t *eglib,
	hal_dc_t dc,
	uint8_t *bytes,
	uint16_t length
) {
	if(hal_i2c_send_slave_addr(eglib))
		send_slave_address(eglib, dc);

	display_i2c_send(eglib, i2c_write, dc, bytes, length);
}

static void comm_end(eglib_t *eglib) {
	i2c_libopencm3_stm32f4_config_t *config;

	config = hal_get_config(eglib);

	// Clears ADDR
	(void)I2C_SR2(config->i2c);

	i2c_send_stop(config->i2c);
}

const hal_t i2c_libopencm3_stm32f4 = {
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.comm_begin = comm_begin,
	.send = send,
	.comm_end = comm_end,
};