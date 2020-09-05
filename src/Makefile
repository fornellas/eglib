.PHONY: all
all:

##
## libopencm3
##

ifdef OPENCM3_DIR
CFLAGS += -I$(OPENCM3_DIR)/include
CFILES += eglib/comm/libopencm3_stm32f4.c

include $(OPENCM3_DIR)/mk/genlink-config.mk

endif

##
## Core
##

BUILD_DIR ?= bin
CFILES += $(wildcard *.c)
CFILES += eglib/comm/none.c
CFILES += $(wildcard eglib/display/*.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
CFLAGS += -MD -Werror -Wall

all: $(BUILD_DIR)/eglib.a

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(BUILD_DIR)/eglib.a: $(OBJS)
	$(AR) $(ARFLAGS) "$@" $(OBJS)

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

