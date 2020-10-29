#include <eglib.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <eglib/display/tga.h>
#include <eglib/display/frame_buffer.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	eglib_t eglib_tga;
	eglib_display_tga_config_t tga_config = {
		.width = 100,
		.height = 100,
	};

	eglib_t eglib;
	eglib_display_t frame_buffer;
	eglib_display_frame_buffer_config_t frame_buffer_config;

	eglib_coordinate_t width, height;

	eglib_Init(
		&eglib_tga,
		&eglib_hal_four_wire_spi_none, NULL,
		&eglib_display_tga, &tga_config
	);

	eglib_Init_FrameBuffer(
		&eglib,
		&frame_buffer, &frame_buffer_config,
		&eglib_tga
	);

	setbuf(stdout, NULL);

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

	eglib_FrameBuffer_Send(&eglib, 0, 0, width - 1, height -1);

	if(argc == 2)
		eglib_display_tga_save(&tga_config, argv[1]);
	else
		return 1;
}