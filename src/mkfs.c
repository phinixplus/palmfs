#include "mkfs.h"

#include <stdio.h>
#include <stdlib.h>

noreturn void do_mkfs(struct args_results_t *results) {
	(void) results;
	puts("MKFS");
	exit(EXIT_SUCCESS);
}