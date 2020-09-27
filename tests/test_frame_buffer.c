#include <eglib.h>
#include <eglib/hal/4wire_spi/none.h>
#include <eglib/display/4wire_spi/tga.h>
#include <eglib/display/4wire_spi/frame_buffer.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	eglib_t eglib;
	eglib_coordinate_t width, height;
	eglib_display_4wire_spi_tga_config_t eglib_display_4wire_spi_tga_config = {
		.width = 100,
		.height = 100,
	};
	eglib_display_4wire_spi_frame_buffer_config_t eglib_display_4wire_spi_frame_buffer_config = {
		.display = &eglib_display_4wire_spi_tga,
		.display_config = &eglib_display_4wire_spi_tga_config,
	};

	setbuf(stdout, NULL);

	eglib_Init_4wire_spi(
		&eglib,
		&eglib_hal_4wire_spi_none, NULL,
		&eglib_display_4wire_spi_frame_buffer, &eglib_display_4wire_spi_frame_buffer_config
	);

	width = eglib_GetWidth(&eglib);
	height = eglib_GetHeight(&eglib);

	eglib_SetColor(&eglib, 0, 0, 0, 0);
	for(eglib_coordinate_t v=0 ; (v < width) && (v < height) ; v++ )
		eglib_DrawPixel(&eglib, v, v);

	eglib_SetClipRange(&eglib, 0, 0, width / 2, height / 2);

	eglib_SetColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, width - 1, 0);

	eglib_SetColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib, 0, height - 1, 0, 0);

	eglib_SetColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib, 0, 0, width - 1, height - 1);

	eglib_display_4wire_spi_frame_buffer_draw(&eglib);

	if(argc == 2)
		eglib_display_4wire_spi_tga_save(&eglib_display_4wire_spi_tga_config, argv[1]);
	else
		return 1;
}