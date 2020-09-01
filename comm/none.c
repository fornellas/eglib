#include "none.h"

static void power_up(uint16_t clock_ns) {
  (void)clock_ns;
};

static void power_down(void) {
};

const eglib_comm_t eglib_comm_none = {
  .power_up = power_up,
  .power_down = power_down,
};