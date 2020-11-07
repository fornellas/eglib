#ifndef EGLIB_HAL_H
#define EGLIB_HAL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  EGLIB_HAL_BUS_FOUR_WIRE_SPI,
  EGLIB_HAL_BUS_I2C,
} eglib_hal_bus_t;

// 4-Wire SPI

typedef enum {
  EGLIB_HAL_FOUR_WIRE_SPI_LSB_FIRST,
  EGLIB_HAL_FOUR_WIRE_SPI_MSB_FIRST,
} eglib_hal_four_wire_spi_bit_numbering_t;

typedef struct {
	// SPI Mode
	// 0: CPOL=0, CPHA=0
	// 1: CPOL=0, CPHA=1
	// 2: CPOL=1, CPHA=0
	// 3: CPOL=1, CPHA=1
	uint8_t mode;

	// MSB / LSB first
	eglib_hal_four_wire_spi_bit_numbering_t bit_numbering;

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
} eglib_hal_four_wire_spi_config_comm_t;

// I2C

typedef enum {
  EGLIB_HAL_I2C_100KHZ,
  EGLIB_HAL_I2C_400KHZ,
} eglib_hal_i2c_speed_t;

typedef struct {
	eglib_hal_i2c_speed_t speed;
} eglib_hal_i2c_config_comm_t;

// Common

typedef struct {
	union {
		eglib_hal_four_wire_spi_config_comm_t *four_wire_spi;
		eglib_hal_i2c_config_comm_t *i2c;
	} comm;
	void *driver_config_ptr;
} eglib_hal_config_t;

typedef enum {
  EGLIB_HAL_COMMAND,
  EGLIB_HAL_DATA,
} eglib_hal_dc_t;

struct _eglib_hal;
typedef struct _eglib_hal eglib_hal_t;

#include "../eglib.h"

struct _eglib_hal {
	eglib_hal_bus_t bus;
	void (*init)(eglib_t *eglib);
	void (*sleep_in)(eglib_t *eglib);
	void (*sleep_out)(eglib_t *eglib);
	void (*delay_ns)(eglib_t *eglib, uint32_t ns);
	void (*set_reset)(eglib_t *eglib, bool state);
	void (*comm_begin)(eglib_t *eglib);
	void (*send)(
		eglib_t *eglib,
		eglib_hal_dc_t dc,
		uint8_t *bytes,
		uint16_t length
	);
	void (*comm_end)(eglib_t *eglib);
};

#define eglib_hal_init(eglib) (eglib->hal->init(eglib))
#define eglib_hal_sleep_in(eglib) (eglib->hal->sleep_in(eglib))
#define eglib_hal_sleep_out(eglib) (eglib->hal->sleep_out(eglib))
#define eglib_hal_delay_ns(eglib, ns) (eglib->hal->delay_ns(eglib, ns))
#define eglib_hal_delay_ms(eglib, ns) (eglib->hal->delay_ns(eglib, ns * 1000 * 1000))
#define eglib_hal_set_reset(eglib, state) (eglib->hal->set_reset(eglib, state))
#define eglib_hal_comm_begin(eglib) (eglib->hal->comm_begin(eglib))
#define eglib_hal_send(eglib, dc, bytes, length) (\
	eglib->hal->send(eglib, dc, bytes, length)\
)
#define eglib_hal_send_data(eglib, bytes, length) (\
	eglib->hal->send(eglib, EGLIB_HAL_DATA, bytes, length)\
)
#define eglib_hal_send_data_literal(eglib, bytes) (\
	eglib->hal->send(eglib, EGLIB_HAL_DATA, &((uint8_t){bytes}), 1)\
)
#define eglib_hal_send_command(eglib, bytes, length) (\
	eglib->hal->send(eglib, EGLIB_HAL_COMMAND, bytes, length)\
)
#define eglib_hal_send_command_literal(eglib, bytes) (\
	eglib->hal->send(eglib, EGLIB_HAL_COMMAND, &((uint8_t){bytes}), 1)\
)
#define eglib_hal_comm_end(eglib) eglib->hal->comm_end(eglib)

#endif