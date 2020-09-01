#include "tga.h"

#include <stdlib.h>
#include <stdio.h>

#define WIDTH 256
#define HEIGHT 256


static uint8_t *tga_data = NULL;


static void power_up(void) {
  if ( tga_data != NULL )
    free(tga_data);
  tga_data = (uint8_t *)calloc(WIDTH * HEIGHT, 3 * sizeof(uint8_t));
  if ( tga_data == NULL )
    exit(1);
}

static void power_down(void) {
  if ( tga_data != NULL )
    free(tga_data);
}

static void get_dimension(eglib_coordinate_t *width, eglib_coordinate_t*height) {
	*width = WIDTH;
	*height = HEIGHT;
}

static void draw_pixel(eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color) {
  uint8_t *p;

  p = tga_data + (WIDTH-y-1)*HEIGHT*3 + x*3;
  *p++ = color.b;
  *p++ = color.g;
  *p++ = color.r;
}

const eglib_display_t eglib_display_tga = {
	.clock_ns = 0,
	.power_up = power_up,
	.power_down = power_down,
	.get_dimension = get_dimension,
	.draw_pixel = draw_pixel,
};

static void tga_write_byte(FILE *fp, uint8_t byte) {
  fputc(byte, fp);
}

static void tga_write_word(FILE *fp, uint16_t word) {
  tga_write_byte(fp, word&255);
  tga_write_byte(fp, word>>8);
}

void eglib_display_tga_save(char *path) {
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
    tga_write_word(fp, WIDTH);		/* width */
    tga_write_word(fp, HEIGHT);		/* height */
    tga_write_byte(fp, 24);		/* color depth */
    tga_write_byte(fp, 0);
    fwrite(tga_data, WIDTH*HEIGHT*3, 1, fp);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    fwrite("TRUEVISION-XFILE.", 18, 1, fp);
    fclose(fp);
  }
}