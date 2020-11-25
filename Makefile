MAKEFILES += src/Makefile
MAKEFILES += $(wildcard tests/*/Makefile)
MAKEFILES += $(wildcard examples/libopencm3/*_*/Makefile)
MAKEFILES += docs/Makefile

MAKE_ALL = $(addsuffix -all,$(MAKEFILES))
MAKE_CLEAN = $(addsuffix -clean,$(MAKEFILES))

all: $(MAKE_ALL)

.PHONY: $(MAKE_ALL)
$(MAKE_ALL):
	$(MAKE) -C $(dir $@)

clean: $(MAKE_CLEAN)

.PHONY: $(MAKE_CLEAN)
$(MAKE_CLEAN):
	$(MAKE) -C $(dir $@) clean
