#define _GNU_SOURCE
#include "common.h"
#include <check.h>
#include <eglib/display/tga.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int updated_expectations = 0;

Suite * build_suite(void);
static int run(char *command);

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
			if(WIFEXITED(ret))
				return WEXITSTATUS(ret);
			if(WIFSIGNALED(ret)) {
				fprintf(stderr, "Terminated by signal %d `%s'.\n", WTERMSIG(ret), command);
				exit(EXIT_FAILURE);
			}
			fprintf(stderr, "Unknown failure `%s'.\n", command);
			exit(EXIT_FAILURE);
	}
}

void compare_expectation(char *expectation_name, eglib_t *eglib) {
	char *expectation_path;
	char *test_tga_path;
	char *command;
	int ret;

	if(asprintf(&expectation_path, "%s/%s/%s.png", TOP_BUILDDIR, reldir, expectation_name) == -1)
		exit(EXIT_FAILURE);

	if(asprintf(&test_tga_path, "%s/%s/%s_test.tga", TOP_BUILDDIR, reldir, expectation_name) == -1)
		exit(EXIT_FAILURE);

	tga_Save(eglib, test_tga_path);
	tga_Free(eglib);

	if(getenv("EGLIB_UPDATE_EXPECTATIONS")) {
		fprintf(stderr, "Updating expectation `%s'.\n", expectation_path);
		if(asprintf(&command, "convert -quality 100 -define png:exclude-chunk=date,time %s %s", test_tga_path, expectation_path) == -1)
			exit(EXIT_FAILURE);
		if(run(command) != 0) {
			fprintf(stderr, "Failed to run `%s'.\n", command);
			exit(EXIT_FAILURE);
		}
		free(command);
		updated_expectations++;
	}

	if(access(expectation_path, F_OK)) {
		fprintf(
			stderr,
			"ERROR: An expectation image at:\n"
			"%s\n"
			"isn't available to compare it with the test output at:\n"
			"%s\n"
			"\n"
			"Please open the test output image and confirm it is as expected. "
			"If not, fix the code until it is.\n"
			"\n"
			"Once test output image is as expected, you can re-run the tests once with this set\n"
			"EGLIB_UPDATE_EXPECTATIONS=true\n"
			"so that the test test expectation is updated with the current test output.\n", 
			expectation_path, test_tga_path
		);
		exit(EXIT_FAILURE);
	}

	if(asprintf(&command, "compare -quiet -metric FUZZ %s %s /dev/null", test_tga_path, expectation_path) == -1)
		exit(EXIT_FAILURE);
	ret = run(command);
	switch(ret) {
		case 0:
			break;
		case 1:
			fprintf(
				stderr,
				"Test output image at:\n"
				"%s\n"
				"does not match test expectation at:\n"
				"%s\n"
				"\n"
				"If the test output is legit but the expectation isn't,"
				"re-run the tests once with this set:\n"
				"EGLIB_UPDATE_EXPECTATIONS=true\n"
				"so that the test test expectation is updated with the current test output.\n"
				"\n"
				"If the expectation is legit, but the test output isn't,"
				"fix the code and make sure the test output matches the expectation.",
				test_tga_path, expectation_path
			);
			exit(EXIT_FAILURE);
		default:
			fprintf(stderr, "Failure comparing expectation `%s' (%d).\n", command, ret);
			exit(EXIT_FAILURE);
			break;
	}

	free(expectation_path);
	free(test_tga_path);
	free(command);
}

int main(void) {
	int number_failed;
	Suite *suite;
	SRunner *srunner;

	suite = build_suite();
	srunner = srunner_create(suite);
	srunner_set_fork_status(srunner, CK_NOFORK);
	srunner_set_tap(srunner, "-");

	srunner_run_all(srunner, CK_SILENT);
	number_failed = srunner_ntests_failed(srunner);
	srunner_free(srunner);

	if(getenv("EGLIB_UPDATE_EXPECTATIONS") && updated_expectations) {
		char *command;
		char *expectation_pngs;
		int ret;

		if(asprintf(&expectation_pngs, "%s/%s/expectation_pngs.tar", TOP_SRCDIR, reldir) == -1)
			exit(EXIT_FAILURE);
		if(asprintf(&command, "cd %s && tar --sort=name --owner=root:0 --group=root:0 --mtime='UTC 2019-01-01' -cf %s *.png", reldir, expectation_pngs) == -1)
			exit(EXIT_FAILURE);

		fprintf(stderr, "Updating %s.\n", expectation_pngs);
		free(expectation_pngs);
		ret = run(command);
		if(ret) {
			fprintf(stderr, "%s: returned %d.\n", command, ret);
			exit(EXIT_FAILURE);
		}
		free(command);
	}

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}