BUILD_DIR ?= bin
CFILES += $(wildcard *.c)
ifdef DISPLAY_DRIVERS
CFILES += $(DISPLAY_DRIVERS:%=eglib/display/%.c)
endif
ifdef HAL_DRIVERS
CFILES += $(HAL_DRIVERS:%=eglib/hal/%.c)
endif
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
override CFLAGS += -MD -Werror -Wall -O3

.PHONY: all
all: $(BUILD_DIR)/libeglib.a

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(BUILD_DIR)/libeglib.a: $(OBJS)
	$(AR) $(ARFLAGS) "$@" $(OBJS)

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)