#include "tga.h"
#include "frame_buffer.h"

#include <stdlib.h>
#include <stdio.h>

static void init(eglib_t *eglib) {
	tga_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	display_config->tga_data = (uint8_t *)calloc(
		display_config->width * display_config->height,
		3
	);
	if ( display_config->tga_data == NULL )
		exit(1);
}

static void sleep_in(eglib_t *eglib) {
	(void)eglib;
}

static void sleep_out(eglib_t *eglib) {
	(void)eglib;
}

static void get_dimension(
	eglib_t *eglib,
	coordinate_t *width,
	coordinate_t *height
) {
	tga_config_t *display_config;

	display_config = eglib_GetDisplayConfig(eglib);

	*width = display_config->width;
	*height = display_config->height;
}

static void get_pixel_format(eglib_t *eglib, enum pixel_format_t *pixel_format) {
	(void)eglib;

	*pixel_format = PIXEL_FORMAT_24BIT_RGB;
}

static void draw_pixel_color(
	eglib_t *eglib,
	coordinate_t x,
	coordinate_t y,
	color_t color
) {
	tga_config_t *display_config;
	uint8_t *p;

	display_config = eglib_GetDisplayConfig(eglib);

	if(x >= display_config->width || y >= display_config->height || x < 0 || y < 0)
		return;

	p = (display_config->tga_data) + (display_config->width-y-1)*display_config->height*3 + x*3;
	*p++ = color.b;
	*p++ = color.g;
	*p++ = color.r;
}

static void send_buffer(
       eglib_t *eglib,
       void *buffer_ptr,
       coordinate_t x, coordinate_t y,
       coordinate_t width, coordinate_t height
) {
       uint8_t *buffer = (uint8_t *)buffer_ptr;
       color_t color;
       coordinate_t y_start, y_end, x_start, x_end;

       y_start = x;
       y_end = y + height;
       x_start = x;
       x_end = x + width;

       for(y = y_start; y <= y_end ; y++) {
               for(x = x_start; x <= x_end ; x++) {
                       color.r = *buffer;
                       buffer++;
                       color.g = *buffer;
                       buffer++;
                       color.b = *buffer;
                       buffer++;
                       eglib_DrawPixelColor(
                               eglib,
                               x, y,
                               color
                       );
               }
       }
}

static bool refresh(eglib_t *eglib) {
	(void)eglib;
	return false;
}

static hal_four_wire_spi_config_t four_wire_spi_config = {
		.mode = 0,
		.bit_numbering = HAL_MSB_FIRST,
		.cs_setup_ns = 0,
		.cs_hold_ns = 0,
		.cs_disable_ns = 0,
		.dc_setup_ns = 0,
		.dc_hold_ns = 0,
		.sck_cycle_ns = 0,
};

const display_t tga = {
	.comm.four_wire_spi = &four_wire_spi_config,
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_pixel_format = get_pixel_format,
	.draw_pixel_color = draw_pixel_color,
	.draw_line = display_default_draw_line,
	.send_buffer = send_buffer,
	.refresh = refresh,
};

static void tga_write_byte(FILE *fp, uint8_t byte) {
	fputc(byte, fp);
}

static void tga_write_word(FILE *fp, uint16_t word) {
	tga_write_byte(fp, word&255);
	tga_write_byte(fp, word>>8);
}

void tga_Save(eglib_t *eglib, char *path) {
	tga_config_t *display_config;
	FILE *fp;

	display_config = eglib_GetDisplayConfig(eglib);

	fp = fopen(path, "wb");
	if ( fp != NULL ) {
		tga_write_byte(fp, 0);		/* no ID */
		tga_write_byte(fp, 0);		/* no color map */
		tga_write_byte(fp, 2);		/* uncompressed true color */
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		tga_write_byte(fp, 0);
		tga_write_word(fp, 0);		/* x origin */
		tga_write_word(fp, 0);		/* y origin */
		tga_write_word(fp, display_config->width);		/* width */
		tga_write_word(fp, display_config->height);		/* height */
		tga_write_byte(fp, 24);		/* color depth */
		tga_write_byte(fp, 0);
		fwrite(display_config->tga_data, 3, display_config->width * display_config->height, fp);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		fwrite("TRUEVISION-XFILE.", 18, 1, fp);
		fclose(fp);
	}
}