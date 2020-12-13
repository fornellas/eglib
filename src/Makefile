BUILD_DIR ?= bin
CFILES += $(wildcard *.c)
CFILES += $(wildcard eglib/*.c)
CFILES += $(wildcard eglib/hal/*.c)
CFILES += $(wildcard eglib/drawing/fonts/*.c)
CFILES += eglib/display/frame_buffer.c
ifdef DISPLAY_DRIVERS
CFILES += $(DISPLAY_DRIVERS:%=eglib/display/%.c)
endif
CFILES += eglib/hal/four_wire_spi/none.c
ifdef HAL_DRIVERS
CFILES += $(HAL_DRIVERS:%=eglib/hal/%.c)
endif
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
override CFLAGS += \
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

.PHONY: all
all: $(BUILD_DIR)/libeglib.a

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(BUILD_DIR)/libeglib.a: $(OBJS)
	$(AR) $(ARFLAGS) "$@" $(OBJS)

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)