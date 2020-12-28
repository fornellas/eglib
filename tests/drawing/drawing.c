#define _GNU_SOURCE
#include <check.h>
#include <eglib.h>
#include <eglib/display.h>
#include <eglib/display/tga.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EGLIB_UPDATE_EXPECTATIONS_MSG "If you trust the code is legit set "\
	"EGLIB_UPDATE_EXPECTATIONS=true to have the expectation updated.\n"

eglib_t eglib;
tga_config_t tga_config = {
	.width = 100,
	.height = 100,
};
char *test_name;

void setup(void);
void teardown(void);
Suite * build_suite(void);
static int run(char *command);

void setup(void) {
	eglib_Init(&eglib, &four_wire_spi_none, NULL, &tga, &tga_config);
}

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

static int run(char *command) {
	int ret;

	ret = system(command);

	switch(ret) {
		case -1:
			fprintf(stderr, "Failed to run `%s': %s.\n", command, strerror(errno));
			exit(EXIT_FAILURE);
			break;
		case 127:
			fprintf(stderr, "Failed to execute shell to run `%s'.\n", command);
			exit(EXIT_FAILURE);
			break;
		default:
			return ret;
	}
}

void teardown(void) {
	char *expectation_dir;
	char *expectation_path;
	char *test_tga_path;
	char *command;

	expectation_dir = getenv("EXPECTATIONS_DIR");
	if(expectation_dir == NULL) {
		fprintf(stdout, "EXPECTATIONS_DIR not set. Please run this via `make check'.\n");
		exit(EXIT_FAILURE);
	}
	if(asprintf(&expectation_path, "%s/%s.png", expectation_dir, test_name) == -1)
		exit(EXIT_FAILURE);
	if(asprintf(&test_tga_path, "%s_test.tga", test_name) == -1)
		exit(EXIT_FAILURE);

	tga_Save(&eglib, test_tga_path);
	tga_Free(&eglib);

	if(getenv("EGLIB_UPDATE_EXPECTATIONS")) {
		fprintf(stderr, "Updating expectation `%s'.\n", expectation_path);
		if(asprintf(&command, "convert -quality 100 -define png:exclude-chunk=date,time %s %s", test_tga_path, expectation_path) == -1)
			exit(EXIT_FAILURE);
		if(run(command) != 0) {
			fprintf(stderr, "Failed to run `%s'.\n", command);
			exit(EXIT_FAILURE);
		}
		free(command);
	}

	if(asprintf(&command, "compare -metric FUZZ %s %s /dev/null", test_tga_path, expectation_path) == -1)
		exit(EXIT_FAILURE);
	switch(run(command)) {
		case 0:
			break;
		case 1:
			fprintf(
				stderr,
				"`%s' differs from expectation `%s'.\n" EGLIB_UPDATE_EXPECTATIONS_MSG,
				test_tga_path, expectation_path
			);
			exit(EXIT_FAILURE);
		default:
			fprintf(stderr, "Failed to run `%s'.\n", command);
			exit(EXIT_FAILURE);
			break;
	}

	free(expectation_path);
	free(test_tga_path);
	free(command);
}

Suite * build_suite(void) {
	Suite *suite;
	TCase *tcase;

	suite = suite_create("drawing");

	tcase = tcase_create("functions");
	tcase_add_checked_fixture(tcase, setup, teardown);

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

	suite_add_tcase(suite, tcase);

	return suite;
}

int main(void) {
	int number_failed;
	Suite *suite;
	SRunner *srunner;

	suite = build_suite();
	srunner = srunner_create(suite);
	// srunner_set_fork_status(srunner, CK_NOFORK);
	srunner_set_tap(srunner, "-");

	srunner_run_all(srunner, CK_SILENT);
	number_failed = srunner_ntests_failed(srunner);
	srunner_free(srunner);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}