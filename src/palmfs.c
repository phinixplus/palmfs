#define _GNU_SOURCE

#include <stdio.h>

#include "args.h"
#include "mkfs.h"
#include "driver.h"

/* noreturn */ int main(int argc, char **argv) {
	struct args_results_t results = process_arguments(argc, argv);
	switch(results.command) {
		case ERR: print_help(argv[0]);
		case MAKE: do_mkfs(&results);
		case DRIVER: do_driver(&results);
	}
}
