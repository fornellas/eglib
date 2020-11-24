#include <eglib.h>
#include <eglib/hal/four_wire_spi/stdout.h>
#include <eglib/display/st7789.h>

int main(void) {
	eglib_t eglib;

	st7789_config_t st7789_config = {
		.width = 240,
		.height = 240,
		.color = ST7789_COLOR_16_BIT,
		.page_address = ST7789_PAGE_ADDRESS_TOP_TO_BOTTOM,
		.colum_address = ST7789_COLUMN_ADDRESS_LEFT_TO_RIGHT,
		.page_column_order = ST7789_PAGE_COLUMN_ORDER_NORMAL,
		.vertical_refresh = ST7789_VERTICAL_REFRESH_TOP_TO_BOTTOM,
		.horizontal_refresh = ST7789_HORIZONTAL_REFRESH_LEFT_TO_RIGHT,
	};


	eglib_Init(
		&eglib,
		&four_wire_spi_stdout, NULL,
		&st7789, &st7789_config
	);

	eglib_SetColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib,0, 0, st7789_config.width-1, st7789_config.height/2);

	eglib_SetColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib,0, 0, st7789_config.width-1, st7789_config.height-1);

	eglib_SetColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib,0, 0, st7789_config.width/2, st7789_config.height-1);
}