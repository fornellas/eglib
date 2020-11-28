libopencm3 STM32F4
==================

Driver
------

.. code:: c

    #include <eglib/hal/four_wire_spi/libopencm3_stm32f4.h>

.. c:autodoc:: eglib/hal/four_wire_spi/libopencm3_stm32f4.h
	:clang: -I../submodules/libopencm3/include/,-DSTM32F4

Example
-------

Also see :doc:`../../libopencm3`.

.. literalinclude:: ../../../../examples/libopencm3/stm32f4_sh1106_four_wire_spi/main.c
   :language: C