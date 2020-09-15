#include "tga.h"

#include <stdlib.h>
#include <stdio.h>

static uint8_t *tga_data = NULL;

static void power_up(eglib_hal_4wire_spi_t *hal, void *hal_config, void *display_config) {
  (void)hal;
  (void)hal_config;
  eglib_display_4wire_spi_tga_config_t *config = (eglib_display_4wire_spi_tga_config_t *)display_config;

  if ( tga_data != NULL )
    free(tga_data);
  tga_data = (uint8_t *)calloc(config->width * config->height, 3 * sizeof(uint8_t));
  if ( tga_data == NULL )
    exit(1);
}

static void power_down(eglib_hal_4wire_spi_t *hal, void *hal_config, void *display_config) {
  (void)hal;
  (void)hal_config;
  (void)display_config;
  
  if ( tga_data != NULL )
    free(tga_data);
}

static void get_dimension(eglib_hal_4wire_spi_t *hal, void *hal_config, void *display_config, eglib_coordinate_t *width, eglib_coordinate_t*height) {
  (void)hal;
  (void)hal_config;
  eglib_display_4wire_spi_tga_config_t *config = (eglib_display_4wire_spi_tga_config_t *)display_config;

	*width = config->width;
	*height = config->height;
}

static void draw_pixel(eglib_hal_4wire_spi_t *hal, void *hal_config, void *display_config, eglib_coordinate_t x, eglib_coordinate_t y, eglib_color_t color) {
  (void)hal;
  (void)hal_config;
  eglib_display_4wire_spi_tga_config_t *config = (eglib_display_4wire_spi_tga_config_t *)display_config;
  uint8_t *p;

  if(x >= config->width || y >= config->height || x < 0 || y < 0)
    return;

  if ( tga_data == NULL )
    return;

  p = tga_data + (config->width-y-1)*config->height*3 + x*3;
  *p++ = color.b;
  *p++ = color.g;
  *p++ = color.r;
}

const eglib_display_4wire_spi_t eglib_display_4wire_spi_tga = {
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

void eglib_display_4wire_spi_tga_save(eglib_display_4wire_spi_tga_config_t *config, char *path) {
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
    tga_write_word(fp, config->width);		/* width */
    tga_write_word(fp, config->height);		/* height */
    tga_write_byte(fp, 24);		/* color depth */
    tga_write_byte(fp, 0);
    fwrite(tga_data, config->width * config->height * 3, 1, fp);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    fwrite("TRUEVISION-XFILE.", 18, 1, fp);
    fclose(fp);
  }
}