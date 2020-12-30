include ../common.mk

SUBDIRS = . adobe liberation

check_LIBRARIES = libunicode_block.a
check_HEADERS = unicode_block.h
libunicode_block_a_SOURCES = unicode_block.c
libunicode_block_a_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(AM_CFLAGS)

check-valgrind-local: libunicode_block.a