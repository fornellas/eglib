#ifndef EGLIB_DISPLAY_H
#define EGLIB_DISPLAY_H

#include "../eglib.h"
#include "hal.h"

/**
 * Communication bus configuration required by the display.
 *
 * Buses net supported by the display can be set to ``NULL``.
 */
struct display_comm_struct {
	/** 4-Wire SPI */
	hal_four_wire_spi_config_t *four_wire_spi;
	/** I2C */
	hal_i2c_config_t *i2c;
};

/**
 * Display driver definition.
 *
 * Communication with the data bus can be done using these and other ``hal_*``
 * functions:
 *
 * - :c:func:`hal_DelayNs`.
 * - :c:func:`hal_SetReset`.
 * - :c:func:`hal_CommBegin`.
 * - :c:func:`hal_Send`.
 * - :c:func:`hal_CommEnd`.
 * - :c:func:`hal_GetBusy`.
 *
 * :note: :c:func:`display_GetConfig` can be used to retrieve the HAL driver
 *   configuration.
 *
 * Aliased as :c:type:`display_t`.
 */
struct display_struct {
	/** Communication bus configuration required by the display. */
	struct display_comm_struct comm;
	/**
	 * Pointer to a function that initializes the display based on the driver
	 * configuration (:c:func:`display_GetConfig`)
	 */
	void (*init)(eglib_t *eglib);
	/** Pointer to a function that puts the display in sleep mode. */
	void (*sleep_in)(eglib_t *eglib);
	/** Pointer to a function that puts the display out of sleep mode. */
	void (*sleep_out)(eglib_t *eglib);
	/**
	 * Pointer to a function that returns the display dimensions:
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param width: Pointer where to write display width to.
	 * :param height: Pointer where to write display height to.
	 * :return: ``void``.
	 */
	void (*get_dimension)(
		eglib_t *eglib,
		coordinate_t *width,
		coordinate_t *height
	);
	/**
	 * Pointer to a function that returns the pixel format used in-memory by
	 * the display.
	 *
	 * This is used by the frame buffer (:c:type:`eglib_Init_FrameBuffer`) to
	 * decide how to write pixels to the buffer, which will then be handled by
	 * the ``send_buffer`` function from :c:type:`display_struct`.
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param pixel_format: Pointer to :c:type:`pixel_format_t` where to write
	 *   pixel format to.
	 * :return: :c:type:`pixel_format_t`.
	 */
	void (*get_pixel_format)(eglib_t *eglib, pixel_format_t *pixel_format);
	/**
	 * Pointer to a function that that draws directly to the display memory at
	 * ``(x, y)`` using given ``color``.
	 *
	 * Some displays can not support this method. Eg: black and white displays,
	 * where each bit is a pixel, requires reading a whole byte from the display
	 * memory, changing the required bit and sending it back to the display
	 * memory. As Eglib does not support reading the display memory, such
	 * displays must implement this as an empty function:
	 * :c:type:`eglib_Init_FrameBuffer` can be used to interface with the
	 * display using a frame buffer.
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param x: X :c:type:`coordinate_t`.
	 * :param y: Y :c:type:`coordinate_t`.
	 * :param color: Color :c:type:`color_t`.
	 */
	void (*draw_pixel_color)(
		eglib_t *eglib,
		coordinate_t x,
		coordinate_t y,
		color_t color
	);
	/**
	 * Pointer to a function that sends given buffer to display memory.
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :param buffer: Pointer to the memory buffer to be sent. The format is
	 *   dependent on both :c:type:`pixel_format_t` from ``get_pixel_format``
	 *   and the display dimensions from ``get_dimension``.
	 * :param x: X :c:type:`coordinate_t` of data to be sent: X pixels lower
	 *    than ``x`` must not be sent to the display.
	 * :param y: Y :c:type:`coordinate_t` of data to be sent: Y pixels lower
	 *    than ``y`` must not be sent to the display.
	 * :param width: Width of data to be sent: X pixels greater than
	 *   ``x + width`` must not be sent to the display.
	 * :param height: Height of data to be sent: Y pixels greater than
	 *   ``y + height`` must not be sent to the display.
	 */
	void (*send_buffer)(
		eglib_t *eglib,
		void *buffer,
		coordinate_t x, coordinate_t y,
		coordinate_t width, coordinate_t height
	);
	/**
	 * Pointer to a function that refreshes the display image.
	 *
	 * This method is only relevant to displays such as e-ink / e-paper, where
	 * writing to the display memory (``draw_pixel_color`` / ``send_buffer``)
	 * does not affect the displayed image: it needs to be sent a *refresh*
	 * command to do so. Other displays (eg: LCD, OLED) can implement this
	 * function with an empty body.
	 *
	 * A typical implementation of this function will issue the refresh command
	 * to the display when first called and then poll the busy data line to
	 * return ``true`` when refresh is ongoing and ``false`` when refresh finished:
	 *
	 * .. code-block:: c
	 *
	 *   if(display_IsRefreshing(eglib)) {
	 *   	return !hal_GetBusy(eglib);
	 *   } else {
	 *   	send_refresh_command_to_display(eglib);
	 *   	return true;
	 *   }
	 *
	 * :c:func:`display_IsRefreshing` queries the current state of refresh (that
	 * eglib keeps track) and :c:func:`hal_GetBusy` can be used no read the
	 * state of the busy data line.
	 *
	 * User code can then refresh the display with:
	 *
	 * .. code-block:: c
	 *
	 *   while(display_Refresh(eglib));
	 *
	 * :param eglib: :c:type:`eglib_t` handle.
	 * :return: ``true`` when refresh is ongoing and ``false`` when refresh finished.
	 */
	bool (*refresh)(eglib_t *eglib);
};

/**
 * Returns a pointer to the display driver configuration that was passed to
 * :c:func:`eglib_Init`.
 */
#define display_GetConfig(eglib) ((eglib)->display_config_ptr)

/**
 * Returns :c:type:`hal_four_wire_spi_config_t` for :c:type:`display_struct`
 * from given :c:type:`eglib_t`.
 *
 * :note: Used by 4-Wire SPI HAL drivers :c:type:`hal_t`.
 */
#define display_GetHalFourWireSpiConfigComm(eglib) (\
	(eglib)->display->comm.four_wire_spi \
)

/**
 * Returns :c:type:`hal_i2c_config_t` for :c:type:`display_struct`
 * from given :c:type:`eglib_t`.
 *
 * :note: Used by I2C HAL drivers :c:type:`hal_t`.
 */
#define display_GetHalI2cConfigComm(eglib) (\
	(eglib)->display->comm.i2c \
)

/**
 * :See also: :c:type:`hal_i2c_config_t` ``get_7bit_slave_addr`` for details on this
 *   function.
 * :note: Used by I2C HAL drivers :c:type:`hal_t`.
 */
#define display_GetI2c7bitSlaveAddr(eglib, dc) \
	(display_GetHalI2cConfigComm(eglib)->get_7bit_slave_addr(eglib, dc))

/**
 * :See also: :c:type:`hal_i2c_config_t` ``send`` for details on this
 *   function.
 * :note: Used by I2C HAL drivers :c:type:`hal_t`.
 */
#define display_I2cSend(eglib, i2c_write, dc, bytes, length) \
	(display_GetHalI2cConfigComm(eglib)->send(eglib, i2c_write, dc, bytes, length))

/**
 * Get display dimensions.
 *
 * :param eglib: :c:type:`eglib_t` handle.
 * :param width: Pointer where to write display width to.
 * :param height: Pointer where to write display height to.
 */
#define display_GetDimension(eglib, width, height) ( \
	(eglib)->display->get_dimension(eglib, width, height) \
)

/**
 * Returns the pixel format used in-memory by the display.
 *
 * :param eglib: :c:type:`eglib_t` handle.
 * :param pixel_format: Pointer to :c:type:`pixel_format_t` where to write
 *   pixel format to.
 * :return: :c:type:`pixel_format_t`.
 */
#define display_GetPixelFormat(eglib, pixel_format) ( \
	(eglib)->display->get_pixel_format(eglib, pixel_format) \
)

/** Returns display width as :c:type:`coordinate_t`. */
coordinate_t display_GetWidth(eglib_t *eglib);

/** Returns display height as :c:type:`coordinate_t`. */
coordinate_t display_GetHeight(eglib_t *eglib);

/**
 * Draws directly to the display memory at ``(x, y)`` using given ``color``.
 *
 * :param eglib: :c:type:`eglib_t` handle.
 * :param x: X :c:type:`coordinate_t`.
 * :param y: Y :c:type:`coordinate_t`.
 * :param color: Color :c:type:`color_t`.
 *
 * :note: Some displays do not support this function and must be used with
 *   :c:type:`eglib_Init_FrameBuffer`.
 */
#define display_DrawPixelColor(eglib, x, y, color) ( \
	(eglib)->display->draw_pixel_color(eglib, x, y, color) \
)

/**
 * Refreshes the display image. Only applicable to some displays (eg: e-ink /
 * e-paper). Typical usage:
 *
 * .. code-block:: c
 *
 *   while(display_Refresh(eglib));
 *
 * :param eglib: :c:type:`eglib_t` handle.
 * :return: ``true`` when refresh is ongoing and ``false`` when refresh finished.
 */
bool display_Refresh(eglib_t *eglib);

/** Whether a display refresh initiated by :c:func:`display_Refresh` is ongoing */
#define display_IsRefreshing(eglib) ((eglib)->display_refreshing)

#endif