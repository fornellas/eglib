MAKEFILES += src/Makefile
MAKEFILES += $(wildcard tests/*/Makefile)
MAKEFILES += $(wildcard examples/libopencm3/*_*/Makefile)

MAKE_ALL = $(addsuffix -all,$(MAKEFILES))
MAKE_CLEAN = $(addsuffix -clean,$(MAKEFILES))

all: $(MAKE_ALL) docs

.PHONY: $(MAKE_ALL)
$(MAKE_ALL):
	$(MAKE) -C $(dir $@)

clean: $(MAKE_CLEAN)

.PHONY: $(MAKE_CLEAN)
$(MAKE_CLEAN):
	$(MAKE) -C $(dir $@) clean

.PHONY: docs
docs:
	rm -rf docs/*
	sphinx-build -b html -a -d sphinx/_build/doctrees/ -W sphinx/ docs/
	rm -rf docs/.buildinfo sphinx/_build/