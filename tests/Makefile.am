include common.mk

SUBDIRS = . drawing fonts frame_buffer display

check_LIBRARIES = libcommon.a
check_HEADERS = common.h
libcommon_a_SOURCES = common.c
libcommon_a_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(AM_CFLAGS)