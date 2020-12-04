TESTS_MAKEFILES += $(wildcard tests/*/Makefile)
MAKEFILES += $(TESTS_MAKEFILES)
EXAMPLES_MAKEFILES += $(wildcard examples/libopencm3/*_*/Makefile)
MAKEFILES += $(EXAMPLES_MAKEFILES)

MAKE_ALL = $(addsuffix -all,$(MAKEFILES))
MAKE_CLEAN = $(addsuffix -clean,$(MAKEFILES))

all: $(MAKE_ALL) docs

clean: $(MAKE_CLEAN)

.PHONY: fonts
fonts:
	make -C font_generator/

.PHONY: clean-fonts
clean-fonts:
	make -C font_generator clean

clean: clean-fonts

.PHONY: tests
tests: $(addsuffix -all,$(TESTS_MAKEFILES))

.PHONY: examples
examples: $(addsuffix -all,$(EXAMPLES_MAKEFILES))

.PHONY: $(MAKE_ALL)
$(MAKE_ALL): fonts
	$(MAKE) -C $(dir $@)

.PHONY: $(MAKE_CLEAN)
$(MAKE_CLEAN):
	$(MAKE) -C $(dir $@) clean

.PHONY: docs
docs: fonts
	rm -rf docs/*
	sphinx-build -b html -a -d sphinx/_build/doctrees/ -W sphinx/ docs/
	rm -rf docs/.buildinfo sphinx/_build/