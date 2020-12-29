#define _GNU_SOURCE
#include <check.h>
#include <eglib.h>
#include <eglib/display.h>
#include <eglib/display/frame_buffer.h>
#include <eglib/display/tga.h>
#include <eglib/hal/four_wire_spi/none.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EGLIB_UPDATE_EXPECTATIONS_MSG "If you trust the code is legit set "\
	"EGLIB_UPDATE_EXPECTATIONS=true to have the expectation updated.\n"

eglib_t eglib;
eglib_t eglib_tga;
eglib_t *eglib_export;
tga_config_t tga_config = {
	.width = 100,
	.height = 100,
};
extern bool frame_buffer;
	frame_buffer_config_t frame_buffer_config;
extern char *suite_name;
extern char *tcase_name;
char *test_name = NULL;

void setup(void);
void teardown(void);
Suite * build_suite(void);
static int run(char *command);
void tcase_add_tests(TCase *tcase);

void setup(void) {
	if(frame_buffer) {
		eglib_export = eglib_Init_FrameBuffer(
			&eglib, &frame_buffer_config,
			&four_wire_spi_none, NULL,
			&tga, &tga_config
		);
	} else {
		eglib_Init(&eglib, &four_wire_spi_none, NULL, &tga, &tga_config);
		eglib_export = &eglib;
	}
}

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
	ck_assert_ptr_ne(test_name, NULL);
	if(asprintf(&expectation_path, "%s/%s.png", expectation_dir, test_name) == -1)
		exit(EXIT_FAILURE);
	if(asprintf(&test_tga_path, "%s_test.tga", test_name) == -1)
		exit(EXIT_FAILURE);

	tga_Save(eglib_export, test_tga_path);
	tga_Free(eglib_export);

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

	suite = suite_create(suite_name);

	tcase = tcase_create(tcase_name);
	tcase_add_checked_fixture(tcase, setup, teardown);

	tcase_add_tests(tcase);

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