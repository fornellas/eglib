#include <eglib.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <eglib/display/tga.h>

#include <stdio.h>

#define CHARS_PER_ROW 32

int main(int argc, char *argv[]) {
	eglib_t eglib_probe;
	tga_config_t tga_config_probe = {
		.width = 100,
		.height = 100,
	};
	eglib_t eglib;
	tga_config_t tga_config;
	coordinate_t width;
	int rows;
	wchar_t charcode;

	setvbuf(stdout, NULL, _IONBF, 0);

	eglib_Init(&eglib_probe, &four_wire_spi_none, NULL, &tga, &tga_config_probe);

	eglib_SetFont(&eglib_probe, &FONT);
	eglib_AddUnicodeBlockToFont(&FONT, &UNICODE_BLOCK);

	width = 0;

	rows = 0;
	for(charcode = UNICODE_BLOCK.charcode_start ; charcode <= UNICODE_BLOCK.charcode_end ; ) {
		wchar_t charcode_end;
		coordinate_t new_width;
		struct glyph_t *glyph;

		rows++;

		charcode_end = charcode + CHARS_PER_ROW;
		new_width = 0;
		for(;charcode < charcode_end && charcode <= UNICODE_BLOCK.charcode_end; charcode++) {
			glyph = eglib_GetGlyph(&eglib_probe, charcode);
			if(glyph == NULL)
				new_width += FONT.pixel_size;
			else
				new_width += glyph->advance;
		}
		if(new_width > width)
			width = new_width;
	}

	tga_config.width = width;
	tga_config.height = FONT.line_space * rows;

	eglib_Init(&eglib, &four_wire_spi_none, NULL, &tga, &tga_config);

	eglib_SetIndexColor(&eglib, 0, 255, 255, 255);
	eglib_ClearScreen(&eglib);

	eglib_SetFont(&eglib, &FONT);
	eglib_SetIndexColor(&eglib, 0, 0, 0, 0);
	charcode = UNICODE_BLOCK.charcode_start;
	for(int row=0 ; row < rows ; row++) {
		struct glyph_t *glyph;
		coordinate_t x;

		x=0;
		for(int i=0 ; i < CHARS_PER_ROW && charcode <= UNICODE_BLOCK.charcode_end; i++) {
			glyph = eglib_GetGlyph(&eglib, charcode);
			eglib_DrawGlyph(&eglib, x, row * FONT.line_space + FONT.ascent, glyph);
			if(glyph == NULL)
				x += FONT.pixel_size;
			else
				x += glyph->advance;
			charcode++;
		}
	}

	if(argc == 2)
		tga_Save(&eglib, argv[1]);
	else
		return 1;
}