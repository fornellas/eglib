AUTOMAKE_OPTIONS = subdir-objects

libopencm3_stm32f4_sources =
libopencm3_stm32f4_sources += libopencm3_stm32f4/build-aux/libopencm3.mk
libopencm3_stm32f4_sources += libopencm3_stm32f4/configure.ac
libopencm3_stm32f4_sources += libopencm3_stm32f4/gdb.init
libopencm3_stm32f4_sources += libopencm3_stm32f4/Makefile.am
libopencm3_stm32f4_sources += libopencm3_stm32f4/sh1106-four_wire_spi.c
libopencm3_stm32f4_sources += libopencm3_stm32f4/sh1106-i2c.c
libopencm3_stm32f4_sources += libopencm3_stm32f4/ssd1331-four_wire_spi.c
libopencm3_stm32f4_sources += libopencm3_stm32f4/st7789-four_wire_spi.c

libopencm3_stm32f4_configury =
libopencm3_stm32f4_configury += libopencm3_stm32f4/aclocal.m4
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/compile
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/config.guess
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/config.sub
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/depcomp
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/install-sh
libopencm3_stm32f4_configury += libopencm3_stm32f4/build-aux/missing
libopencm3_stm32f4_configury += libopencm3_stm32f4/config.h.in
libopencm3_stm32f4_configury += libopencm3_stm32f4/configure
libopencm3_stm32f4_configury += libopencm3_stm32f4/gdb.init
libopencm3_stm32f4_configury += libopencm3_stm32f4/Makefile.in

dist_noinst_DATA = $(libopencm3_stm32f4_sources) $(libopencm3_stm32f4_configury)
nodist_doc_DATA = eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz

.PHONY: clean-eglib-example-libopencm3_stm32f4-$(VERSION)
clean-eglib-example-libopencm3_stm32f4-$(VERSION):
	if test -d eglib-example-libopencm3_stm32f4-$(VERSION) ; then chmod u+w -R eglib-example-libopencm3_stm32f4-$(VERSION) ; fi
	rm -rf eglib-example-libopencm3_stm32f4-$(VERSION)

clean-local: clean-eglib-example-libopencm3_stm32f4-$(VERSION)

eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz: $(libopencm3_stm32f4_sources) $(libopencm3_stm32f4_configury)
	$(MAKE) $(AM_MAKEFLAGS) clean-eglib-example-libopencm3_stm32f4-$(VERSION)
	mkdir eglib-example-libopencm3_stm32f4-$(VERSION)
	cp -a $? eglib-example-libopencm3_stm32f4-$(VERSION)/
	tar zcf $@ eglib-example-libopencm3_stm32f4-$(VERSION)/
	chmod u+w -R eglib-example-libopencm3_stm32f4-$(VERSION)/
	rm -rf eglib-example-libopencm3_stm32f4-$(VERSION)

CLEANFILES = eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz

.PHONY: check-eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz

if OPENCM3_STM32F4

check-eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz: eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz
	$(MAKE) $(AM_MAKEFLAGS) clean-eglib-example-libopencm3_stm32f4-$(VERSION)
	tar zxf eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz \
		&& cd eglib-example-libopencm3_stm32f4-$(VERSION)/ \
		&& mkdir build \
		&& cd build/ \
		&& ../configure \
			--host=$(host) \
			--with-libopencm3="$(OPENCM3_DIR)" \
			--with-eglib-libdir="$(abs_top_builddir)/src" \
			--with-eglib-includedir="$(abs_top_builddir)/src" \
			CC="$(CC)" \
			CFLAGS="$(CFLAGS)" \
			LDFLAGS="$(LDFLAGS)" \
			LIBS="$(LIBS)" \
			CPPFLAGS="$(CPPFLAGS)" \
			CPP="$(CPP)" \
		&& $(MAKE) $(AM_MAKEFLAGS) distcheck

check: check-eglib-example-libopencm3_stm32f4-$(VERSION).tar.gz

endif