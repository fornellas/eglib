#include <eglib.h>
#include <eglib/hal/four_wire_spi/stdout.h>
#include <eglib/display/ssd1331.h>

int main(void) {
	eglib_t eglib;

	eglib_Init(
		&eglib,
		&four_wire_spi_stdout, NULL,
		&ssd1331, &ssd1331_config_adafruit_65k_colors
	);

	for(uint16_t y=0;y<SSD1331_HEIGHT;y++) {
		uint8_t v;
		v = y / ((float)SSD1331_WIDTH-1) * 255;
		eglib_SetIndexColor(&eglib, 0, v, v, v);
		eglib_DrawLine(&eglib,0, y, SSD1331_WIDTH-1, y);
	}

	eglib_SetIndexColor(&eglib, 0, 255, 255, 255);
	eglib_DrawVLine(&eglib, SSD1331_WIDTH/2, 0, SSD1331_HEIGHT);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, SSD1331_WIDTH-1, SSD1331_HEIGHT/2);

	eglib_SetIndexColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib,0, 0, SSD1331_WIDTH-1, SSD1331_HEIGHT-1);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib,0, 0, SSD1331_WIDTH/2, SSD1331_HEIGHT-1);
}