#include "state.h"
#include "sys_reader.h"
#include "proc_writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#define SYSFS_PATTERN "/sys/devices/system/cpu/cpu0/cpuidle/state*"

int main() {
    State *states;
    glob_t sys_states;
    int num_states;

    if (glob(SYSFS_PATTERN, GLOB_ONLYDIR, NULL, &sys_states) == 0) {
        num_states = sys_states.gl_pathc;
    } else {
        // default to the 9 intel driver states
        num_states = 9;
    }

    states = malloc(num_states * sizeof(State));

    if (states == NULL) {
        perror("Error: Memory Allocation failed.");
        return 1;
    }

    read_sys_states(states, num_states);
    for (int i = 0; i < num_states; ++i) {
        calc_state(&states[i]);
        print_state(&states[i]);
    }

    if (num_states > 0) {
        if (write_to_proc_file(states, num_states) == 0) {
            fprintf(stderr, "Error writing states to file.\n");
            free(states);
            return 1;
        } else {
            printf("Writing states successful.\n");
        }
    } else {
        printf("No cpuidle states found.\n");
    }

    free(states);
    return 0;
}
