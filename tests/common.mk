EGLIB_CFLAGS = -I$(top_builddir)/font_generator -I$(top_srcdir)/src
EGLIB_LIBS = -L$(top_builddir)/src -leglib -lm

AM_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(COMMON_CFLAGS)
LDADD = $(EGLIB_LIBS) @CHECK_LIBS@

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh