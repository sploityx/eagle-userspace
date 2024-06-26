#ifndef SYS_READER_H
#define SYS_READER_H

#include "state.h"

#define MAX_BUF_SIZE 1024
#define SYS_FILE_PREFIX "/sys/devices/system/cpu/cpu0/cpuidle/state"

void read_sys_states(State* states, int num_states);

#endif
