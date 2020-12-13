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

	eglib_tga = eglib_Init_FrameBuffer(
		&eglib, &frame_buffer_config,
		&four_wire_spi_none, NULL,
		&tga, &tga_config
	);

	eglib_SetIndexColor(&eglib, 0, 255, 255, 255);
	eglib_DrawBox(&eglib, 25, 25, 50, 50);

	eglib_FrameBuffer_SendUpdated(&eglib);

	if(argc == 2)
		tga_Save(eglib_tga, argv[1]);
	else
		return 1;
}