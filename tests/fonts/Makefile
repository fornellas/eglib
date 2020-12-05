EGLIB_HAL_DRIVERS=four_wire_spi/none
EGLIB_DISPLAY_DRIVERS=tga
PNG_FILES = $(wildcard test_*.png)

include ../common.mk

CFILES = $(PNG_FILES:test_%.png=$(BUILD_DIR)/test_%.c)
OBJS = $(PNG_FILES:test_%.png=$(BUILD_DIR)/test_%.o)
TESTS = $(PNG_FILES:test_%.png=$(BUILD_DIR)/test_%)
TGA_FILES = $(PNG_FILES:test_%.png=$(BUILD_DIR)/test_%.tga)
COMPARE = $(PNG_FILES:test_%.png=$(BUILD_DIR)/test_%.compare)
.PRECIOUS: $(CFILES) $(OBJS) $(TGA_FILES) $(COMPARE)

all: $(COMPARE)

$(BUILD_DIR)/test_%.c: main.c.template
	mkdir -p $(dir $@)
	cp main.c.template $@

$(BUILD_DIR)/test_%.o: $(BUILD_DIR)/test_%.c
	$(CC) $(CFLAGS) -DFONT=$(@:$(BUILD_DIR)/test_%.o=%) $(INCLUDES) -o $@ -c $<

$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lm

$(BUILD_DIR)/test_%.tga: $(BUILD_DIR)/test_%
	valgrind -q $< $@

$(BUILD_DIR)/test_%.compare: $(BUILD_DIR)/test_%.tga
	compare -metric FUZZ $< $(<:$(BUILD_DIR)/%.tga=%.png) /dev/null
	touch $@