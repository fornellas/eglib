#include <eglib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	eglib_t eglib;

	setbuf(stdout, NULL);

	eglib_Init(&eglib, &eglib_display_tga, &eglib_comm_none);
	eglib_PowerUp(&eglib);

	eglib_SetColor(&eglib, 0, 0, 0, 0);
	for(eglib_coordinate_t x=0, y=0 ; x < eglib_GetWidth(&eglib), y < eglib_GetHeight(&eglib) ; x++, y++) {
		eglib_DrawPixel(&eglib, x, y);
	}

	eglib_SetClipRange(&eglib, 0, 0, eglib_GetWidth(&eglib) / 2, eglib_GetHeight(&eglib) / 2);

	eglib_SetColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, eglib_GetWidth(&eglib) - 1, 0);

	eglib_SetColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib, 0, eglib_GetHeight(&eglib) - 1, 0, 0);

	eglib_SetColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib, 0, 0, eglib_GetWidth(&eglib) - 1, eglib_GetHeight(&eglib) - 1);

	if(argc == 2)
		eglib_display_tga_save(argv[1]);
	else
		return 1;
}