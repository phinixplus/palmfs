#pragma once

#include <fuse3/fuse_opt.h>
#include <stdnoreturn.h>

struct args_results_t {
	struct fuse_args leftovers;
	enum { ERR = 0, MAKE, DRIVER } command;
	char *mewhen;
};

struct args_results_t process_arguments(int argc, char **argv);
noreturn void print_help(const char *exe_name);