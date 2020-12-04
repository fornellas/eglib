CFLAGS += $(shell pkg-config --cflags freetype2)
LDFLAGS += $(shell pkg-config --libs freetype2)
BUILD_DIR ?= bin
CFILES = $(wildcard *.c)
OBJS = $(CFILES:%.c=$(BUILD_DIR)/%.o)
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

.PHONY: generate_fonts
generate_fonts: font_generator
	./generate_fonts.sh

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

font_generator: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean-font_generator
clean-font_generator:
	rm -f ../src/eglib/drawing/fonts.h
	rm -rf ../src/eglib/drawing/fonts/
	rm -rf font_generator
clean: clean-font_generator

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(OBJS:.o=.d)

