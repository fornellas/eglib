#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdio.h>
#include <stdlib.h>
#include <freetype/fterrors.h>
#include <stdint.h>
#include <stdbool.h>

void exit_error(FT_Error error, const char *msg);

void exit_error(FT_Error error, const char *msg) {
	const char *error_str;

	fprintf(stderr, "%s", msg);

	error_str = FT_Error_String(error);
	if(error_str == NULL) {
		fprintf(stderr, ".\n");
	} else {
		fprintf(stderr, "%s.\n", error_str);
	}
	exit(error);
}

int main(int argc, char *argv[]) {
	FT_Library  library;
	FT_Error error;
	FT_Face face;
	FT_Long face_index;
	char *filepathname;
	uint8_t pixel_size;
	FT_ULong charcode_start, charcode_end;
	char *font_name;

	if(argc != 7) {
		fprintf(stderr, "Usage: %s [font path] [font name] [face index] [pixel size] [charcode start] [charcode end]\n", argv[0]);
		exit(1);
	}

	filepathname = argv[1];
	font_name = argv[2];
	face_index = atol(argv[3]);
	pixel_size = atol(argv[4]);
	charcode_start = atol(argv[5]);
	charcode_end = atol(argv[6]);

	error = FT_Init_FreeType(&library);
	if(error)
		exit_error(error, "Failed to initialize the Freetype library");

	error = FT_New_Face(library, filepathname, face_index, &face);
	if(error)
		exit_error(error, "Failed to open font");

	error = FT_Set_Pixel_Sizes(face, 0, pixel_size);
	if(error)
		exit_error(error, "Failed to set pixel size");

	printf("#include \"../../drawing.h\"\n");
	printf("\n");
	printf("struct font_t font_%s = {\n", font_name);
	printf("  .pixel_size = %d,\n", pixel_size);
	printf("  .ascent = %ld,\n", face->size->metrics.ascender >> 6);
	printf("  .descent = %ld,\n", face->size->metrics.descender >> 6);
	printf("  .line_space = %ld,\n", face->size->metrics.height >> 6);
	printf("  .charcode_start = %ld,\n", charcode_start);
	printf("  .charcode_end = %ld,\n", charcode_end);
	printf("  .glyphs = (struct glyph_t *[]){\n");

	for(FT_ULong charcode = charcode_start ; charcode <= charcode_end ; charcode++) {
		uint16_t x_start, x_end, y_start, y_end;
		int16_t width, height, left, advance, top;
		uint8_t byte;
		uint16_t bits;

		error = FT_Load_Char(face, charcode, FT_LOAD_RENDER | FT_LOAD_MONOCHROME);
		if(error)
			exit_error(error, "Failed to load character");

		x_start = face->glyph->bitmap.width;
		x_end = 0;
		y_start = face->glyph->bitmap.rows;
		y_end = 0;
		for(uint16_t y=0 ; y < face->glyph->bitmap.rows ; y++) {
			unsigned char*row_buffer;

			row_buffer = face->glyph->bitmap.buffer + (y * face->glyph->bitmap.pitch);

			for(uint16_t x=0 ; x < face->glyph->bitmap.width ; x++) {
				if(row_buffer[x / 8] & (1<<(7-(x % 8)))) {
					if(x < x_start)
						x_start = x;
					if(x > x_end)
						x_end = x;
					if(y < y_start)
						y_start = y;
					y_end = y;
				}
			}
		}
		if(x_start == face->glyph->bitmap.width)
			x_start = 0;
		if(y_start == face->glyph->bitmap.rows)
			y_start = 0;

		width = x_end - x_start + 1;
		if(width < 0) {
			fprintf(stderr, "Negative width: %d.\n", width);
			exit(1);
		}
		height = y_end - y_start + 1;
		if(height < 0) {
			fprintf(stderr, "Negative height: %d.\n", height);
			exit(1);
		}
		left = face->glyph->bitmap_left + x_start;
		top = face->glyph->bitmap_top - y_start;
		advance = face->glyph->advance.x >> 6;

		printf("    &(struct glyph_t){\n");
		printf("      .width = %d,\n", width);
		printf("      .height = %d,\n", height);
		printf("      .left = %d,\n", left);
		printf("      .top = %d,\n", top);
		printf("      .advance = %d,\n", advance);
		printf("      .data = (uint8_t []){");

		byte = 0;
		bits = 0;
		for(uint16_t y=y_start ; y <= y_end ; y++) {
			unsigned char*row_buffer;

			row_buffer = face->glyph->bitmap.buffer + (y * face->glyph->bitmap.pitch);

			for(uint16_t x=x_start ; x <= x_end ; x++) {
				bool pixel;
				pixel = row_buffer[x / 8] & (1<<(7-(x % 8)));

				if(pixel)
					byte |= (1<<(7 - (bits % 8)));

				bits++;

				if(!(bits % 8)) {
					if(bits > 8)
						printf(", ");
					printf("0x%x", byte);
					byte = 0;
				}
			}
		}
		if((bits % 8)) {
			if(bits > 8)
				printf(", ");
			printf("0x%x", byte);
		}

		printf("},\n");
		printf("    },\n");
	}

	printf("  },\n");
	printf("};\n");
}