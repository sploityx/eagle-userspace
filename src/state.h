#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>

#define MAX_NAME_LENGTH 20

typedef struct State {
    int number;
    char name[MAX_NAME_LENGTH];
    int residency;
    int latency;
    int usage;
    int below;
    int above;
} State;

State* create_state(int number, const char* name, int residency,
                    int latency, int usage, int below, int above);
void destroy_state(State* state);
void print_state(State* state);
void write_state(FILE *file, State* state);

#endif // STATE_H_
