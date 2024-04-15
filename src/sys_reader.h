#ifndef SYS_READER_H
#define SYS_READER_H

#define MAX_STATES 10
#define MAX_BUF_SIZE 1024
#define SYS_FILE_PREFIX "/sys/devices/system/cpu/cpu0/cpuidle/state"

int read_residency_values(int *state_residency);

#endif
