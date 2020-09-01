BUILD_DIR = bin
CFILES = $(wildcard *.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
CFLAGS += -MD
EGLIB_PATH = ../src
EGLIB_LIB = $(EGLIB_PATH)/bin/eglib.a
INCLUDES = -I$(EGLIB_PATH)

all: test

.PHONY: all

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

-include $(OBJS:.o=.d)

$(EGLIB_LIB):
	make -C $(EGLIB_PATH)

$(BUILD_DIR)/test: $(OBJS) $(EGLIB_LIB)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LIBS)

test: $(BUILD_DIR)/test
	valgrind $(BUILD_DIR)/test

.PHONY: test

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean