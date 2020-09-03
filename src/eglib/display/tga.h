#ifndef EGLIB_DISPLAY_TGA_H
#define EGLIB_DISPLAY_TGA_H

#include "../../eglib.h"

typedef struct {
	eglib_coordinate_t width;
	eglib_coordinate_t height;
} eglib_display_tga_config_t;

const eglib_display_t eglib_display_tga;

void eglib_display_tga_save(eglib_display_tga_config_t *config, char *path);

#endif