include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/drawing

EXTRA_DIST =

drawing_sources =
drawing_sources += eglib_AddUnicodeBlockToFont.c
drawing_sources += eglib_ClearScreen.c
drawing_sources += eglib_DrawArc.c
drawing_sources += eglib_DrawBitmap.c
drawing_sources += eglib_DrawBox.c
drawing_sources += eglib_DrawCircle.c
drawing_sources += eglib_DrawDisc.c
drawing_sources += eglib_DrawFilledArc.c
drawing_sources += eglib_DrawFrame.c
drawing_sources += eglib_DrawGradientArc.c
drawing_sources += eglib_DrawGradientBox.c
drawing_sources += eglib_DrawGradientDisc.c
drawing_sources += eglib_DrawGradientFilledArc.c
drawing_sources += eglib_DrawGradientFrame.c
drawing_sources += eglib_DrawGradientHLine.c
drawing_sources += eglib_DrawGradientLine.c
drawing_sources += eglib_DrawGradientVLine.c
drawing_sources += eglib_DrawHLine.c
drawing_sources += eglib_DrawLine.c
drawing_sources += eglib_DrawPixelColor.c
drawing_sources += eglib_DrawPixel.c
drawing_sources += eglib_DrawRoundBox.c
drawing_sources += eglib_DrawRoundFrame.c
drawing_sources += eglib_DrawText.c
drawing_sources += eglib_DrawTriangle.c
drawing_sources += eglib_DrawVLine.c
drawing_sources += eglib_DrawWChar.c
EXTRA_DIST += $(drawing_sources)

drawing_png =
drawing_png += eglib_AddUnicodeBlockToFont.png
drawing_png += eglib_ClearScreen.png
drawing_png += eglib_DrawArc.png
drawing_png += eglib_DrawBitmap.png
drawing_png += eglib_DrawBox.png
drawing_png += eglib_DrawCircle.png
drawing_png += eglib_DrawDisc.png
drawing_png += eglib_DrawFilledArc.png
drawing_png += eglib_DrawFrame.png
drawing_png += eglib_DrawGradientArc.png
drawing_png += eglib_DrawGradientBox.png
drawing_png += eglib_DrawGradientDisc.png
drawing_png += eglib_DrawGradientFilledArc.png
drawing_png += eglib_DrawGradientFrame.png
drawing_png += eglib_DrawGradientHLine.png
drawing_png += eglib_DrawGradientLine.png
drawing_png += eglib_DrawGradientVLine.png
drawing_png += eglib_DrawHLine.png
drawing_png += eglib_DrawLine.png
drawing_png += eglib_DrawPixelColor.png
drawing_png += eglib_DrawPixel.png
drawing_png += eglib_DrawRoundBox.png
drawing_png += eglib_DrawRoundFrame.png
drawing_png += eglib_DrawText.png
drawing_png += eglib_DrawTriangle.png
drawing_png += eglib_DrawVLine.png
drawing_png += eglib_DrawWChar.png
EXTRA_DIST += $(drawing_png)
BUILT_SOURCES = $(drawing_png)
$(drawing_png): drawing.test

check_PROGRAMS = drawing.test
drawing_test_SOURCES = drawing.c
EXTRA_drawing_test_DEPENDENCIES = $(drawing_sources)

TESTS = $(check_PROGRAMS)

.PHONY: clean-local
clean-local:
	-rm -f *.tga

@VALGRIND_CHECK_RULES@