#include "none.h"

static void power_up(void *comm_config, uint16_t clock_ns) {

}

static void power_down(void *comm_config) {

}

static void delay(void *comm_config, uint16_t microseconds) {

}

static void set_reset(void *comm_config, uint8_t state) {

}

static void set_cd(void *comm_config, uint8_t state) {

}

static void set_cs(void *comm_config, uint8_t state) {

}

static void send_byte(void *comm_config, uint8_t state) {

}


const eglib_comm_t eglib_comm_none = {
  .power_up = power_up,
  .power_down = power_down,
  .delay = delay,
  .set_reset = set_reset,
  .set_cd = set_cd,
  .set_cs = set_cs,
  .send_byte = send_byte,
};