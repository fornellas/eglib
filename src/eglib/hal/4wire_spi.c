#include "4wire_spi.h"

void eglib_hal_4wire_spi_delay_ns(eglib_t *eglib, uint32_t ns) {
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;

	hal = (eglib_hal_4wire_spi_t *)eglib->drivers.four_wire_spi.hal;
	hal_config = &(eglib->drivers.four_wire_spi.hal_config);

	hal->delay_ns(hal_config, ns);
}

void eglib_hal_4wire_spi_set_reset(eglib_t *eglib, bool state) {
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;

	hal = (eglib_hal_4wire_spi_t *)eglib->drivers.four_wire_spi.hal;
	hal_config = &(eglib->drivers.four_wire_spi.hal_config);

	hal->set_reset(hal_config, state);
}

void eglib_hal_4wire_spi_set_dc(eglib_t *eglib, bool state) {
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;

	hal = (eglib_hal_4wire_spi_t *)eglib->drivers.four_wire_spi.hal;
	hal_config = &(eglib->drivers.four_wire_spi.hal_config);

	hal->set_dc(hal_config, state);
}

void eglib_hal_4wire_spi_set_cs(eglib_t *eglib, bool state) {
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;

	hal = (eglib_hal_4wire_spi_t *)eglib->drivers.four_wire_spi.hal;
	hal_config = &(eglib->drivers.four_wire_spi.hal_config);

	hal->set_cs(hal_config, state);
}

void eglib_hal_4wire_spi_send_byte(eglib_t *eglib, uint8_t byte) {
	const eglib_hal_4wire_spi_t *hal;
	eglib_hal_4wire_spi_config_t *hal_config;

	hal = (eglib_hal_4wire_spi_t *)eglib->drivers.four_wire_spi.hal;
	hal_config = &(eglib->drivers.four_wire_spi.hal_config);

	hal->send_byte(hal_config, byte);
}
