EGLIB_CFLAGS = -I$(top_builddir)/font_generator -I$(top_srcdir)/src
EGLIB_LIBS = -L$(top_builddir)/src -leglib -lm

AM_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(COMMON_CFLAGS)
LDADD = $(EGLIB_LIBS) @CHECK_LIBS@

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh

check_PROGRAMS =

check_PROGRAMS += sh1106.test
sh1106_test_SOURCES = display.c sh1106.c

check_PROGRAMS += ssd1331.test
ssd1331_test_SOURCES = display.c ssd1331.c

check_PROGRAMS += st7789.test
st7789_test_SOURCES = display.c st7789.c

TESTS = $(check_PROGRAMS)

@VALGRIND_CHECK_RULES@