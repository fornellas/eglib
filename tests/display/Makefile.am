include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/display

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
EXTRA_DIST += sh1106.four_wire_spi.EntireDisplayOn
EXTRA_DIST += sh1106.four_wire_spi.Reverse
EXTRA_DIST += sh1106.four_wire_spi.SetContrast
EXTRA_DIST += sh1106.four_wire_spi.SetStartLine
EXTRA_DIST += sh1106.i2c.init
EXTRA_DIST += sh1106.i2c.sleep_in
EXTRA_DIST += sh1106.i2c.sleep_out
EXTRA_DIST += sh1106.i2c.get_dimension
EXTRA_DIST += sh1106.i2c.get_pixel_format
EXTRA_DIST += sh1106.i2c.draw_pixel_color
EXTRA_DIST += sh1106.i2c.draw_line
EXTRA_DIST += sh1106.i2c.send_buffer
EXTRA_DIST += sh1106.i2c.refresh
EXTRA_DIST += sh1106.i2c.EntireDisplayOn
EXTRA_DIST += sh1106.i2c.Reverse
EXTRA_DIST += sh1106.i2c.SetContrast
EXTRA_DIST += sh1106.i2c.SetStartLine
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
EXTRA_DIST += ssd1331.four_wire_spi.DrawBox
EXTRA_DIST += ssd1331.four_wire_spi.DrawFrame
EXTRA_DIST += ssd1331.four_wire_spi.DrawLine
EXTRA_DIST += ssd1331.four_wire_spi.SetDimMode
EXTRA_DIST += ssd1331.four_wire_spi.SetDisplayMode
EXTRA_DIST += ssd1331.four_wire_spi.SetDisplayStartLine
EXTRA_DIST += ssd1331.four_wire_spi.SetMasterCurrent
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
EXTRA_DIST += st7789.four_wire_spi.SetDisplayInversion
EXTRA_DIST += st7789.four_wire_spi.SetIdleMode
check_PROGRAMS += st7789.test
st7789_test_SOURCES = display.c st7789.c

TESTS = $(check_PROGRAMS)

@VALGRIND_CHECK_RULES@