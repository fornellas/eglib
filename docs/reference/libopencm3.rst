libopencm3 integration
======================

.. contents::
    :depth: 3

`libopencm3 documentation <http://libopencm3.org/>`_ should be referred to learn how to create a new project with it.

Manual integration
------------------

Integrating eglib with it requires that eglib is built with Arm gcc and flags required by libopencm3 headers, eg:

.. code:: shell

  export CC=arm-none-eabi-gcc
  export CFLAGS="-DSTM32F4 -DSTM32F411CEU6 -I${LIBOPENCM3_ROOT}/libopencm3/include -I${EGLIB_ROOT}/eglib/src -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nano.specs"
  make -C ${EGLIB_ROOT}/eglib/src HAL_DRIVERS=four_wire_spi/libopencm3_stm32f4 EGLIB_DISPLAY_DRIVERS=st7789

This will build ``${EGLIB_ROOT}/eglib/src/bin/libeglib.a``, which can be linked at the final build by passing these parameters to gcc:

.. code::

  -L${EGLIB_ROOT}/eglib/src/bin/ -leglib

``Makefile`` example
--------------------

The following ``common.mk`` comes from eglib's own source tree example. It can be used as a starting point to write your own. Note that it depends on ``rules.mk`` from  `libopencm3-template <https://github.com/libopencm3/libopencm3-template>`_. and ``mk/genlink-config.mk`` from `libopencm3 <https://github.com/libopencm3/libopencm3>`_.

.. literalinclude:: ../../examples/libopencm3/common.mk
   :language: make

And it can then be used by a project's ``Makefile``:

.. literalinclude:: ../../examples/libopencm3/stm32f4_st7789_four_wire_spi/Makefile
   :language: make