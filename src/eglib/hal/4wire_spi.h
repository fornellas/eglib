#ifndef EGLIB_HAL_4WIRE_SPI_H
#define EGLIB_HAL_4WIRE_SPI_H

#include <stdint.h>

typedef enum {
  EGLIB_HAL_4WIRE_SPI_LSB_FIRST,
  EGLIB_HAL_4WIRE_SPI_MSB_FIRST,
} eglib_hal_4wire_spi_bit_numbering_t;

typedef struct {
	// SPI Mode
	// 0: CPOL=0, CPHA=0
	// 1: CPOL=0, CPHA=1
	// 2: CPOL=1, CPHA=0
	// 3: CPOL=1, CPHA=1
	uint8_t mode;

	// MSB / LSB first
	eglib_hal_4wire_spi_bit_numbering_t bit_numbering;

	// CS Timing
	uint32_t cs_setup_ns;
	uint32_t cs_hold_ns;
	uint32_t cs_disable_ns;

	// DC Timing
	uint32_t dc_setup_ns;
	uint32_t dc_hold_ns;

	// SCK Timing
	uint32_t sck_cycle_ns;

	// MOSI timing
	uint32_t mosi_setup_ns;
	uint32_t mosi_hold_ns;
} eglib_hal_4wire_spi_config_base_t;

typedef struct {
	const eglib_hal_4wire_spi_config_base_t *base;
	void *driver;
} eglib_hal_4wire_spi_config_t;

typedef struct {
	void (*init)(eglib_hal_4wire_spi_config_t *config);
	void (*sleep_in)(eglib_hal_4wire_spi_config_t *config);
	void (*sleep_out)(eglib_hal_4wire_spi_config_t *config);
	void (*delay_ns)(eglib_hal_4wire_spi_config_t *config, uint32_t ns);
	void (*set_reset)(eglib_hal_4wire_spi_config_t *config, uint8_t state);
	void (*set_dc)(eglib_hal_4wire_spi_config_t *config, uint8_t state);
	void (*set_cs)(eglib_hal_4wire_spi_config_t *config, uint8_t state);
	void (*send_byte)(eglib_hal_4wire_spi_config_t *config, uint8_t byte);
} eglib_hal_4wire_spi_t;

#endif