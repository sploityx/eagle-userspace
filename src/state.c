#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

State* create_state(int number, const char* name, int residency,
                    int latency, int below, int above) {
    State* state = (State*)malloc(sizeof(State));
    if (state == NULL) {
        perror("Error: Memory Allocation failed.");
        exit(EXIT_FAILURE);
    }
    state->number = number;
    strlcpy(state->name, name, sizeof(state->name));
    state->residency = residency;
    state->latency = latency;
    state->below = below;
    state->above = above;
    return state;
}

void destroy_state(State* state) {
    free(state);
}

void print_state(State* state) {
    printf("State\nNumber: %d\nName: %s\nResidency: %d\nLatency: %d\n"
           "Below: %d\nAbove: %d\n\n", state->number, state->name,
           state->residency, state->latency, state->below, state->above);
}

void write_state(FILE *file, State* state) {
    fprintf(file, "State\nNumber: %d\nName: %s\nResidency: %d\nLatency: %d\n"
                        "Below: %d\nAbove: %d\n\n",
                        state->number, state->name, state->residency,
                        state->latency, state->below, state->above);
}
