BUILD_DIR_PREFIX = bin
BUILD_DIR = $(BUILD_DIR_PREFIX)/fonts
VALGRIND=valgrind -q
CFLAGS += \
	-MD \
	-O3 \
	-Wall \
	-Wextra \
	-Wimplicit-function-declaration \
	-Wredundant-decls \
	-Wmissing-prototypes \
	-Wstrict-prototypes \
	-Wundef \
	-Wshadow \
	-Wstrict-prototypes \
	-Werror \
	-Wfatal-errors

all:

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR_PREFIX)

##
## eglib 
##

EGLIB_BUILD_DIR = $(abspath $(BUILD_DIR_PREFIX)/eglib)
EGLIB_PATH = ../../src
CFLAGS += -I$(EGLIB_PATH)
EGLIB_LIB = $(EGLIB_BUILD_DIR)/libeglib.a
EGLIB_DISPLAY_DRIVERS=tga
EGLIB_HAL_DRIVERS=four_wire_spi/none

.PHONY: $(EGLIB_LIB)
$(EGLIB_LIB):
	make \
		-C $(EGLIB_PATH) \
		BUILD_DIR=$(EGLIB_BUILD_DIR) \
		DISPLAY_DRIVERS="$(EGLIB_DISPLAY_DRIVERS)" \
		HAL_DRIVERS=$(EGLIB_HAL_DRIVERS) \
		$@

##
## unicode_block
##

UNICODE_BLOCK_PNG = $(wildcard test_unicode_block_*.png)
UNICODE_BLOCK_OBJS = $(UNICODE_BLOCK_PNG:test_unicode_block_%.png=$(BUILD_DIR)/test_unicode_block_%.o)
UNICODE_BLOCK_BIN = $(UNICODE_BLOCK_PNG:test_unicode_block_%.png=$(BUILD_DIR)/test_unicode_block_%)
UNICODE_BLOCK_TGA = $(UNICODE_BLOCK_PNG:test_unicode_block_%.png=$(BUILD_DIR)/test_unicode_block_%.tga)
.PRECIOUS: $(UNICODE_BLOCK_TGA)
UNICODE_BLOCK_OK = $(UNICODE_BLOCK_PNG:test_unicode_block_%.png=$(BUILD_DIR)/test_unicode_block_%.ok)

.PHONY: unicode_block
unicode_block: $(UNICODE_BLOCK_OK)
all: unicode_block

$(BUILD_DIR)/test_unicode_block_%.o: unicode_block.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DFONT=font_$(shell basename $@ | cut -d_ -f4,5,6) -DUNICODE_BLOCK=unicode_block_$(shell basename $@ | cut -d_ -f4,5,6,7 | cut -d. -f1) -o $@ -c $<	

$(BUILD_DIR)/test_unicode_block_%: $(BUILD_DIR)/test_unicode_block_%.o $(EGLIB_LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BUILD_DIR)/test_unicode_block_%.tga: $(BUILD_DIR)/test_unicode_block_%
	$(VALGRIND) $< $@

$(BUILD_DIR)/test_unicode_block_%.ok: $(BUILD_DIR)/test_unicode_block_%.tga
	compare -metric FUZZ $< $(<:$(BUILD_DIR)/%.tga=%.png) /dev/null
	touch $@