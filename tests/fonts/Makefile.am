include ../common.mk

SUBDIRS = . adobe liberation

check_HEADERS = unicode_block.h
check_LIBRARIES = libunicode_block.a
libunicode_block_a_CFLAGS = @CHECK_CFLAGS@ $(CFLAGS_WARNINGS)
libunicode_block_a_CPPFLAGS = $(CPPFLAGS_EGLIB)
libunicode_block_a_SOURCES = unicode_block.c

check-valgrind-local: libunicode_block.a