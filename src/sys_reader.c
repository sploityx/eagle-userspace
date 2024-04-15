#include <stdio.h>
#include "sys_reader.h"

int read_residency_values(int *state_residency) {
    char sys_filename[MAX_BUF_SIZE];
    int state_count = 0;

    printf("Reading residency values from sys files...\n");
    for (int i = 0; i < MAX_STATES; ++i) {
        snprintf(sys_filename, sizeof(sys_filename), "%s%d/residency", SYS_FILE_PREFIX, i);
        FILE *sys_file = fopen(sys_filename, "r");
        if (sys_file != NULL) {
            fscanf(sys_file, "%d", &state_residency[i]);
            fclose(sys_file);
            state_count++;
        } else {
            break;
        }
    }

    return state_count;
}
