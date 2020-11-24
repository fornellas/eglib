EGLIB_HAL_DRIVERS=four_wire_spi/none
EGLIB_DISPLAY_DRIVERS=tga

include ../common.mk

.PHONY: test_*
test_%: $(BUILD_DIR)/test_%
	valgrind -q $< $<.tga
	cmp $<.tga $(@:test_%=test_%.tga)