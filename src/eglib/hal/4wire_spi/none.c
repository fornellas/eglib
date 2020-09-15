#include "none.h"

static void power_up(void *hal_4wire_spi_config) {

}

static void power_down(void *hal_4wire_spi_config) {

}

static void delay_ms(void *hal_4wire_spi_config, uint32_t ms) {

}

static void set_reset(void *hal_4wire_spi_config, uint8_t state) {

}

static void set_cd(void *hal_4wire_spi_config, uint8_t state) {

}

static void set_cs(void *hal_4wire_spi_config, uint8_t state) {

}

static void send_byte(void *hal_4wire_spi_config, uint8_t byte) {

}


const eglib_hal_4wire_spi_t eglib_hal_4wire_spi_none = {
	.power_up = power_up,
	.power_down = power_down,
	.delay_ms = delay_ms,
	.set_reset = set_reset,
	.set_cd = set_cd,
	.set_cs = set_cs,
	.send_byte = send_byte,
};