#include <stdio.h>
#include "proc_writer.h"
#include "state.h"

int write_to_proc_file(State *states, int num_states) {
    FILE *proc_file = fopen(PROCFS_NAME, "w");
    if (proc_file == NULL) {
        perror("Error opening file for writing");
        return 0;
    }

    printf("Writing state information to %s...\n", PROCFS_NAME);
    for (int i = 0; i < num_states; ++i) {
        write_state(proc_file, &states[i]);
    }

    fclose(proc_file);
    return 1;
}
