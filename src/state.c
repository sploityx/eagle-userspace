#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

State* create_state(int number, const char* name, int residency,
                    int latency, int usage, int below, int above) {
    State* state = (State*)malloc(sizeof(State));
    if (state == NULL) {
        perror("Error: Memory Allocation failed.");
        exit(EXIT_FAILURE);
    }
    state->number = number;
    strlcpy(state->name, name, sizeof(state->name));
    state->residency = residency;
    state->latency = latency;
    state->usage = usage;
    state->below = below;
    state->above = above;
    state->correction = 0;
    return state;
}

void destroy_state(State* state) {
    free(state);
}

void print_state(State* state) {
    if (state == NULL) {
        fprintf(stderr, "Error: State pointer is NULL.\n");
        return;
    }

    printf("State\nNumber: %d\nName: %s\nResidency: %d\nLatency: %d\n"
           "Usage: %d\nBelow: %d\nAbove: %d\nCorrection: %d\n\n", state->number,
           state->name, state->residency, state->latency, state->usage,
           state->below, state->above, state->correction);
}

void write_state(FILE *file, State* state) {
    if (file == NULL) {
        fprintf(stderr, "Error: File pointer is NULL.\n");
        return;
    }
    if (state == NULL) {
        fprintf(stderr, "Error: State pointer is NULL.\n");
        return;
    }

    fprintf(file, "State\nNumber: %d\nName: %s\nResidency: %d\nLatency: %d\n"
                    "Usage: %d\nBelow: %d\nAbove: %d\nCorrection: %d\n\n",
                    state->number, state->name, state->residency,
                    state->latency, state->usage, state->below, state->above,
                    state->correction);
}

void calc_state(State* state) {
    if (state == NULL) {
        fprintf(stderr, "Error: State pointer is NULL.\n");
        return;
    }

    if (state->usage == 0) {
        state->correction = state->residency;
    } else {
        float above_perc = ((float)state->above * 100.0) / state->usage;
        state->correction = state->residency + ((100.0 + above_perc *
                                                state->residency) / 100.0);
    }
}
