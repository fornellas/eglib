include common.mk

SUBDIRS = . display drawing frame_buffer

check_LIBRARIES = libtga_tester.a
libtga_tester_a_SOURCES = tga_tester.c
libtga_tester_a_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(AM_CFLAGS)