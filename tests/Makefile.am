if NOT_CROSS_COMPILE

include common.mk

SUBDIRS = . drawing fonts frame_buffer display

check_HEADERS = common.h
check_LIBRARIES = libcommon.a
libcommon_a_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS)
libcommon_a_CPPFLAGS = $(CPPFLAGS_EGLIB)
libcommon_a_SOURCES = common.c

check-valgrind-local: libcommon.a

endif