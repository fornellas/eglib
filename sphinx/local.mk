EXTRA_DIST += %D%/api_reference/display/drivers/frame_buffer.rst
EXTRA_DIST += %D%/api_reference/display/drivers/index.rst
EXTRA_DIST += %D%/api_reference/display/drivers/sh1106.rst
EXTRA_DIST += %D%/api_reference/display/drivers/ssd1331.rst
EXTRA_DIST += %D%/api_reference/display/drivers/st7789.rst
EXTRA_DIST += %D%/api_reference/display/drivers/tga.rst
EXTRA_DIST += %D%/api_reference/display/index.rst
EXTRA_DIST += %D%/api_reference/display/interface.rst
EXTRA_DIST += %D%/api_reference/drawing/fonts.rst
EXTRA_DIST += %D%/api_reference/drawing/functions.rst
EXTRA_DIST += %D%/api_reference/drawing/index.rst
EXTRA_DIST += %D%/api_reference/eglib.rst
EXTRA_DIST += %D%/api_reference/hal/four_wire_spi/index.rst
EXTRA_DIST += %D%/api_reference/hal/four_wire_spi/libopencm3_stm32f4.rst
EXTRA_DIST += %D%/api_reference/hal/four_wire_spi/none.rst
EXTRA_DIST += %D%/api_reference/hal/four_wire_spi/stream.rst
EXTRA_DIST += %D%/api_reference/hal/i2c/index.rst
EXTRA_DIST += %D%/api_reference/hal/i2c/libopencm3_stm32f4.rst
EXTRA_DIST += %D%/api_reference/hal/i2c/stream.rst
EXTRA_DIST += %D%/api_reference/hal/index.rst
EXTRA_DIST += %D%/api_reference/hal/interface.rst
EXTRA_DIST += %D%/api_reference/index.rst
EXTRA_DIST += %D%/conf.py
EXTRA_DIST += %D%/driver_development/display.rst
EXTRA_DIST += %D%/driver_development/hal.rst
EXTRA_DIST += %D%/driver_development/index.rst
EXTRA_DIST += %D%/index.rst
EXTRA_DIST += %D%/requirements.txt
EXTRA_DIST += %D%/_static/logo.png
EXTRA_DIST += %D%/_templates/badges.html

.PHONY: %D%/html/
.PHONY: html-local
.PHONY: install-html-local
.PHONY: update-html
.PHONY: uninstall-local

clean-local: clean-html

if BUILD_HTML

CLEANFILES += top_srcdir
top_srcdir:
	$(LN_S) $(top_srcdir) $@

CLEANFILES += opencm3_dir
opencm3_dir:
	$(LN_S) $(OPENCM3_DIR) $@


%D%/html/: eglib/drawing/fonts.h top_srcdir opencm3_dir $(EXPECTATION_PNGS_TARGETS)
	TOP_SRCDIR=$(top_srcdir) TOP_BUILDDIR=$(top_builddir) sphinx-build -b html -W $(top_srcdir)/sphinx/ $@
	rm -rf $@/.buildinfo $@/.doctrees $@/_sources

clean-html:
	rm -rf %D%/html/

html-local: %D%/html/

install-html-local: html-local
	cd %D% && find html/ -type f -exec $(install_sh_DATA) "{}" $(DESTDIR)$(docdir)/"{}" \;

update-html: html-local
	rm -rf $(top_srcdir)/docs
	cp -a %D%/html $(top_srcdir)/docs
	touch $(top_srcdir)/docs/.nojekyll

uninstall-local:
	-rm -rf $(DESTDIR)$(docdir)/html

check: html-local

else

clean-html:

endif