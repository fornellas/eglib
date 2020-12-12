#include "none.h"
#include <stdio.h>

static void init(eglib_t *eglib) {
	(void)eglib;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("init\n");
}

static void sleep_in(eglib_t *eglib) {
	(void)eglib;

	printf("sleep_in\n");
}

static void sleep_out(eglib_t *eglib) {
	(void)eglib;

	printf("sleep_out\n");
}

static void delay_ns(eglib_t *eglib, uint32_t ns) {
	(void)eglib;

	printf("delay_ns %d\n", ns);
}

static void set_reset(eglib_t *eglib, bool state) {
	(void)eglib;

	printf("set_reset %d\n", state);
}

static bool get_busy(eglib_t *eglib) {
	(void)eglib;

	printf("get_busy\n");
	return false;
}

static void comm_begin(eglib_t *eglib) {
	(void)eglib;

	printf("comm_begin\n");
}

static void send(
	eglib_t *eglib,
	enum hal_dc_t dc,
	uint8_t *bytes,
	uint32_t length
) {
	(void)eglib;

	printf("send\n");
	printf("  dc %d\n", dc);
	printf("  bytes");
	for(uint32_t i=0 ; i < length ; i++)
		printf(" %02x", bytes[i]);

	printf("\n");
}

static void comm_end(eglib_t *eglib) {
	(void)eglib;

	printf("comm_end\n");
}

const hal_t four_wire_spi_stdout = {
	.init = init,
	.sleep_in = sleep_in,
	.sleep_out = sleep_out,
	.delay_ns = delay_ns,
	.set_reset = set_reset,
	.get_busy = get_busy,
	.comm_begin = comm_begin,
	.send = send,
	.comm_end = comm_end,
};