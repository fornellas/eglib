.PHONY: clean-tests-frame_buffer
clean-local: clean-tests-frame_buffer

if NOT_CROSS_COMPILE

tests_frame_buffer_expectations_pngs =
tests_frame_buffer_expectations_pngs += eglib_FrameBuffer_SendPartial.png
tests_frame_buffer_expectations_pngs += eglib_FrameBuffer_Send.png
tests_frame_buffer_expectations_pngs += eglib_FrameBuffer_SendUpdated.png
EXTRA_DIST += $(tests_frame_buffer_expectation_pngs)

check_PROGRAMS += %D%/frame_buffer.test
TESTS += %D%/frame_buffer.test
tests_frame_buffer_frame_buffer_test_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS) -DRELDIR=\"%D%\"
tests_frame_buffer_frame_buffer_test_LDFLAGS = $(LDFLAGS_EGLIB)
tests_frame_buffer_frame_buffer_test_LDADD = tests/libcommon.a tests/fonts/libunicode_block.a $(LIBS_EGLIB) @CHECK_LIBS@
tests_frame_buffer_frame_buffer_test_CPPFLAGS = $(CPPFLAGS_EGLIB)
tests_frame_buffer_frame_buffer_test_SOURCES = %D%/frame_buffer.c
EXTRA_tests_frame_buffer_frame_buffer_test_DEPENDENCIES = $(drawing_tests_frame_buffer_expectation_pngs)  $(drawing_test_sources)

clean-tests-fonts-frame_buffer:
	-rm -f %D%/*.tga

else

clean-tests-fonts-frame_buffer:

endif