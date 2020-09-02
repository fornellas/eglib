BUILD_DIR = bin
CFILES = $(wildcard *.c)
CFILES += $(wildcard comm/*.c)
CFILES += $(wildcard display/*.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
CFLAGS += -MD

.PHONY: all
all: $(BUILD_DIR)/eglib.a

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/eglib.a: $(OBJS)
	$(AR) $(ARFLAGS) "$@" $(OBJS)

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)