EXTRA_DIST =

EXTRA_DIST += api_reference/display/drivers/frame_buffer.rst
EXTRA_DIST += api_reference/display/drivers/index.rst
EXTRA_DIST += api_reference/display/drivers/sh1106.rst
EXTRA_DIST += api_reference/display/drivers/ssd1331.rst
EXTRA_DIST += api_reference/display/drivers/st7789.rst
EXTRA_DIST += api_reference/display/drivers/tga.rst
EXTRA_DIST += api_reference/display/index.rst
EXTRA_DIST += api_reference/display/interface.rst
EXTRA_DIST += api_reference/drawing/fonts.rst
EXTRA_DIST += api_reference/drawing/functions.rst
EXTRA_DIST += api_reference/drawing/index.rst
EXTRA_DIST += api_reference/eglib.rst
EXTRA_DIST += api_reference/hal/four_wire_spi/index.rst
EXTRA_DIST += api_reference/hal/four_wire_spi/libopencm3_stm32f4.rst
EXTRA_DIST += api_reference/hal/four_wire_spi/none.rst
EXTRA_DIST += api_reference/hal/four_wire_spi/stream.rst
EXTRA_DIST += api_reference/hal/i2c/index.rst
EXTRA_DIST += api_reference/hal/i2c/libopencm3_stm32f4.rst
EXTRA_DIST += api_reference/hal/i2c/stream.rst
EXTRA_DIST += api_reference/hal/index.rst
EXTRA_DIST += api_reference/hal/interface.rst
EXTRA_DIST += api_reference/index.rst
EXTRA_DIST += conf.py
EXTRA_DIST += driver_development/display.rst
EXTRA_DIST += driver_development/hal.rst
EXTRA_DIST += driver_development/index.rst
EXTRA_DIST += index.rst
EXTRA_DIST += requirements.txt
EXTRA_DIST += _static/logo.png
EXTRA_DIST += _templates/badges.html

if BUILD_HTML

.PHONY: include/
include/:
	rm -rf include/
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/src/ install-data includedir=include DESTDIR=$(top_builddir)/sphinx/
	cd include && $(LN_S) $(OPENCM3_DIR)/include/* .

.PHONY: $(top_builddir)/html/
$(top_builddir)/html/: include/
	EGLIB_SRC="$(top_builddir)/sphinx/include" sphinx-build -b html -W $(top_srcdir)/sphinx/ html/
	rm -rf html/.buildinfo html/.doctrees

.PHONY: html-local
html-local: $(top_builddir)/html/

.PHONY: install-html-local
install-html-local: html-local
	find html/ -type f -exec $(install_sh_DATA) "{}" $(DESTDIR)$(docdir)/"{}" \;

.PHONY: uninstall-local
uninstall-local:
	-rm -rf $(DESTDIR)$(docdir)/html

check: html-local

.PHONY: clean-local
clean-local:
	-rm -rf include/
	-rm -rf html/

endif