#include "libopencm3_stm32f4_spi.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

#define wait_spi_not_busy(spi) while(SPI_SR((uintptr_t)spi) & SPI_SR_BSY);


static void power_up(void *hal_config) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	rcc_periph_clock_enable(config->rcc_rst);
	gpio_mode_setup(config->port_rst, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config->gpio_rst);

	rcc_periph_clock_enable(config->rcc_cd);
	gpio_mode_setup(config->port_cd, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config->gpio_cd);

	rcc_periph_clock_enable(config->rcc_cs);
	gpio_mode_setup(config->port_cs, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config->gpio_cs);

	rcc_periph_clock_enable(config->rcc_sck);
	gpio_mode_setup(config->port_sck, GPIO_MODE_AF, GPIO_PUPD_NONE, config->gpio_sck);
	gpio_set_af(config->port_sck, GPIO_AF5, config->gpio_sck);

	rcc_periph_clock_enable(config->rcc_mosi);
	gpio_mode_setup(config->port_mosi, GPIO_MODE_AF, GPIO_PUPD_NONE, config->gpio_mosi);
	gpio_set_af(config->port_mosi, GPIO_AF5, config->gpio_mosi);

	rcc_periph_clock_enable(config->rcc_spi);

	spi_init_master(
		config->spi,
		config->br,
		config->cpol,
		config->cpha,
		config->dff,
		config->lsbfirst
	);
	spi_enable(config->spi);
}

static void power_down(void *hal_config) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	spi_disable(config->spi);
}

static void delay_ms(void *hal_config, uint32_t ms) {
	(void)hal_config;

    ms *= rcc_ahb_frequency / 1000 / 3;

    asm volatile(
		" mov r0, %[ms] \n\t"
		"1: subs r0, #1 \n\t"
		" bhi 1b \n\t"
		:
		: [ms] "r" (ms)
		: "r0"
	);
}

static void set_reset(void *hal_config, uint8_t state) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	wait_spi_not_busy(config->spi);
	if(state)
		gpio_set(config->port_rst, config->gpio_rst);
	else
		gpio_clear(config->port_rst, config->gpio_rst);
}

static void set_cd(void *hal_config, uint8_t state) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	wait_spi_not_busy(config->spi);
	if(state)
		gpio_set(config->port_cd, config->gpio_cd);
	else
		gpio_clear(config->port_cd, config->gpio_cd);
}

static void set_cs(void *hal_config, uint8_t state) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	wait_spi_not_busy(config->spi);
	if(state)
		gpio_set(config->port_cs, config->gpio_cs);
	else
		gpio_clear(config->port_cs, config->gpio_cs);
}

static void send_byte(void *hal_config, uint8_t byte) {
	eglib_hal_libopencm3_stm32f4_spi_config_t *config = (eglib_hal_libopencm3_stm32f4_spi_config_t *)hal_config;

	spi_send(config->spi, byte);
}

const eglib_hal_t eglib_hal_libopencm3_stm32f4_spi = {
	.power_up = power_up,
	.power_down = power_down,
	.delay_ms = delay_ms,
	.set_reset = set_reset,
	.set_cd = set_cd,
	.set_cs = set_cs,
	.send_byte = send_byte,
};