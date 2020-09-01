BUILD_DIR = bin
CFILES = $(wildcard *.c)
CFILES += $(wildcard comm/*.c)
CFILES += $(wildcard display/*.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
CFLAGS += -MD

all: $(BUILD_DIR)/eglib.a

.PHONY: all

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(BUILD_DIR)/eglib.a: $(OBJS)
	$(AR) $(ARFLAGS) "$@" $(OBJS)

-include $(OBJS:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean