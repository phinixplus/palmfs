#include "args.h"

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#undef FUSE_OPT_KEY
#define FUSE_OPT_KEY(t, e, k) {t, offsetof(struct args_results_t, e), k}
#define FUSE_OPT_FMT(t, e) {t, offsetof(struct args_results_t, e), 0}
#define FUSE_OPT_CALL(t, k) {t, -1, k}

static int opts_callback(
	void *data, const char *arg,
	int key, struct fuse_args *outargs
) {
	(void) key;
	struct args_results_t *results = (struct args_results_t *) data;
	if(outargs->argc == 1) {
		if(strcmp(arg, "make") == 0) results->command = MAKE;
		else if(strcmp(arg, "driver") == 0) results->command = DRIVER;
		else return 1;
		return 0; 
	}
	return 1;
}

static void atexit_free(struct args_results_t *results) {
	static struct args_results_t saved;
	if(results != NULL) {
		saved = *results;
		return;
	}
	fuse_opt_free_args(&saved.leftovers);
	if(saved.mewhen != NULL) free(saved.mewhen);
}

static void atexit_callback(void) { atexit_free(NULL); }

noreturn void print_help(const char *exe_name) {
	fprintf(stderr,
		"Useage:\n"
		"\t%s make [options] <normal_file> <sectors>\n"
		"\t%s make [options] <device_file>\n"
		"\t%s driver [options] <device_file>\n",
	exe_name, exe_name, exe_name);
	exit(EXIT_FAILURE);
}

static struct fuse_opt opts_schema[] = {
	FUSE_OPT_FMT("--mewhen=%s", mewhen),
	FUSE_OPT_END
};

struct args_results_t process_arguments(int argc, char **argv) {
	if(argc == 1) print_help(argv[0]);

	struct args_results_t results;
	memset(&results, 0, sizeof(struct args_results_t));
	results.leftovers = (struct fuse_args) FUSE_ARGS_INIT(argc, argv);
	fuse_opt_parse(&results.leftovers, &results, opts_schema, opts_callback);

	atexit_free(&results);
	atexit(atexit_callback);
	return results;
}

