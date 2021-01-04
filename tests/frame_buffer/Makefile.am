include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/frame_buffer

EXTRA_DIST =

expectations_pngs =
expectations_pngs += eglib_FrameBuffer_SendPartial.png
expectations_pngs += eglib_FrameBuffer_Send.png
expectations_pngs += eglib_FrameBuffer_SendUpdated.png
EXTRA_DIST += $(expectations_pngs)
BUILT_SOURCES = $(expectations_pngs)

check_PROGRAMS = frame_buffer.test
frame_buffer_test_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS)
frame_buffer_test_LDFLAGS = $(LDFLAGS_EGLIB)
frame_buffer_test_LDADD = ../libcommon.a $(LIBS_EGLIB) @CHECK_LIBS@
frame_buffer_test_CPPFLAGS = $(CPPFLAGS_EGLIB)
frame_buffer_test_SOURCES = frame_buffer.c

TESTS = $(check_PROGRAMS)

.PHONY: clean-local
clean-local:
	-rm -f *.tga

@VALGRIND_CHECK_RULES@