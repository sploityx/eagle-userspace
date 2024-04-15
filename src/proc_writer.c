#include <stdio.h>
#include "proc_writer.h"

int write_to_proc_file(int *state_residency, int state_count) {
    FILE *proc_file = fopen(PROCFS_NAME, "w");
    if (proc_file == NULL) {
        perror("Error opening file for writing");
        return 0;
    }

    printf("Writing residency values to %s...\n", PROCFS_NAME);
    for (int i = 0; i < state_count; ++i) {
        fprintf(proc_file, "cpu0 state%d residency: %d\n", i, state_residency[i]);
    }

    fclose(proc_file);
    return 1;
}
