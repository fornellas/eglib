include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/drawing

EXTRA_DIST =

drawing_test_sources =
drawing_test_sources += eglib_AddUnicodeBlockToFont.c
drawing_test_sources += eglib_ClearScreen.c
drawing_test_sources += eglib_DrawArc.c
drawing_test_sources += eglib_DrawBitmap.c
drawing_test_sources += eglib_DrawBox.c
drawing_test_sources += eglib_DrawCircle.c
drawing_test_sources += eglib_DrawDisc.c
drawing_test_sources += eglib_DrawFilledArc.c
drawing_test_sources += eglib_DrawFrame.c
drawing_test_sources += eglib_DrawGradientArc.c
drawing_test_sources += eglib_DrawGradientBox.c
drawing_test_sources += eglib_DrawGradientDisc.c
drawing_test_sources += eglib_DrawGradientFilledArc.c
drawing_test_sources += eglib_DrawGradientFrame.c
drawing_test_sources += eglib_DrawGradientHLine.c
drawing_test_sources += eglib_DrawGradientLine.c
drawing_test_sources += eglib_DrawGradientVLine.c
drawing_test_sources += eglib_DrawHLine.c
drawing_test_sources += eglib_DrawLine.c
drawing_test_sources += eglib_DrawPixelColor.c
drawing_test_sources += eglib_DrawPixel.c
drawing_test_sources += eglib_DrawRoundBox.c
drawing_test_sources += eglib_DrawRoundFrame.c
drawing_test_sources += eglib_DrawText.c
drawing_test_sources += eglib_DrawTriangle.c
drawing_test_sources += eglib_DrawVLine.c
drawing_test_sources += eglib_DrawWChar.c
EXTRA_DIST += $(drawing_test_sources)

drawing_expectation_pngs =
drawing_expectation_pngs += eglib_AddUnicodeBlockToFont.png
drawing_expectation_pngs += eglib_ClearScreen.png
drawing_expectation_pngs += eglib_DrawArc.png
drawing_expectation_pngs += eglib_DrawBitmap.png
drawing_expectation_pngs += eglib_DrawBox.png
drawing_expectation_pngs += eglib_DrawCircle.png
drawing_expectation_pngs += eglib_DrawDisc.png
drawing_expectation_pngs += eglib_DrawFilledArc.png
drawing_expectation_pngs += eglib_DrawFrame.png
drawing_expectation_pngs += eglib_DrawGradientArc.png
drawing_expectation_pngs += eglib_DrawGradientBox.png
drawing_expectation_pngs += eglib_DrawGradientDisc.png
drawing_expectation_pngs += eglib_DrawGradientFilledArc.png
drawing_expectation_pngs += eglib_DrawGradientFrame.png
drawing_expectation_pngs += eglib_DrawGradientHLine.png
drawing_expectation_pngs += eglib_DrawGradientLine.png
drawing_expectation_pngs += eglib_DrawGradientVLine.png
drawing_expectation_pngs += eglib_DrawHLine.png
drawing_expectation_pngs += eglib_DrawLine.png
drawing_expectation_pngs += eglib_DrawPixelColor.png
drawing_expectation_pngs += eglib_DrawPixel.png
drawing_expectation_pngs += eglib_DrawRoundBox.png
drawing_expectation_pngs += eglib_DrawRoundFrame.png
drawing_expectation_pngs += eglib_DrawText.png
drawing_expectation_pngs += eglib_DrawTriangle.png
drawing_expectation_pngs += eglib_DrawVLine.png
drawing_expectation_pngs += eglib_DrawWChar.png
EXTRA_DIST += $(drawing_expectation_pngs)
BUILT_SOURCES = $(drawing_expectation_pngs)

check_PROGRAMS = drawing.test
drawing_test_SOURCES = drawing.c
drawing_test_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(AM_CFLAGS)
drawing_test_LDADD = ../libcommon.a $(EGLIB_LIBS) @CHECK_LIBS@
drawing_test_DEPENDENCIES = $(drawing_test_sources)

TESTS = $(check_PROGRAMS)

.PHONY: clean-local
clean-local:
	-rm -f *.tga

@VALGRIND_CHECK_RULES@