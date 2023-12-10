#pragma once

#include <fuse3/fuse_opt.h>

struct args_results_t {
	struct fuse_args leftovers;
	char *mewhen;
};

struct args_results_t process_arguments(int argc, char **argv);