.PHONY: clean-tests-frame_buffer
clean-local: clean-tests-frame_buffer

if NOT_CROSS_COMPILE

EXTRA_DIST += %D%/expectation_pngs.tar

%D%/.expectations: $(top_srcdir)/%D%/expectation_pngs.tar
	tar xf $< -C %D%/
	touch $@

check_PROGRAMS += %D%/frame_buffer.test
TESTS += %D%/frame_buffer.test
tests_frame_buffer_frame_buffer_test_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS) -DRELDIR=\"%D%\"
tests_frame_buffer_frame_buffer_test_LDFLAGS = $(LDFLAGS_EGLIB)
tests_frame_buffer_frame_buffer_test_LDADD = tests/libcommon.a tests/fonts/libunicode_block.a $(LIBS_EGLIB) @CHECK_LIBS@
tests_frame_buffer_frame_buffer_test_CPPFLAGS = $(CPPFLAGS_EGLIB)
tests_frame_buffer_frame_buffer_test_SOURCES = %D%/frame_buffer.c
EXTRA_tests_frame_buffer_frame_buffer_test_DEPENDENCIES = %D%/.expectations

clean-tests-frame_buffer:
	rm -f %D%/*.tga %D%/*.png %D%/.expectations

else

clean-tests-frame_buffer:

endif