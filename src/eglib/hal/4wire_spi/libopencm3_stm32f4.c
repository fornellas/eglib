#include "libopencm3_stm32f4.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>

#define CLOCKS_PER_DELAY_LOOP 3
#define MAX(x,y) ((x) >= (y)) ? (x) : (y)

#define wait_spi_not_busy(spi) while(SPI_SR((uintptr_t)spi) & SPI_SR_BSY);

static void init(
	eglib_hal_4wire_spi_config_t *config
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;
	uint32_t serial_clk_hz;
	uint32_t br;
	uint32_t cpol = 0;
	uint32_t cpha = 0;
	uint32_t lsbfirst = 0;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_rst);
	gpio_mode_setup(
		libopencm3_stm32f4_config->port_rst,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		libopencm3_stm32f4_config->gpio_rst
	);

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_dc);
	gpio_mode_setup(
		libopencm3_stm32f4_config->port_dc,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		libopencm3_stm32f4_config->gpio_dc
	);

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_cs);
	gpio_mode_setup(
		libopencm3_stm32f4_config->port_cs,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		libopencm3_stm32f4_config->gpio_cs
	);

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_sck);
	gpio_mode_setup(
		libopencm3_stm32f4_config->port_sck,
		GPIO_MODE_AF,
		GPIO_PUPD_NONE,
		libopencm3_stm32f4_config->gpio_sck
	);
	gpio_set_af(
		libopencm3_stm32f4_config->port_sck,
		GPIO_AF5,
		libopencm3_stm32f4_config->gpio_sck
	);

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_mosi);
	gpio_mode_setup(
		libopencm3_stm32f4_config->port_mosi,
		GPIO_MODE_AF,
		GPIO_PUPD_NONE,
		libopencm3_stm32f4_config->gpio_mosi
	);
	gpio_set_af(
		libopencm3_stm32f4_config->port_mosi,
		GPIO_AF5,
		libopencm3_stm32f4_config->gpio_mosi
	);

	rcc_periph_clock_enable(libopencm3_stm32f4_config->rcc_spi);

	serial_clk_hz = 1000000000UL / (config->comm->sck_cycle_ns);
	if(serial_clk_hz < (rcc_ahb_frequency / 128))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_256;
	else if(serial_clk_hz < (rcc_ahb_frequency / 64))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_128;
	else if(serial_clk_hz < (rcc_ahb_frequency / 32))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_64;
	else if(serial_clk_hz < (rcc_ahb_frequency / 16))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_32;
	else if(serial_clk_hz < (rcc_ahb_frequency / 8))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_16;
	else if(serial_clk_hz < (rcc_ahb_frequency / 4))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_8;
	else if(serial_clk_hz < (rcc_ahb_frequency / 2))
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_4;
	else
		br = SPI_CR1_BAUDRATE_FPCLK_DIV_2;

	switch(config->comm->mode) {
		case 0:
			cpol = SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE;
			cpha = SPI_CR1_CPHA_CLK_TRANSITION_1;
			break;
		case 1:
			cpol = SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE;
			cpha = SPI_CR1_CPHA_CLK_TRANSITION_2;
			break;
		case 2:
			cpol = SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE;
			cpha = SPI_CR1_CPHA_CLK_TRANSITION_1;
			break;
		case 3:
			cpol = SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE;
			cpha = SPI_CR1_CPHA_CLK_TRANSITION_2;
			break;
	}

	switch(config->comm->bit_numbering) {
		case EGLIB_HAL_4WIRE_SPI_LSB_FIRST:
			lsbfirst = SPI_CR1_LSBFIRST;
			break;
		case EGLIB_HAL_4WIRE_SPI_MSB_FIRST:
			lsbfirst = SPI_CR1_MSBFIRST;
			break;
	}

	spi_init_master(
		libopencm3_stm32f4_config->spi,
		br,
		cpol,
		cpha,
		SPI_CR1_DFF_8BIT,
		lsbfirst
	);

	spi_enable(libopencm3_stm32f4_config->spi);
}

static void sleep_in(
	eglib_hal_4wire_spi_config_t *config
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	wait_spi_not_busy(libopencm3_stm32f4_config->spi);

	spi_disable(libopencm3_stm32f4_config->spi);
}

static void sleep_out(
	eglib_hal_4wire_spi_config_t *config
) {
	init(config);
}

inline static void _delay_ns(volatile uint32_t ns) {
	volatile uint32_t loop_count;

	loop_count = ns * (float)rcc_ahb_frequency / (CLOCKS_PER_DELAY_LOOP * 1000000000U);

	__asm__ volatile(
		" mov r0, %[loop_count] \n\t"
		"1: subs r0, #1 \n\t"
		" bhi 1b \n\t"
		:
		: [loop_count] "r" (loop_count)
		: "r0"
	);
}

static void delay_ns(
	eglib_hal_4wire_spi_config_t *config,
	volatile uint32_t ns
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	wait_spi_not_busy(libopencm3_stm32f4_config->spi);

	_delay_ns(ns);
}

static void set_reset(
	eglib_hal_4wire_spi_config_t *config,
	bool state
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	wait_spi_not_busy(libopencm3_stm32f4_config->spi);
	if(state)
		gpio_set(
			libopencm3_stm32f4_config->port_rst,
			libopencm3_stm32f4_config->gpio_rst
		);
	else
		gpio_clear(
			libopencm3_stm32f4_config->port_rst,
			libopencm3_stm32f4_config->gpio_rst
		);
}

static void set_dc(
	eglib_hal_4wire_spi_config_t *config,
	bool state
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	wait_spi_not_busy(libopencm3_stm32f4_config->spi);
	if(state)
		gpio_set(
			libopencm3_stm32f4_config->port_dc,
			libopencm3_stm32f4_config->gpio_dc
		);
	else
		gpio_clear(
			libopencm3_stm32f4_config->port_dc,
			libopencm3_stm32f4_config->gpio_dc
		);
	_delay_ns(config->comm->dc_setup_ns);
}

static void set_cs(
	eglib_hal_4wire_spi_config_t *config,
	bool state
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	wait_spi_not_busy(libopencm3_stm32f4_config->spi);
	if(state) {
		_delay_ns(MAX(config->comm->dc_setup_ns, config->comm->cs_hold_ns));
		gpio_set(
			libopencm3_stm32f4_config->port_cs,
			libopencm3_stm32f4_config->gpio_cs
		);
		_delay_ns(config->comm->cs_disable_ns);
	} else {
		gpio_clear(
			libopencm3_stm32f4_config->port_cs,
			libopencm3_stm32f4_config->gpio_cs
		);
		_delay_ns(config->comm->cs_setup_ns);
	}
}

static void send_byte(
	eglib_hal_4wire_spi_config_t *config,
	uint8_t byte
) {
	eglib_hal_4wire_spi_libopencm3_stm32f4_config_t *libopencm3_stm32f4_config;

	libopencm3_stm32f4_config = config->driver_config_ptr;

	spi_send(libopencm3_stm32f4_config->spi, byte);
}

const eglib_hal_4wire_spi_t eglib_hal_4wire_spi_libopencm3_stm32f4 = {
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.set_dc = set_dc,
	.set_cs = set_cs,
	.send_byte = send_byte,
};