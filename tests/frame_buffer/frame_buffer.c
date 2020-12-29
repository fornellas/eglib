#include <check.h>
#include <eglib.h>
#include <eglib/display.h>
#include <eglib/display/frame_buffer.h>

extern eglib_t eglib;
char *suite_name = "display";
char *tcase_name = "frame_buffer";
extern char *test_name;
bool frame_buffer = true;

void tcase_add_tests(TCase *tcase);

START_TEST(test_eglib_FrameBuffer_Send) {
	coordinate_t width, height;

	test_name = "eglib_FrameBuffer_Send";

	width = eglib_GetWidth(&eglib);
	height = eglib_GetHeight(&eglib);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 0);
	for(coordinate_t v=0 ; (v < width) && (v < height) ; v++ )
		eglib_DrawPixel(&eglib, v, v);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, width - 1, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib, 0, height - 1, 0, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib, 0, 0, width - 1, height - 1);

	eglib_FrameBuffer_Send(&eglib);
}END_TEST

START_TEST(test_eglib_FrameBuffer_SendPartial) {
	coordinate_t width, height;

	test_name = "eglib_FrameBuffer_SendPartial";

	width = eglib_GetWidth(&eglib);
	height = eglib_GetHeight(&eglib);
	eglib_SetIndexColor(&eglib, 0, 0, 0, 0);
	for(coordinate_t v=0 ; (v < width) && (v < height) ; v++ )
		eglib_DrawPixel(&eglib, v, v);

	eglib_SetIndexColor(&eglib, 0, 255, 0, 0);
	eglib_DrawLine(&eglib, 0, 0, width - 1, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 255, 0);
	eglib_DrawLine(&eglib, 0, height - 1, 0, 0);

	eglib_SetIndexColor(&eglib, 0, 0, 0, 255);
	eglib_DrawLine(&eglib, 0, 0, width - 1, height - 1);

	eglib_FrameBuffer_SendPartial(&eglib, 0, 0, 50, 50);
}END_TEST

START_TEST(test_eglib_FrameBuffer_SendUpdated) {
	test_name = "eglib_FrameBuffer_SendUpdated";

	eglib_SetIndexColor(&eglib, 0, 255, 255, 255);
	eglib_DrawBox(&eglib, 25, 25, 50, 50);

	eglib_FrameBuffer_SendUpdated(&eglib);
}END_TEST

void tcase_add_tests(TCase *tcase) {
	tcase_add_test(tcase, test_eglib_FrameBuffer_Send);
	tcase_add_test(tcase, test_eglib_FrameBuffer_SendPartial);
	tcase_add_test(tcase, test_eglib_FrameBuffer_SendUpdated);
}