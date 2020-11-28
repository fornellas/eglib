libopencm3 STM32F4
==================

Driver
------

.. code:: c

    #include <eglib/hal/i2c/libopencm3_stm32f4.h>

.. c:autodoc:: eglib/hal/i2c/libopencm3_stm32f4.h
	:clang: -I../submodules/libopencm3/include/,-DSTM32F4

Example
-------

Also see :doc:`../../libopencm3`.

.. literalinclude:: ../../../../examples/libopencm3/stm32f4_sh1106_i2c/main.c
   :language: C