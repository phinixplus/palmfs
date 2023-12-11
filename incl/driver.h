#pragma once

#define FUSE_USE_VERSION 31
#include <fuse3/fuse.h>
#include <stdnoreturn.h>

#include "args.h"

noreturn void do_driver(struct args_results_t *results);