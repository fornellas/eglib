eglib
=====

eglib is a portable graphics library for interfacing with LCD, OLED, e-ink / e-paper displays, usable from microcontrollers to Linux.

Its design provides a simple but coherent interface enjoyable from both the perspective of end users or HAL / display driver developers.

The name *eglib* originally came from *Experimental Graphics Library*, but as it matured, *e* can stand for *exceptional*, *extraordinary*, *exquisite*, *elegant*...

Features
--------

- Hardware Abstraction Layer (HAL).

  - Supports different data buses such as 4-Wire SPI and I2C.
  - Easy to develop reusable drivers to different platforms.
  - Drivers can accept configuration (eg: I/O pins).
  - Supports display specific configuration for things like timings.

- Display drivers.

  - Common interface regardless of data bus.
  - Supports configuration

    - Enables the same controller driver to be used with different screen sizes or boards from different manufactures.
    - Support for extra controller features, such as different color depths.
    - Configuration for new boards can often be added with only a few lines.

  - Support for display controller specific functions, such as color inversion, scrolling, brightness etc.
  - Accelerated line drawing routines.
  - Supports a wide range:

    - Of display types: LCD, OLED, e-ink/e-paper.
    - Of color depths: black/white, black/white/red|yellow (e-ink / e-paper), grayscale to full color.

- Frame buffer

	- Can be used on top of any display driver.
	- Seamlessly integrates regardless of display color depth.
	- Faster refresh rates.
	- No visual artifacts from drawing directly on the display memory.
	- Supports partial display updates.

- Drawing

  - Many functions for lines, boxes, circle etc.
  - Supports defining a clipping box for drawing functions.

.. toctree::
   :maxdepth: 4
   :caption: Contents:
   :hidden:

   reference/index.rst