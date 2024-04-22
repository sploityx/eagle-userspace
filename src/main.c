#include "state.h"
#include "sys_reader.h"
#include "proc_writer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    State *states;

    // TODO: write function to check amount of states in sysfs
    // this is necessary, if ACPI is used or intel drivers would change
    int num_states = 9;
    states = malloc(num_states * sizeof(State));

    if (states == NULL) {
        fprintf(stderr, "Memory Allocation failed\n");
        return 1;
    }

    read_sys_states(states, num_states);
    for (int i = 0; i < num_states; ++i) {
        calc_state(&states[i]);
        print_state(&states[i]);
    }

    if (num_states > 0) {
        if (write_to_proc_file(states, num_states) == 0) {
            fprintf(stderr, "Something went wrong then writting.\n");
            free(states);
            return 1;
        } else {
            printf("Write successful.\n");
        }
    } else {
        printf("No cpuidle states found.\n");
    }

    free(states);
    return 0;
}
