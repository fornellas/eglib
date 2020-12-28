#include <eglib/display/sh1106.h>

const display_t *display_driver = &sh1106_vdd1_2_4_v;
void *display_config_ptr = &sh1106_config_sparkfun_micro_oled;
coordinate_t width = 64;
coordinate_t height = 48;
enum pixel_format_t pixel_format = PIXEL_FORMAT_1BIT_BW_PAGED;
char driver_name[] = "sh1106";