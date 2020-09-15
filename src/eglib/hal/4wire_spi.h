#ifndef EGLIB_HAL_4WIRE_SPI_H
#define EGLIB_HAL_4WIRE_SPI_H

#include <stdint.h>

typedef struct {
	void (*power_up)(void *hal_4wire_spi_config);
	void (*power_down)(void *hal_4wire_spi_config);
	void (*delay_ms)(void *hal_4wire_spi_config, uint32_t ms);
	void (*set_reset)(void *hal_4wire_spi_config, uint8_t state);
	void (*set_cd)(void *hal_4wire_spi_config, uint8_t state);
	void (*set_cs)(void *hal_4wire_spi_config, uint8_t state);
	void (*send_byte)(void *hal_4wire_spi_config, uint8_t byte);
} eglib_hal_4wire_spi_t;

#endif