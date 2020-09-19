BUILD_DIR_PREFIX = bin
BUILD_DIR = $(BUILD_DIR_PREFIX)/$(PROJECT)
OPENCM3_DIR=$(abspath ../libopencm3)

include $(OPENCM3_DIR)/mk/genlink-config.mk
# genlink-config.mk does not populate these variables first run,
# as it depends on opencm3_stm32f4.a existing.
ifndef LIBNAME
LIBNAME = $(OPENCM3_LIBNAME)
LDLIBS += -l$(LIBNAME)
LIBDEPS += $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
endif
ifneq ($(LIBNAME), $(OPENCM3_LIBNAME))
$(error Unexpected LIBNAME value $(LIBNAME))
endif

include ../libopencm3-template/rules.mk

.PHONY: $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(MAKE) -C $(OPENCM3_DIR) $(OPENCM3_LIBDIR)

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
		HAL_DRIVERS=$(EGLIB_HAL_DRIVERS) \
		DISPLAY_DRIVERS=$(EGLIB_DISPLAY_DRIVERS)

dfu_download: ${BINARY}.bin
	dfu-util \
		--alt 0 \
		--device $(USB_DFU_BOOTLOADER_VID):$(USB_DFU_BOOTLOADER_PID) \
		--dfuse-address $(MAIN_MEMORY_BASE) \
		--download $<

openocd:
	openocd \
		--file interface/$(OOCD_INTERFACE).cfg \
		--file target/$(OOCD_TARGET).cfg

.PHONY: openocd_program
openocd_program: ${PROJECT}.bin $(LDSCRIPT)
	$(Q)openocd \
		--file interface/$(OOCD_INTERFACE).cfg \
		--file target/$(OOCD_TARGET).cfg \
		--command "program ${PROJECT}.bin verify reset exit $(FLASH_BASE)"

gdb: $(BINARY).elf
	$(GDB) --init-command=lib/gdb.init $(BINARY).elf

.PHONY: clean-eglib
clean-eglib:
	rm -rf $(EGLIB_BUILD_DIR)

clean: clean-eglib

.PHONY: clean-libopencm3
clean-libopencm3:
	$(MAKE) -C $(OPENCM3_DIR) clean

clean: clean-libopencm3