##
## Project
##

PROJECT = stm32f4_st7789
CFILES = main.c

##
## Hardware
##

DEVICE=stm32f411ceu6
FLASH_BASE = 0x08000000
USB_DFU_BOOTLOADER_VID=0x0483
USB_DFU_BOOTLOADER_PID=0xdf11

##
## openocd
##

OOCD_INTERFACE = stlink-v2
OOCD_TARGET= stm32f4x

##
## libopencm3
##

OPENCM3_LIBNAME = opencm3_stm32f4
OPENCM3_LIBDIR = lib/stm32/f4

##
## eglib
##

EGLIB_HAL_DRIVERS=4wire_spi/libopencm3_stm32f4
EGLIB_DISPLAY_DRIVERS=4wire_spi/st7789

include ../common.mk