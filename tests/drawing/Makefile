EGLIB_HAL_DRIVERS=four_wire_spi/none
EGLIB_DISPLAY_DRIVERS=tga
TGA_FILES = $(wildcard *.tga)
PNG_FILES = $(TGA_FILES:%.tga=%.png)

include ../common.mk

$(BUILD_DIR)/test_%: $(BUILD_DIR)/main.o $(BUILD_DIR)/test_%.o $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

.PHONY: test_*
test_%: $(BUILD_DIR)/test_%
	valgrind -q $< $<.tga
	cmp $<.tga $(@:test_%=test_%.tga)


.PHONY: png
png: $(PNG_FILES)

%.png: %.tga
	convert -quality 100 $< $@

.PHONY: clean-png
clean-png:
	rm *.png

clean: clean-png