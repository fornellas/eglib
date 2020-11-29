#include <eglib.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <eglib/display/tga.h>
#include <stdio.h>
#include "draw_test.h"

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

	draw_test(&eglib);

	if(argc == 2)
		tga_Save(&eglib, argv[1]);
	else
		return 1;
}