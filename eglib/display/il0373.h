#ifndef EGLIB_DISPLAY_IL0373_H
#define EGLIB_DISPLAY_IL0373_H

#include "../../eglib.h"
#include <stdbool.h>

typedef struct {
	coordinate_t width;
	coordinate_t height;

	// Internal refreshing state
	bool refreshing : 1;
} il0373_config_t;

// Heltec 2.13 inch E-ink Black/White/Red
// https://heltec.org/project/213-e-ink/
extern const il0373_config_t il0373_config_heltec_213_bwr;

//
// display_t
//

extern const display_t il0373;

//
// Custom Functions
//

#endif