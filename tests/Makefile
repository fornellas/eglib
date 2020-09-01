BUILD_DIR = bin
CFILES = $(wildcard *.c)
BINARIES = $(CFILES:%.c=$(BUILD_DIR)/%)
TESTS = $(CFILES:%.c=%_test)
CFLAGS += -MD
EGLIB_PATH = ../src
EGLIB_LIB = $(EGLIB_PATH)/bin/eglib.a
INCLUDES = -I$(EGLIB_PATH)

all: $(TESTS)

.PHONY: all

$(EGLIB_LIB):
	make -C $(EGLIB_PATH)

$(BUILD_DIR)/%: %.c $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%_test: $(BUILD_DIR)/%
	valgrind -q $<
	cmp $<.tga $(@:%_test=%.tga)

# .PHONY: $(TESTS)

-include $(OBJS:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean