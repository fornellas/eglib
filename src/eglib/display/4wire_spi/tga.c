#include "tga.h"
#include "frame_buffer.h"

#include <stdlib.h>
#include <stdio.h>

static uint8_t *tga_data = NULL;

static void init(eglib_t *eglib) {
	eglib_display_4wire_spi_tga_config_t *display_config;

	display_config = eglib_Get4WireSPIDisplayConfig(eglib);

	if ( tga_data != NULL )
		free(tga_data);
	tga_data = (uint8_t *)calloc(
		display_config->width * display_config->height,
		3 * sizeof(uint8_t)
	);
	if ( tga_data == NULL )
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
	eglib_coordinate_t *width,
	eglib_coordinate_t *height
) {
	eglib_display_4wire_spi_tga_config_t *display_config;

	display_config = eglib_Get4WireSPIDisplayConfig(eglib);

	*width = display_config->width;
	*height = display_config->height;
}

static void get_color_depth(eglib_t *eglib, eglib_color_depth_t *color_depth) {
	(void)eglib;

	*color_depth = EGLIB_COLOR_DEPTH_24BIT_RGB;
}

static void draw_pixel_color(
	eglib_t *eglib,
	eglib_coordinate_t x,
	eglib_coordinate_t y,
	eglib_color_t color
) {
	eglib_display_4wire_spi_tga_config_t *display_config;
	uint8_t *p;

	display_config = eglib_Get4WireSPIDisplayConfig(eglib);

	if(x >= display_config->width || y >= display_config->height || x < 0 || y < 0)
		return;

	if ( tga_data == NULL )
		return;

	p = tga_data + (display_config->width-y-1)*display_config->height*3 + x*3;
	*p++ = color.b;
	*p++ = color.g;
	*p++ = color.r;
}

const eglib_display_4wire_spi_t eglib_display_4wire_spi_tga = {
	.hal_4wire_spi_config_comm = {
		.mode = 0,
		.bit_numbering = EGLIB_HAL_4WIRE_SPI_LSB_FIRST,
		.cs_setup_ns = 0,
		.cs_hold_ns = 0,
		.cs_disable_ns = 0,
		.dc_setup_ns = 0,
		.dc_hold_ns = 0,
		.sck_cycle_ns = 0,
		.mosi_setup_ns = 0,
		.mosi_hold_ns = 0,
	},
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.get_dimension = get_dimension,
	.get_color_depth = get_color_depth,
	.draw_pixel_color = draw_pixel_color,
	.send_buffer = eglib_display_4wire_spi_frame_buffer_send_buffer_24bit_rgb,
};

static void tga_write_byte(FILE *fp, uint8_t byte) {
	fputc(byte, fp);
}

static void tga_write_word(FILE *fp, uint16_t word) {
	tga_write_byte(fp, word&255);
	tga_write_byte(fp, word>>8);
}

void eglib_display_4wire_spi_tga_save(eglib_display_4wire_spi_tga_config_t *display_config, char *path) {
	FILE *fp;
	fp = fopen(path, "wb");
	if ( fp != NULL )
	{
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
		fwrite(tga_data, display_config->width * display_config->height * 3, 1, fp);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		tga_write_word(fp, 0);
		fwrite("TRUEVISION-XFILE.", 18, 1, fp);
		fclose(fp);
	}
}