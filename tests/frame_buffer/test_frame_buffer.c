#include <eglib.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <eglib/display/tga.h>
#include <eglib/display/frame_buffer.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	tga_config_t tga_config = {
		.width = 100,
		.height = 100,
	};

	eglib_t eglib;
	eglib_t *eglib_tga;
	frame_buffer_config_t frame_buffer_config;

	coordinate_t width, height;
	
	setbuf(stdout, NULL);

	eglib_tga = eglib_Init_FrameBuffer(
		&eglib, &frame_buffer_config,
		&four_wire_spi_none, NULL,
		&tga, &tga_config
	);


	width = eglib_GetWidth(&eglib);
	height = eglib_GetHeight(&eglib);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 0);
	for(coordinate_t v=0 ; (v < width) && (v < height) ; v++ )
		eglib_DrawPixel(&eglib, v, v);

	eglib_SetClipRange(&eglib, 0, 0, width / 2, height / 2);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, width - 1, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib, 0, height - 1, 0, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib, 0, 0, width - 1, height - 1);

	eglib_FrameBuffer_Send(&eglib, 0, 0, width - 1, height -1);

	if(argc == 2)
		tga_Save(eglib_tga, argv[1]);
	else
		return 1;
}