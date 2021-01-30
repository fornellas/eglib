.PHONY: clean-tests-drawing
clean-local: clean-tests-drawing

if NOT_CROSS_COMPILE

tests_drawing_test_sources =
tests_drawing_test_sources += %D%/eglib_AddUnicodeBlockToFont.c
tests_drawing_test_sources += %D%/eglib_ClearScreen.c
tests_drawing_test_sources += %D%/eglib_DrawArc.c
tests_drawing_test_sources += %D%/eglib_DrawBitmap.c
tests_drawing_test_sources += %D%/eglib_DrawBox.c
tests_drawing_test_sources += %D%/eglib_DrawCircle.c
tests_drawing_test_sources += %D%/eglib_DrawDisc.c
tests_drawing_test_sources += %D%/eglib_DrawFilledArc.c
tests_drawing_test_sources += %D%/eglib_DrawFrame.c
tests_drawing_test_sources += %D%/eglib_DrawGradientArc.c
tests_drawing_test_sources += %D%/eglib_DrawGradientBox.c
tests_drawing_test_sources += %D%/eglib_DrawGradientDisc.c
tests_drawing_test_sources += %D%/eglib_DrawGradientFilledArc.c
tests_drawing_test_sources += %D%/eglib_DrawGradientFrame.c
tests_drawing_test_sources += %D%/eglib_DrawGradientHLine.c
tests_drawing_test_sources += %D%/eglib_DrawGradientLine.c
tests_drawing_test_sources += %D%/eglib_DrawGradientVLine.c
tests_drawing_test_sources += %D%/eglib_DrawHLine.c
tests_drawing_test_sources += %D%/eglib_DrawLine.c
tests_drawing_test_sources += %D%/eglib_DrawPixelColor.c
tests_drawing_test_sources += %D%/eglib_DrawPixel.c
tests_drawing_test_sources += %D%/eglib_DrawRoundBox.c
tests_drawing_test_sources += %D%/eglib_DrawRoundFrame.c
tests_drawing_test_sources += %D%/eglib_DrawText.c
tests_drawing_test_sources += %D%/eglib_DrawTriangle.c
tests_drawing_test_sources += %D%/eglib_DrawVLine.c
tests_drawing_test_sources += %D%/eglib_DrawWChar.c
EXTRA_DIST += $(tests_drawing_test_sources)

tests_drawing_expectation_pngs =
tests_drawing_expectation_pngs += %D%/eglib_AddUnicodeBlockToFont.png
tests_drawing_expectation_pngs += %D%/eglib_ClearScreen.png
tests_drawing_expectation_pngs += %D%/eglib_DrawArc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawBitmap.png
tests_drawing_expectation_pngs += %D%/eglib_DrawBox.png
tests_drawing_expectation_pngs += %D%/eglib_DrawCircle.png
tests_drawing_expectation_pngs += %D%/eglib_DrawDisc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawFilledArc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawFrame.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientArc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientBox.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientDisc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientFilledArc.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientFrame.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientHLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawGradientVLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawHLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawPixelColor.png
tests_drawing_expectation_pngs += %D%/eglib_DrawPixel.png
tests_drawing_expectation_pngs += %D%/eglib_DrawRoundBox.png
tests_drawing_expectation_pngs += %D%/eglib_DrawRoundFrame.png
tests_drawing_expectation_pngs += %D%/eglib_DrawText.png
tests_drawing_expectation_pngs += %D%/eglib_DrawTriangle.png
tests_drawing_expectation_pngs += %D%/eglib_DrawVLine.png
tests_drawing_expectation_pngs += %D%/eglib_DrawWChar.png
EXTRA_DIST += $(tests_drawing_expectation_pngs)

check_PROGRAMS += %D%/drawing.test
TESTS += %D%/drawing.test
tests_drawing_drawing_test_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS) -DRELDIR=\"%D%\"
tests_drawing_drawing_test_LDFLAGS = $(LDFLAGS_EGLIB)
tests_drawing_drawing_test_LDADD = tests/libcommon.a $(LIBS_EGLIB) @CHECK_LIBS@
tests_drawing_drawing_test_CPPFLAGS = $(CPPFLAGS_EGLIB)
tests_drawing_drawing_test_SOURCES = %D%/drawing.c
EXTRA_tests_drawing_drawing_test_DEPENDENCIES = $(tests_drawing_expectation_pngs)  $(tests_drawing_test_sources)

clean-tests-drawing:
	-rm -f %D%/*.tga

else

clean-tests-drawing:

endif