libopencm3
==========

`libopencm3 <https://libopencm3.org/>`_ is a lowlevel hardware library for various ARM CPUs.

Both eglib and your project must be compiled using the same libopencm3 build. So first, compile libopencm3:

.. code:: bash

	git clone git@github.com:libopencm3/libopencm3.git
	cd libopencm3/
	make

eglib must then be configured pointing to where libopencm3 is:

The following libopencm3 targets are supported:

STM32F4
-------

.. code:: bash

  ./configure --host=arm-none-eabi --with-libopencm3=$OPENCM3_PATH --enable-libopencm3_stm32f4