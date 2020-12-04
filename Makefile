MAKEFILES += src/Makefile
MAKEFILES += $(wildcard tests/*/Makefile)
MAKEFILES += $(wildcard examples/libopencm3/*_*/Makefile)

MAKE_ALL = $(addsuffix -all,$(MAKEFILES))
MAKE_CLEAN = $(addsuffix -clean,$(MAKEFILES))

all: $(MAKE_ALL) docs

clean: $(MAKE_CLEAN)

.PHONY: font_generator
font_generator:
	make -C font_generator/

.PHONY: clean-font_generator
clean-font_generator:
	make -C font_generator clean

clean: font_generator

.PHONY: $(MAKE_ALL)
$(MAKE_ALL): font_generator
	$(MAKE) -C $(dir $@)

.PHONY: $(MAKE_CLEAN)
$(MAKE_CLEAN):
	$(MAKE) -C $(dir $@) clean

.PHONY: docs
docs: font_generator
	rm -rf docs/*
	sphinx-build -b html -a -d sphinx/_build/doctrees/ -W sphinx/ docs/
	rm -rf docs/.buildinfo sphinx/_build/