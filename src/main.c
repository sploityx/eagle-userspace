#include <stdio.h>
#include "sys_reader.h"
#include "proc_writer.h"

int main() {
    int state_residency[MAX_STATES];
    int state_count = read_residency_values(state_residency);

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

    return 0;
}
