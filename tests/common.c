#define _GNU_SOURCE
#include "common.h"
#include <check.h>
#include <eglib/display/tga.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EGLIB_UPDATE_EXPECTATIONS_MSG "If you trust the code is legit set EGLIB_UPDATE_EXPECTATIONS=true to have the expectation updated.\n"

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

	if(asprintf(&expectation_path, "%s/%s/%s.png", TOP_SRCDIR, reldir, expectation_name) == -1)
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
				"`%s' differs from expectation `%s'.\n" EGLIB_UPDATE_EXPECTATIONS_MSG,
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
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}