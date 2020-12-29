#include <check.h>
#include <eglib.h>

extern eglib_t eglib;
char *suite_name = "drawing";
char *tcase_name = "functions";
extern char *test_name;

void tcase_add_tests(TCase *tcase);

START_TEST(test_eglib_AddUnicodeBlockToFont) {
	test_name = "eglib_AddUnicodeBlockToFont";
	#include "eglib_AddUnicodeBlockToFont.c"
}END_TEST

START_TEST(test_eglib_ClearScreen) {
	test_name = "eglib_ClearScreen";
	#include "eglib_ClearScreen.c"
}END_TEST

START_TEST(test_eglib_DrawArc) {
	test_name = "eglib_DrawArc";
	#include "eglib_DrawArc.c"
}END_TEST

START_TEST(test_eglib_DrawBitmap) {
	test_name = "eglib_DrawBitmap";
	#include "eglib_DrawBitmap.c"
}END_TEST

START_TEST(test_eglib_DrawBox) {
	test_name = "eglib_DrawBox";
	#include "eglib_DrawBox.c"
}END_TEST

START_TEST(test_eglib_DrawCircle) {
	test_name = "eglib_DrawCircle";
	#include "eglib_DrawCircle.c"
}END_TEST

START_TEST(test_eglib_DrawDisc) {
	test_name = "eglib_DrawDisc";
	#include "eglib_DrawDisc.c"
}END_TEST

START_TEST(test_eglib_DrawFilledArc) {
	test_name = "eglib_DrawFilledArc";
	#include "eglib_DrawFilledArc.c"
}END_TEST

START_TEST(test_eglib_DrawFrame) {
	test_name = "eglib_DrawFrame";
	#include "eglib_DrawFrame.c"
}END_TEST

START_TEST(test_eglib_DrawGradientArc) {
	test_name = "eglib_DrawGradientArc";
	#include "eglib_DrawGradientArc.c"
}END_TEST

START_TEST(test_eglib_DrawGradientBox) {
	test_name = "eglib_DrawGradientBox";
	#include "eglib_DrawGradientBox.c"
}END_TEST

START_TEST(test_eglib_DrawGradientDisc) {
	test_name = "eglib_DrawGradientDisc";
	#include "eglib_DrawGradientDisc.c"
}END_TEST

START_TEST(test_eglib_DrawGradientFilledArc) {
	test_name = "eglib_DrawGradientFilledArc";
	#include "eglib_DrawGradientFilledArc.c"
}END_TEST

START_TEST(test_eglib_DrawGradientFrame) {
	test_name = "eglib_DrawGradientFrame";
	#include "eglib_DrawGradientFrame.c"
}END_TEST

START_TEST(test_eglib_DrawGradientHLine) {
	test_name = "eglib_DrawGradientHLine";
	#include "eglib_DrawGradientHLine.c"
}END_TEST

START_TEST(test_eglib_DrawGradientLine) {
	test_name = "eglib_DrawGradientLine";
	#include "eglib_DrawGradientLine.c"
}END_TEST

START_TEST(test_eglib_DrawGradientVLine) {
	test_name = "eglib_DrawGradientVLine";
	#include "eglib_DrawGradientVLine.c"
}END_TEST

START_TEST(test_eglib_DrawHLine) {
	test_name = "eglib_DrawHLine";
	#include "eglib_DrawHLine.c"
}END_TEST

START_TEST(test_eglib_DrawLine) {
	test_name = "eglib_DrawLine";
	#include "eglib_DrawLine.c"
}END_TEST

START_TEST(test_eglib_DrawPixelColor) {
	test_name = "eglib_DrawPixelColor";
	#include "eglib_DrawPixelColor.c"
}END_TEST

START_TEST(test_eglib_DrawPixel) {
	test_name = "eglib_DrawPixel";
	#include "eglib_DrawPixel.c"
}END_TEST

START_TEST(test_eglib_DrawRoundBox) {
	test_name = "eglib_DrawRoundBox";
	#include "eglib_DrawRoundBox.c"
}END_TEST

START_TEST(test_eglib_DrawRoundFrame) {
	test_name = "eglib_DrawRoundFrame";
	#include "eglib_DrawRoundFrame.c"
}END_TEST

START_TEST(test_eglib_DrawText) {
	test_name = "eglib_DrawText";
	#include "eglib_DrawText.c"
}END_TEST

START_TEST(test_eglib_DrawTriangle) {
	test_name = "eglib_DrawTriangle";
	#include "eglib_DrawTriangle.c"
}END_TEST

START_TEST(test_eglib_DrawVLine) {
	test_name = "eglib_DrawVLine";
	#include "eglib_DrawVLine.c"
}END_TEST

START_TEST(test_eglib_DrawWChar) {
	test_name = "eglib_DrawWChar";
	#include "eglib_DrawWChar.c"
}END_TEST

void tcase_add_tests(TCase *tcase) {
	tcase_add_test(tcase, test_eglib_AddUnicodeBlockToFont);
	tcase_add_test(tcase, test_eglib_ClearScreen);
	tcase_add_test(tcase, test_eglib_DrawArc);
	tcase_add_test(tcase, test_eglib_DrawBitmap);
	tcase_add_test(tcase, test_eglib_DrawBox);
	tcase_add_test(tcase, test_eglib_DrawCircle);
	tcase_add_test(tcase, test_eglib_DrawDisc);
	tcase_add_test(tcase, test_eglib_DrawFilledArc);
	tcase_add_test(tcase, test_eglib_DrawFrame);
	tcase_add_test(tcase, test_eglib_DrawGradientArc);
	tcase_add_test(tcase, test_eglib_DrawGradientBox);
	tcase_add_test(tcase, test_eglib_DrawGradientDisc);
	tcase_add_test(tcase, test_eglib_DrawGradientFilledArc);
	tcase_add_test(tcase, test_eglib_DrawGradientFrame);
	tcase_add_test(tcase, test_eglib_DrawGradientHLine);
	tcase_add_test(tcase, test_eglib_DrawGradientLine);
	tcase_add_test(tcase, test_eglib_DrawGradientVLine);
	tcase_add_test(tcase, test_eglib_DrawHLine);
	tcase_add_test(tcase, test_eglib_DrawLine);
	tcase_add_test(tcase, test_eglib_DrawPixelColor);
	tcase_add_test(tcase, test_eglib_DrawPixel);
	tcase_add_test(tcase, test_eglib_DrawRoundBox);
	tcase_add_test(tcase, test_eglib_DrawRoundFrame);
	tcase_add_test(tcase, test_eglib_DrawText);
	tcase_add_test(tcase, test_eglib_DrawTriangle);
	tcase_add_test(tcase, test_eglib_DrawVLine);
	tcase_add_test(tcase, test_eglib_DrawWChar);
}