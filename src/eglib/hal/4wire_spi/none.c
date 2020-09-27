#include "none.h"

static void init(eglib_hal_4wire_spi_config_t *config) {
	(void)config;
}

static void sleep_in(eglib_hal_4wire_spi_config_t *config) {
	(void)config;
}

static void sleep_out(eglib_hal_4wire_spi_config_t *config) {
	(void)config;
}

static void delay_ns(eglib_hal_4wire_spi_config_t *config, uint32_t ns) {
	(void)config;
	(void)ns;
}

static void set_reset(eglib_hal_4wire_spi_config_t *config, uint8_t state) {
	(void)config;
	(void)state;
}

static void set_dc(eglib_hal_4wire_spi_config_t *config, uint8_t state) {
	(void)config;
	(void)state;
}

static void set_cs(eglib_hal_4wire_spi_config_t *config, uint8_t state) {
	(void)config;
	(void)state;
}

static void send_byte(eglib_hal_4wire_spi_config_t *config, uint8_t byte) {
	(void)config;
	(void)byte;
}

const eglib_hal_4wire_spi_t eglib_hal_4wire_spi_none = {
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.set_dc = set_dc,
	.set_cs = set_cs,
	.send_byte = send_byte,
};