include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/frame_buffer

EXTRA_DIST =

frame_buffer_pngs =
frame_buffer_pngs += eglib_FrameBuffer_SendPartial.png
frame_buffer_pngs += eglib_FrameBuffer_Send.png
frame_buffer_pngs += eglib_FrameBuffer_SendUpdated.png
EXTRA_DIST += $(frame_buffer_pngs)
BUILT_SOURCES = $(frame_buffer_pngs)

check_PROGRAMS = frame_buffer.test
frame_buffer_test_SOURCES = frame_buffer.c
frame_buffer_test_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(AM_CFLAGS)
frame_buffer_test_LDADD = ../libcommon.a $(EGLIB_LIBS) @CHECK_LIBS@

TESTS = $(check_PROGRAMS)

.PHONY: clean-local
clean-local:
	-rm -f *.tga

@VALGRIND_CHECK_RULES@