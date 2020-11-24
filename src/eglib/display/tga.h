#ifndef EGLIB_DISPLAY_TGA_H
#define EGLIB_DISPLAY_TGA_H

#include "../display.h"

typedef struct {
	coordinate_t width;
	coordinate_t height;
} tga_config_t;

extern const display_t tga;

void tga_Save(tga_config_t *config, char *path);

#endif