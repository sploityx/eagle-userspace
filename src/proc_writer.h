#ifndef PROC_WRITER_H
#define PROC_WRITER_H

#define PROCFS_NAME "/proc/eagle_residency"

int write_to_proc_file(int *state_residency, int state_count);

#endif
