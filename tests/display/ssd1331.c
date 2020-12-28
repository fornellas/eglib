#include <eglib/display/ssd1331.h>

const display_t *display_driver = &ssd1331;
void *display_config_ptr = &ssd1331_config_adafruit_65k_colors;
coordinate_t width = 96;
coordinate_t height = 64;
enum pixel_format_t pixel_format = PIXEL_FORMAT_16BIT_RGB;
char driver_name[] = "ssd1331";