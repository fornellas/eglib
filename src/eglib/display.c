#include "display.h"

coordinate_t display_GetWidth(eglib_t *eglib) {
	coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

	return width;
}

coordinate_t display_GetHeight(eglib_t *eglib) {
	coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

	return heigh;
}