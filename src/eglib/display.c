#include "display.h"

coordinate_t eglib_GetWidth(eglib_t *eglib) {
	coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

	return width;
}

coordinate_t eglib_GetHeight(eglib_t *eglib) {
	coordinate_t width, heigh;

	eglib->display->get_dimension(eglib, &width, &heigh);

	return heigh;
}

bool eglib_Refresh(eglib_t *eglib) {
	bool is_currently_refreshing;

	is_currently_refreshing = eglib->display->refresh(eglib);

	eglib->display_refreshing = is_currently_refreshing;

	return is_currently_refreshing;
}
