PROJECT = stm32f4_st7789
BUILD_DIR_PREFIX = bin
BUILD_DIR = $(BUILD_DIR_PREFIX)/$(PROJECT)

CFILES = main.c

DEVICE=stm32f411ceu6
FLASH_BASE = 0x08000000
OOCD_INTERFACE = stlink-v2
OOCD_TARGET= stm32f4x
OPENCM3_DIR=$(abspath ../libopencm3)
include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../libopencm3-template/rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
export CC
CFLAGS += -Werror
CFLAGS += $(CPPFLAGS)
CFLAGS += -I$(OPENCM3_DIR)/include
CFLAGS += $(ARCH_FLAGS)
export CFLAGS

EGLIB_PATH = ../../../src/
INCLUDES += -I$(EGLIB_PATH)
EGLIB_BUILD_DIR = $(abspath $(BUILD_DIR_PREFIX)/eglib)
EGLIB_LIB = $(EGLIB_BUILD_DIR)/libeglib.a
LDLIBS += -leglib -l$(LIBNAME)
$(PROJECT).elf: $(EGLIB_LIB)
LDFLAGS += -L$(EGLIB_BUILD_DIR)

.PHONY: $(EGLIB_LIB)
$(EGLIB_LIB):
	$(MAKE) \
		-C $(EGLIB_PATH) \
		BUILD_DIR=$(EGLIB_BUILD_DIR) \
		HAL_DRIVERS=4wire_spi/libopencm3_stm32f4 \
		DISPLAY_DRIVERS=4wire_spi/st7789

.PHONY: openocd_program
openocd_program: ${PROJECT}.bin $(LDSCRIPT)
	$(Q)openocd --file interface/$(OOCD_INTERFACE).cfg --file target/$(OOCD_TARGET).cfg --command "program ${PROJECT}.bin verify reset exit $(FLASH_BASE)"

.PHONY: clean-eglib
clean-eglib:
	rm -rf $(EGLIB_BUILD_DIR)
clean: clean-eglib