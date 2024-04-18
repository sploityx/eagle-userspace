#ifndef PROC_WRITER_H
#define PROC_WRITER_H

#include "state.h"

#define PROCFS_NAME "/proc/eagle_residency"

int write_to_proc_file(State *states, int num_states);

#endif
