#include <eglib.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <eglib/display/tga.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	eglib_t eglib;
	tga_config_t tga_config = {
		.width = 100,
		.height = 100,
	};

	setbuf(stdout, NULL);

	eglib_Init(
		&eglib,
		&four_wire_spi_none, NULL,
		&tga, &tga_config
	);

	eglib_ClearScreen(&eglib);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_DrawFrame(&eglib, 10, 20, 10, 20);

	eglib_SetIndexColor(&eglib, 0, 0, 255, 0);
	eglib_DrawBox(&eglib, 10, 50, 10, 20);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_SetIndexColor(&eglib, 1, 0, 255, 0);
	eglib_SetIndexColor(&eglib, 2, 0, 0, 255);
	eglib_SetIndexColor(&eglib, 3, 255, 255, 255);
	eglib_DrawGradientFrame(&eglib, 30, 20, 10, 20);

	eglib_DrawGradientBox(&eglib, 30, 50, 10, 20);

	if(argc == 2)
		tga_Save(&eglib, argv[1]);
	else
		return 1;
}