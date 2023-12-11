#include "driver.h"

#include <stdlib.h>

static struct fuse_operations operations = {};

noreturn void do_driver(struct args_results_t *results) {
	results->leftovers.argv[0][0] = '\0';
	int fuse_ret = fuse_main(
		results->leftovers.argc,
		results->leftovers.argv,
		&operations,
		NULL
	);
	if(fuse_ret == 0) exit(EXIT_SUCCESS);
	else exit(EXIT_FAILURE);
}