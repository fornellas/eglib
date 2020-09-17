#include "none.h"

static void power_up(eglib_hal_4wire_spi_config_t *config) {

}

static void power_down(eglib_hal_4wire_spi_config_t *config) {

}

static void delay_ns(eglib_hal_4wire_spi_config_t *config, uint32_t ns) {

}

static void set_reset(eglib_hal_4wire_spi_config_t *config, uint8_t state) {

}

static void set_dc(eglib_hal_4wire_spi_config_t *config, uint8_t state) {

}

static void set_cs(eglib_hal_4wire_spi_config_t *config, uint8_t state) {

}

static void send_byte(eglib_hal_4wire_spi_config_t *config, uint8_t byte) {

}

const eglib_hal_4wire_spi_t eglib_hal_4wire_spi_none = {
	.power_up = power_up,
	.power_down = power_down,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.set_dc = set_dc,
	.set_cs = set_cs,
	.send_byte = send_byte,
};