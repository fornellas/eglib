AUTOMAKE_OPTIONS = subdir-objects

EXTRA_DIST =
BUILT_SOURCES =
CLEANFILES =

SUBDIRS = font_generator .

include $(srcdir)/examples/local.mk
include $(srcdir)/fonts/local.mk
include $(srcdir)/sphinx/local.mk
include $(srcdir)/tests/local.mk
include $(srcdir)/tests/display/local.mk
include $(srcdir)/tests/drawing/local.mk
include $(srcdir)/tests/fonts/local.mk
include $(srcdir)/tests/fonts/adobe/local.mk
include $(srcdir)/tests/fonts/liberation/local.mk
include $(srcdir)/tests/frame_buffer/local.mk
@VALGRIND_CHECK_RULES@

##
## Generated Sources
##

nobase_nodist_include_HEADERS = eglib/config.h
nobase_nodist_include_HEADERS += eglib/drawing/fonts.h
nobase_nodist_include_HEADERS += eglib/drawing/fonts/adobe.h
nobase_nodist_include_HEADERS += eglib/drawing/fonts/liberation.h
nodist_libeglib_a_SOURCES = $(top_builddir)/eglib/drawing/fonts/adobe_courier_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_courier_bold_oblique.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_courier.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_courier_oblique.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_helvetica_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_helvetica_bold_oblique.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_helvetica.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_helvetica_oblique.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_century_schoolbook_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_century_schoolbook_bold_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_century_schoolbook_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_century_schoolbook_roman.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_centuy_schoolbook_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_new_cenury_schoolbook_roman.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_times_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_times_bold_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_times_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/adobe_times_roman.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_mono_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_mono_bolditalic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_mono_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_mono_regular.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sans_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sans_bolditalic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sans_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sansnarrow_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sansnarrow_bolditalic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sansnarrow_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sansnarrow_regular.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_sans_regular.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_serif_bold.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_serif_bolditalic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_serif_italic.c
nodist_libeglib_a_SOURCES += $(top_builddir)/eglib/drawing/fonts/liberation_serif_regular.c

BUILT_SOURCES += $(nobase_nodist_include_HEADERS) $(nodist_libeglib_a_SOURCES)

EXTRA_DIST += generate_fonts.sh

# SUBDIRS can't force `make -C font_generator/` as BUILT_SOURCES depends on it
# so we must explicitly add the dependency
${top_builddir}/font_generator/eglib-font_generator:
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C font_generator

eglib/drawing/fonts.h: $(top_srcdir)/generate_fonts.sh ${top_builddir}/font_generator/eglib-font_generator
	TOP_BUILDDIR=$(top_builddir) $(top_srcdir)/generate_fonts.sh

$(nodist_libeglib_a_SOURCES): eglib/drawing/fonts.h
eglib/drawing/fonts/adobe.h: eglib/drawing/fonts.h
eglib/drawing/fonts/liberation.h: eglib/drawing/fonts.h

.PHONY: clean-local
clean-local:
	-rm -f eglib/drawing/fonts.h
	-rm -rf eglib/drawing/fonts/

##
## Static Sources
##

nobase_include_HEADERS = eglib.h
nobase_include_HEADERS += eglib/display.h
nobase_include_HEADERS += eglib/display/frame_buffer.h
nobase_include_HEADERS += eglib/display/sh1106.h
nobase_include_HEADERS += eglib/display/ssd1331.h
nobase_include_HEADERS += eglib/display/ssd1675a.h
nobase_include_HEADERS += eglib/display/st7789.h
nobase_include_HEADERS += eglib/display/tga.h
nobase_include_HEADERS += eglib/drawing.h
nobase_include_HEADERS += eglib/hal.h
nobase_include_HEADERS += eglib/hal/four_wire_spi/libopencm3_stm32f4.h
nobase_include_HEADERS += eglib/hal/four_wire_spi/none.h
nobase_include_HEADERS += eglib/hal/four_wire_spi/stream.h
nobase_include_HEADERS += eglib/hal/i2c/libopencm3_stm32f4.h
nobase_include_HEADERS += eglib/hal/i2c/stream.h
nobase_include_HEADERS += eglib/hal/parallel_8_bit_8080/libopencm3_stm32f4.h
nobase_include_HEADERS += eglib/hal/parallel_8_bit_8080/stream.h
nobase_include_HEADERS += eglib/types.h

lib_LIBRARIES = libeglib.a
CFLAGS_COMMON = -ffunction-sections -fdata-sections
if OPENCM3_STM32F4
libeglib_a_CFLAGS = $(CFLAGS_OPENCM3) $(CFLAGS_WARNINGS) $(CFLAGS_COMMON)
libeglib_a_CPPFLAGS = -I$(top_builddir) $(CPPFLAGS_OPENCM3)
else
libeglib_a_CFLAGS = $(CFLAGS_WARNINGS) $(CFLAGS_COMMON)
libeglib_a_CPPFLAGS = -I$(top_builddir)
endif

eglib.c: eglib/drawing/fonts.h
libeglib_a_SOURCES = eglib.c
libeglib_a_SOURCES += eglib/display.c
libeglib_a_SOURCES += eglib/display/frame_buffer.c
libeglib_a_SOURCES += eglib/display/sh1106.c
libeglib_a_SOURCES += eglib/display/ssd1331.c
libeglib_a_SOURCES += eglib/display/ssd1675a.c
libeglib_a_SOURCES += eglib/display/st7789.c
libeglib_a_SOURCES += eglib/display/tga.c
libeglib_a_SOURCES += eglib/drawing.c
libeglib_a_SOURCES += eglib/hal.c
libeglib_a_SOURCES += eglib/hal/four_wire_spi/none.c
libeglib_a_SOURCES += eglib/hal/four_wire_spi/stream.c
EXTRA_libeglib_a_SOURCES = eglib/hal/common/libopencm3/stm32f4/delay.c
EXTRA_libeglib_a_SOURCES += eglib/hal/four_wire_spi/libopencm3_stm32f4.c
EXTRA_libeglib_a_SOURCES += eglib/hal/i2c/libopencm3_stm32f4.c
EXTRA_DIST += eglib/hal/common/libopencm3/stm32f4/delay.c
if OPENCM3_STM32F4
libeglib_a_SOURCES += eglib/hal/four_wire_spi/libopencm3_stm32f4.c
libeglib_a_SOURCES += eglib/hal/i2c/libopencm3_stm32f4.c
libeglib_a_SOURCES += eglib/hal/parallel_8_bit_8080/libopencm3_stm32f4.c
endif
libeglib_a_SOURCES += eglib/hal/i2c/stream.c
libeglib_a_SOURCES += eglib/hal/parallel_8_bit_8080/stream.c

##
## Version
##

EXTRA_DIST += $(top_srcdir)/.version
BUILT_SOURCES += $(top_srcdir)/.version

$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@

dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version

##
## Doc
##

dist_doc_DATA = README.md LICENSE.md