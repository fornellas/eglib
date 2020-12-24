all: eglib/drawing/fonts.h

noinst_PROGRAMS = font_generator
font_generator_SOURCES = font_generator.c
font_generator_CFLAGS = $(FREETYPE2_CFLAGS)
font_generator_LDADD = $(FREETYPE2_LIBS)

nobase_include_HEADERS = eglib/drawing/fonts.h
nobase_include_HEADERS += eglib/drawing/fonts/adobe.h
nobase_include_HEADERS += eglib/drawing/fonts/liberation.h

eglib/drawing/fonts/adobe.h: eglib/drawing/fonts.h
eglib/drawing/fonts/liberation.h: eglib/drawing/fonts.h

eglib/drawing/fonts.h: generate_fonts.sh font_generator.c font_generator
	$(top_srcdir)/font_generator/generate_fonts.sh

.PHONY: clean-local
clean-local:
	rm -f eglib/drawing/fonts.h
	rm -rf eglib/drawing/fonts/