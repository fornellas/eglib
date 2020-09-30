#include <eglib.h>
#include <eglib/hal/4wire_spi/none.h>
#include <eglib/display/4wire_spi/tga.h>
#include <eglib/display/4wire_spi/frame_buffer.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	eglib_t eglib;
	eglib_coordinate_t width, height;
	eglib_display_4wire_spi_tga_config_t tga_config;
	eglib_display_4wire_spi_frame_buffer_config_t frame_buffer_config;
	eglib_display_4wire_spi_t display_frame_buffer;

	tga_config.width = 100;
	tga_config.height = 100;

	eglib_display_4wire_spi_frame_buffer_display_init(
		&display_frame_buffer,
		&eglib_display_4wire_spi_tga
	);

	eglib_display_4wire_spi_frame_buffer_config_init(
		&frame_buffer_config,
		&eglib_display_4wire_spi_tga,
		&tga_config
	);

	setbuf(stdout, NULL);

	eglib_Init_4WireSPI(
		&eglib,
		&eglib_hal_4wire_spi_none, NULL,
		&display_frame_buffer, &frame_buffer_config
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

	eglib_display_4wire_spi_frame_buffer_send(&eglib, 0, 0, width - 1, height -1);

	if(argc == 2)
		eglib_display_4wire_spi_tga_save(&tga_config, argv[1]);
	else
		return 1;
}