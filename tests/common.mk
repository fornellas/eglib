EGLIB_CFLAGS = -I$(top_builddir)/src -I$(top_srcdir)/src
EGLIB_LIBS = -leglib -L$(top_builddir)/src/ -lm

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh