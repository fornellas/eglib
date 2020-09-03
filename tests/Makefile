BUILD_DIR = bin
CFILES = $(wildcard *.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
TEST_BINARIES = $(CFILES:%.c=$(BUILD_DIR)/%)
TESTS = $(CFILES:%.c=%_test)
CFLAGS += -MD -Werror -Wall

EGLIB_PATH = ../src
EGLIB_LIB = $(EGLIB_PATH)/bin/eglib.a

INCLUDES = -I$(EGLIB_PATH)

.PHONY: all
all: $(TESTS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

-include $(OBJS:.o=.d)

.PHONY: $(EGLIB_LIB)
$(EGLIB_LIB):
	make -C ../src bin/eglib.a

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(EGLIB_LIB)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

.PHONY: *_test
%_test: $(BUILD_DIR)/%
	valgrind -q $< $<.tga
	cmp $<.tga $(@:%_test=%.tga)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)