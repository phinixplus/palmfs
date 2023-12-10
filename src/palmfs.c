#define _GNU_SOURCE
#define FUSE_USE_VERSION 31

#include <fuse3/fuse.h>
#include <stdio.h>

#include "args.h"

int main(int argc, char **argv) {
	struct args_results_t results = process_arguments(argc, argv);
	if(results.mewhen != NULL) puts(results.mewhen);
	return fuse_main(results.leftovers.argc, results.leftovers.argv, NULL, NULL);
}
