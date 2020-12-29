include ../common.mk

AM_TESTS_ENVIRONMENT = EXPECTATIONS_DIR=$(top_srcdir)/tests/display

AM_CFLAGS += $(EGLIB_CFLAGS) @CHECK_CFLAGS@
LDADD = ../libcommon.a $(EGLIB_LIBS) @CHECK_LIBS@

check_PROGRAMS =
EXTRA_DIST =

SH1106_EXPECTATIONS = sh1106.four_wire_spi.init
SH1106_EXPECTATIONS += sh1106.four_wire_spi.sleep_in
SH1106_EXPECTATIONS += sh1106.four_wire_spi.sleep_out
SH1106_EXPECTATIONS += sh1106.four_wire_spi.get_dimension
SH1106_EXPECTATIONS += sh1106.four_wire_spi.get_pixel_format
SH1106_EXPECTATIONS += sh1106.four_wire_spi.draw_pixel_color
SH1106_EXPECTATIONS += sh1106.four_wire_spi.draw_line
SH1106_EXPECTATIONS += sh1106.four_wire_spi.send_buffer
SH1106_EXPECTATIONS += sh1106.four_wire_spi.refresh
SH1106_EXPECTATIONS += sh1106.four_wire_spi.EntireDisplayOn
SH1106_EXPECTATIONS += sh1106.four_wire_spi.Reverse
SH1106_EXPECTATIONS += sh1106.four_wire_spi.SetContrast
SH1106_EXPECTATIONS += sh1106.four_wire_spi.SetStartLine
SH1106_EXPECTATIONS += sh1106.i2c.init
SH1106_EXPECTATIONS += sh1106.i2c.sleep_in
SH1106_EXPECTATIONS += sh1106.i2c.sleep_out
SH1106_EXPECTATIONS += sh1106.i2c.get_dimension
SH1106_EXPECTATIONS += sh1106.i2c.get_pixel_format
SH1106_EXPECTATIONS += sh1106.i2c.draw_pixel_color
SH1106_EXPECTATIONS += sh1106.i2c.draw_line
SH1106_EXPECTATIONS += sh1106.i2c.send_buffer
SH1106_EXPECTATIONS += sh1106.i2c.refresh
SH1106_EXPECTATIONS += sh1106.i2c.EntireDisplayOn
SH1106_EXPECTATIONS += sh1106.i2c.Reverse
SH1106_EXPECTATIONS += sh1106.i2c.SetContrast
SH1106_EXPECTATIONS += sh1106.i2c.SetStartLine
EXTRA_DIST += $(SH1106_EXPECTATIONS)
check_PROGRAMS += sh1106.test
sh1106_test_SOURCES = display.c sh1106.c
sh1106_test_DEPENDENCIES = $(SH1106_EXPECTATIONS)

SSD1331_EXPECTATIONS = ssd1331.four_wire_spi.init
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.sleep_in
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.sleep_out
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.get_dimension
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.get_pixel_format
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.draw_pixel_color
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.draw_line
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.send_buffer
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.refresh
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.DrawBox
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.DrawFrame
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.DrawLine
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.SetDimMode
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.SetDisplayMode
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.SetDisplayStartLine
SSD1331_EXPECTATIONS += ssd1331.four_wire_spi.SetMasterCurrent
EXTRA_DIST += $(SSD1331_EXPECTATIONS)
check_PROGRAMS += ssd1331.test
ssd1331_test_SOURCES = display.c ssd1331.c
ssd1331_test_DEPENDENCIES = $(SSD1331_EXPECTATIONS)

ST7789_EXPECTATIONS = st7789.four_wire_spi.init
ST7789_EXPECTATIONS += st7789.four_wire_spi.sleep_in
ST7789_EXPECTATIONS += st7789.four_wire_spi.sleep_out
ST7789_EXPECTATIONS += st7789.four_wire_spi.get_dimension
ST7789_EXPECTATIONS += st7789.four_wire_spi.get_pixel_format
ST7789_EXPECTATIONS += st7789.four_wire_spi.draw_pixel_color
ST7789_EXPECTATIONS += st7789.four_wire_spi.draw_line
ST7789_EXPECTATIONS += st7789.four_wire_spi.send_buffer
ST7789_EXPECTATIONS += st7789.four_wire_spi.refresh
ST7789_EXPECTATIONS += st7789.four_wire_spi.SetDisplayInversion
ST7789_EXPECTATIONS += st7789.four_wire_spi.SetIdleMode
EXTRA_DIST += $(ST7789_EXPECTATIONS)
check_PROGRAMS += st7789.test
st7789_test_SOURCES = display.c st7789.c
st7789_test_DEPENDENCIES = $(ST7789_EXPECTATIONS)

TESTS = $(check_PROGRAMS)

@VALGRIND_CHECK_RULES@