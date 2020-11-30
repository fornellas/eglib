EGLIB_HAL_DRIVERS = four_wire_spi/stdout
EGLIB_DISPLAY_DRIVERS = \
	sh1106 \
	st7789

include ../common.mk

$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

.PHONY: test_*
test_%: $(BUILD_DIR)/test_%
	valgrind -q $< > $<.stdout
	cmp $<.stdout $(@:test_%=test_%.stdout)