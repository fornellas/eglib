#ifndef EGLIB_HAL_H
#define EGLIB_HAL_H

#include "../eglib.h"
#include <stdint.h>
#include <stdbool.h>

/** Type of bytes transmitted */
typedef enum {
	/** Command */
	HAL_COMMAND,
	/** Data */
	HAL_DATA,
} hal_dc_t;

/** Endianness */
typedef enum {
	/** Big-endian (most significant bit first) */
	HAL_LSB_FIRST,
	/** Little-endian (least significant bit first) */
	HAL_MSB_FIRST,
} hal_bit_numbering_t;

/**
 * 4-Wire SPI configuration.
 *
 * See :c:type:`display_struct`.
 */
typedef struct {
	/**
	 * SPI Mode:
	 *  - 0: CPOL=0, CPHA=0
	 *  - 1: CPOL=0, CPHA=1
	 *  - 2: CPOL=1, CPHA=0
	 *  - 3: CPOL=1, CPHA=1
	 */
	uint8_t mode;

	/** Endianness */
	hal_bit_numbering_t bit_numbering;

	/** Delay after CS asserted */
	uint32_t cs_setup_ns;
	/** Delay before de-asserting CS */
	uint32_t cs_hold_ns;
	/** Delay after de-asserting CS */
	uint32_t cs_disable_ns;

	/** Delay before changing DC */
	uint32_t dc_setup_ns;
	/** Delay after changing DC */
	uint32_t dc_hold_ns;

	/** SCK Period (1/frequency*10^9) */
	uint32_t sck_cycle_ns;
} hal_four_wire_spi_config_t;

/**
 * I2C Speed.
 *
 * See :c:type:`hal_i2c_config_t`.
 */
typedef enum {
	/** 100kHz */
	HAL_I2C_100KHZ,
	/** 400kHz */
	HAL_I2C_400KHZ,
} hal_i2c_speed_t;

/**
 * I2C Configuration.
 *
 * See :c:type:`display_struct`.
 */
typedef struct {
	/** I2C Speed */
	hal_i2c_speed_t speed;
	/**
	 * Pointer to a function that returns the 7-bit slave address of the display.
	 *
	 * Some displays have fixed addresses, others have addresses configurable
	 * depending on the state of its I/O pins and some have different addresses
	 * whether command or data is being sent.
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param dc: Whether address command or data (:c:type:`hal_dc_t`).
	 *
	 * See :c:type:`hal_dc_t`.
	 */
	uint8_t (*get_7bit_slave_addr)(eglib_t *eglib, hal_dc_t dc);
	/**
	 * Pointer to a function that implements the display specific manipulation
	 * of the I2C byte stream required. This is called when needed by the
	 * I2C HAL driver (:c:type:`hal_struct`).
	 *
	 * Some examples of what may be required by a display:
	 *
	 *  - First send a byte informing whether the following bytes are data or
	 *    command.
	 *  - Issue an I2C restart at the end of transmission (by calling
	 *    :c:func:`hal_CommBegin`).
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param i2c_write: Pointer to a function that sends the passed byte via
	 *                   I2C.
	 * :param dc: Whether bytes are command or data (:c:type:`hal_dc_t`).
	 * :param bytes: Pointer to an array of bytes to send.
	 * :param length: Number of bytes to send.
	 */
	void (*send)(
		eglib_t *eglib,
		void (*i2c_write)(eglib_t *eglib, uint8_t byte),
		hal_dc_t dc,
		uint8_t *bytes,
		uint32_t length
	);
} hal_i2c_config_t;

/**
 * HAL driver definition.
 *
 * :note: :c:func:`hal_GetConfig` can be used to retrieve the HAL driver
 *  configuration.
 *
 * Aliased as :c:type:`hal_t`.
 */
struct hal_struct {
	/**
	 * Pointer to a function that initializes the peripheral based on:
	 *
	 *  - The HAL driver configuration (:c:func:`hal_GetConfig`).
	 *  - The Display driver (:c:func:`display_GetHalFourWireSpiConfigComm`)
	 */
	void (*init)(eglib_t *eglib);
	/** Pointer to a function that puts the peripheral in sleep mode. */
	void (*sleep_in)(eglib_t *eglib);
	/** Pointer to a function that puts the peripheral out of sleep mode */
	void (*sleep_out)(eglib_t *eglib);
	/**
	 * Pointer to a function that delays for given amount of nanoseconds.
	 *
	 * Can be called from the display driver (:c:type:`display_struct`) with
	 * :c:func:`hal_DelayNs`.
	 */
	void (*delay_ns)(eglib_t *eglib, uint32_t ns);
	/**
	 * Pointer to a function that sets the reset pin to given ``state``.
	 *
	 * Can be called from the display driver (:c:type:`display_struct`) with
	 * :c:func:`hal_SetReset`.
	 */
	void (*set_reset)(eglib_t *eglib, bool state);
	/**
	 * Pointer to a function that begins communication. The meaning of this
	 * function varies depending on the bus:
	 *
	 *  - **4-Wire SPI**: asserts CS.
	 *  - **I2C**: sends start condition.
	 *    - When called more than one time before ending communication
	 *    (:c:func:`hal_CommEnd`) sends restart condition.
	 *
	 * Can be called from the display driver (:c:type:`display_struct`) with
	 * :c:func:`hal_CommBegin`.
	 */
	void (*comm_begin)(eglib_t *eglib);
	// hal_ShouldSendI2cSlaveAddr
	/**
	 * Sends data. Depending on the bus, additional things must happen prior to
	 * sending the data:
	 *
	 *  - **4-Wire SPI**: Set data or command line.
	 *  - **I2C**: if :c:func:`hal_ShouldSendI2cSlaveAddr` returns true then the
	 *    slave address must be sent.
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param dc: Whether bytes are command or data (:c:type:`hal_dc_t`).
	 * :param bytes: Pointer to an array of bytes to send.
	 * :param length: Number of bytes to send.
	 *
	 * Can be called from the display driver (:c:type:`display_struct`) with
	 * :c:func:`hal_Send`.
	 */
	void (*send)(eglib_t *eglib, hal_dc_t dc, uint8_t *bytes, uint32_t length);
	/**
	 * Ends communication. The meaning of this function varies depending on the
	 * bus:
	 *
	 *  - **4-Wire SPI**: de-asserts CS.
	 *  - **I2C**: sends stop condition.
	 *
	 * Can be called from the display driver (:c:type:`display_struct`) with
	 * :c:func:`hal_CommEnd`.
	 */
	void (*comm_end)(eglib_t *eglib);
	bool (*get_busy)(eglib_t *eglib);
};

/**
 * Returns a pointer to the HAL driver configuration that was passed to
 * :c:func:`eglib_Init`.
 */
#define hal_GetConfig(eglib) ((eglib)->hal_config_ptr)

/**
 * Whether in between calls to :c:func:`hal_CommBegin` and :c:func:`hal_CommEnd`.
 */
#define hal_IsCommActive(eglib) ((eglib)->hal_comm_active)

/**
 * Whether I2C slave address should be sent.
 *
 * See ``send`` attribute at :c:type:`hal_struct`.
 */
#define hal_ShouldSendI2cSlaveAddr(eglib) ((eglib)->hal_i2c_send_slave_addr)

/** Delay for given number of nanoseconds */
#define hal_DelayNs(eglib, ns) ((eglib)->hal->delay_ns(eglib, ns))

/** Delay for given number of milliseconds */
#define hal_DelayMs(eglib, ns) ((eglib)->hal->delay_ns(eglib, ns * 1000 * 1000))

/** Set reset line to given state */
#define hal_SetReset(eglib, state) ((eglib)->hal->set_reset(eglib, state))

/** Initiates communication. Must be called before :c:func:`hal_Send`. */
void hal_CommBegin(eglib_t *eglib);

/**
 * Sends data. Must be called after :c:func:`hal_CommBegin`.
 *
 * :param eglib: :c:type:`eglib_t` handle.
 * :param dc: Whether bytes are command or data (:c:type:`hal_dc_t`).
 * :param bytes: Pointer to an array of bytes to send.
 * :param length: Number of bytes to send.
 */
void hal_Send(eglib_t *eglib, hal_dc_t dc, uint8_t *bytes, uint32_t length);

/**
 * Sends data.
 *
 * See :c:func:`hal_Send`.
 */
#define hal_SendData(eglib, bytes, length) (\
	hal_Send(eglib, HAL_DATA, bytes, length)\
)

/**
 * Sends a single data byte.
 *
 * See :c:func:`hal_Send`.
 */
#define hal_SendDataByte(eglib, bytes) (\
	hal_SendData(eglib, &((uint8_t){bytes}), 1)\
)

/**
 * Sends commands.
 *
 * See :c:func:`hal_Send`.
 */
#define hal_SendCommands(eglib, bytes, length) (\
	hal_Send(eglib, HAL_COMMAND, bytes, length)\
)

/**
 * Sends a single command byte.
 *
 * See :c:func:`hal_Send`.
 */
#define hal_SendCommandByte(eglib, bytes) (\
	hal_SendCommands(eglib, &((uint8_t){bytes}), 1)\
)

/** Ends communication. */
void hal_CommEnd(eglib_t *eglib);

/**
 * Get the value of th busy data line, often found in e-ink / e-paper displays.
 */
#define hal_GetBusy(eglib) ((eglib)->hal->get_busy(eglib))

/**
 * Busy wait until busy data line is high.
 *
 * See :c:func:`hal_GetBusy`.
 */
#define hal_WaitNotBusy(eglib) while(!(hal_GetBusy(eglib)))

#endif

#include "display.h"