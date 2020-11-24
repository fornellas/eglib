#include "../eglib.h"

#ifndef EGLIB_HAL_H
#define EGLIB_HAL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  EGLIB_HAL_COMMAND,
  EGLIB_HAL_DATA,
} hal_dc_t;

typedef enum {
  EGLIB_HAL_LSB_FIRST,
  EGLIB_HAL_MSB_FIRST,
} hal_bit_numbering_t;

// 4-Wire SPI

typedef struct {
	// SPI Mode
	// 0: CPOL=0, CPHA=0
	// 1: CPOL=0, CPHA=1
	// 2: CPOL=1, CPHA=0
	// 3: CPOL=1, CPHA=1
	uint8_t mode;

	// MSB / LSB first
	hal_bit_numbering_t bit_numbering;

	// Delay after CS asserted
	uint32_t cs_setup_ns;
	// Delay before de-asserting CS
	uint32_t cs_hold_ns;
	// Delay after de-asserting CS
	uint32_t cs_disable_ns;

	// Delay before changing DC
	uint32_t dc_setup_ns;
	// Delay after changing DC
	uint32_t dc_hold_ns;

	// SCK Period (1/frequency*10^9)
	uint32_t sck_cycle_ns;
} hal_four_wire_spi_config_comm_t;

// I2C

typedef enum {
  EGLIB_HAL_I2C_100KHZ,
  EGLIB_HAL_I2C_400KHZ,
} hal_i2c_speed_t;

typedef struct {
	hal_i2c_speed_t speed;
	uint8_t (*get_7bit_slave_addr)(eglib_t *eglib, hal_dc_t dc);
	void (*send)(
		eglib_t *eglib,
		void (*i2c_write)(eglib_t *eglib, uint8_t byte),
		hal_dc_t dc,
		uint8_t *bytes,
		uint32_t length
	);
} hal_i2c_config_comm_t;

// Common

struct _hal;
typedef struct _hal hal_t;

#include "../eglib.h"

struct _hal {
	void (*init)(eglib_t *eglib);
	void (*sleep_in)(eglib_t *eglib);
	void (*sleep_out)(eglib_t *eglib);
	void (*delay_ns)(eglib_t *eglib, uint32_t ns);
	void (*set_reset)(eglib_t *eglib, bool state);
	void (*comm_begin)(eglib_t *eglib);
	void (*send)(eglib_t *eglib, hal_dc_t dc, uint8_t *bytes, uint32_t length);
	void (*comm_end)(eglib_t *eglib);
	bool (*get_busy)(eglib_t *eglib);
};

#define hal_get_config(eglib) ((eglib)->hal_config_ptr)

#define hal_comm_active(eglib) ((eglib)->hal_comm_active)
#define hal_i2c_send_slave_addr(eglib) ((eglib)->hal_i2c_send_slave_addr)

#define hal_delay_ns(eglib, ns) ((eglib)->hal->delay_ns(eglib, ns))
#define hal_delay_ms(eglib, ns) ((eglib)->hal->delay_ns(eglib, ns * 1000 * 1000))
#define hal_set_reset(eglib, state) ((eglib)->hal->set_reset(eglib, state))
void hal_comm_begin(eglib_t *eglib);
void hal_send(eglib_t *eglib, hal_dc_t dc, uint8_t *bytes, uint32_t length);
#define hal_send_data(eglib, bytes, length) (\
	hal_send(eglib, EGLIB_HAL_DATA, bytes, length)\
)
#define hal_send_data_byte(eglib, bytes) (\
	hal_send_data(eglib, &((uint8_t){bytes}), 1)\
)
#define hal_send_commands(eglib, bytes, length) (\
	hal_send(eglib, EGLIB_HAL_COMMAND, bytes, length)\
)
#define hal_send_command_byte(eglib, bytes) (\
	hal_send_commands(eglib, &((uint8_t){bytes}), 1)\
)
void hal_comm_end(eglib_t *eglib);
#define hal_get_busy(eglib) ((eglib)->hal->get_busy(eglib))
#define hal_wait_not_busy(eglib) while(!(hal_get_busy(eglib)))

#endif