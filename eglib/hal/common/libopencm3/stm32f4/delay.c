#define CLOCKS_PER_DELAY_LOOP 3

inline static void _delay_ns(volatile uint32_t ns) {
	volatile uint32_t loop_count;

	loop_count = ns * (float)rcc_ahb_frequency / (CLOCKS_PER_DELAY_LOOP * 1000000000U);

	__asm__ volatile(
		" mov r0, %[loop_count] \n\t"
		"1: subs r0, #1 \n\t"
		" bhi 1b \n\t"
		:
		: [loop_count] "r" (loop_count)
		: "r0"
	);
}