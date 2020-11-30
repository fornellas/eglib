EGLIB_HAL_DRIVERS=four_wire_spi/none
EGLIB_DISPLAY_DRIVERS=tga

include ../common.mk

$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

.PHONY: test_*
test_%: $(BUILD_DIR)/test_%
	valgrind -q $< $<.tga
	cmp $<.tga $(@:test_%=test_%.tga)