BUILD_DIR_PREFIX = bin
BUILD_DIR = $(BUILD_DIR_PREFIX)/tests
EGLIB_BUILD_DIR = $(abspath $(BUILD_DIR_PREFIX)/eglib)
CFILES = $(wildcard test_*.c)
OBJS = $(CFILES:test_%.c=$(BUILD_DIR)/test_%.o)
TEST_BINARIES = $(CFILES:test_%.c=$(BUILD_DIR)/test_%)
TESTS = $(CFILES:test_%.c=test_%)
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

EGLIB_PATH = ../../src
INCLUDES += -I$(EGLIB_PATH)
EGLIB_LIB = $(EGLIB_BUILD_DIR)/libeglib.a

.PHONY: all
all: $(TESTS)

.PHONY: $(EGLIB_LIB)
$(EGLIB_LIB):
	make \
		-C $(EGLIB_PATH) \
		BUILD_DIR=$(EGLIB_BUILD_DIR) \
		DISPLAY_DRIVERS="$(EGLIB_DISPLAY_DRIVERS)" \
		HAL_DRIVERS=$(EGLIB_HAL_DRIVERS) \
		$@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR_PREFIX)
