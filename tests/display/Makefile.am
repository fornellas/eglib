EGLIB_CFLAGS = -I$(top_builddir)/font_generator -I$(top_srcdir)/src
EGLIB_LIBS = -L$(top_builddir)/src -leglib -lm

AM_CFLAGS = $(EGLIB_CFLAGS) @CHECK_CFLAGS@ $(COMMON_CFLAGS)
LDADD = $(EGLIB_LIBS) @CHECK_LIBS@

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh
AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/display/

check_PROGRAMS =
EXTRA_DIST =

EXTRA_DIST += sh1106.four_wire_spi.init
EXTRA_DIST += sh1106.four_wire_spi.sleep_in
EXTRA_DIST += sh1106.four_wire_spi.sleep_out
EXTRA_DIST += sh1106.four_wire_spi.get_dimension
EXTRA_DIST += sh1106.four_wire_spi.get_pixel_format
EXTRA_DIST += sh1106.four_wire_spi.draw_pixel_color
EXTRA_DIST += sh1106.four_wire_spi.draw_line
EXTRA_DIST += sh1106.four_wire_spi.send_buffer
EXTRA_DIST += sh1106.four_wire_spi.refresh
EXTRA_DIST += sh1106.i2c.init
EXTRA_DIST += sh1106.i2c.sleep_in
EXTRA_DIST += sh1106.i2c.sleep_out
EXTRA_DIST += sh1106.i2c.get_dimension
EXTRA_DIST += sh1106.i2c.get_pixel_format
EXTRA_DIST += sh1106.i2c.draw_pixel_color
EXTRA_DIST += sh1106.i2c.draw_line
EXTRA_DIST += sh1106.i2c.send_buffer
EXTRA_DIST += sh1106.i2c.refresh
check_PROGRAMS += sh1106.test
sh1106_test_SOURCES = display.c sh1106.c

EXTRA_DIST += ssd1331.four_wire_spi.init
EXTRA_DIST += ssd1331.four_wire_spi.sleep_in
EXTRA_DIST += ssd1331.four_wire_spi.sleep_out
EXTRA_DIST += ssd1331.four_wire_spi.get_dimension
EXTRA_DIST += ssd1331.four_wire_spi.get_pixel_format
EXTRA_DIST += ssd1331.four_wire_spi.draw_pixel_color
EXTRA_DIST += ssd1331.four_wire_spi.draw_line
EXTRA_DIST += ssd1331.four_wire_spi.send_buffer
EXTRA_DIST += ssd1331.four_wire_spi.refresh
check_PROGRAMS += ssd1331.test
ssd1331_test_SOURCES = display.c ssd1331.c

EXTRA_DIST += st7789.four_wire_spi.init
EXTRA_DIST += st7789.four_wire_spi.sleep_in
EXTRA_DIST += st7789.four_wire_spi.sleep_out
EXTRA_DIST += st7789.four_wire_spi.get_dimension
EXTRA_DIST += st7789.four_wire_spi.get_pixel_format
EXTRA_DIST += st7789.four_wire_spi.draw_pixel_color
EXTRA_DIST += st7789.four_wire_spi.draw_line
EXTRA_DIST += st7789.four_wire_spi.send_buffer
EXTRA_DIST += st7789.four_wire_spi.refresh
check_PROGRAMS += st7789.test
st7789_test_SOURCES = display.c st7789.c

TESTS = $(check_PROGRAMS)

@VALGRIND_CHECK_RULES@