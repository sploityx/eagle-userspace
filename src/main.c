#include "state.h"
#include "sys_reader.h"
#include "proc_writer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int state_residency[MAX_STATES];
    int state_count = 0;
    State *states[MAX_STATES];
    for (int i = 0; i < MAX_STATES; ++i) {
        states[i] = malloc(sizeof(State));
    }

    read_sys_states(states);
    for (int i = 0; i < MAX_STATES; ++i) {
        print_state(states[i]);
    }


    if (state_count > 0) {
        if (write_to_proc_file(state_residency, state_count) == 0) {
            fprintf(stderr, "Something went wrong then writting.\n");
            return 1;
        } else {
            printf("Write successful.\n");
        }
    } else {
        printf("No cpuidle states found.\n");
    }

    for (int i = 0; i < MAX_STATES; ++i) {
        destroy_state(states[i]);
    }

    return 0;
}
