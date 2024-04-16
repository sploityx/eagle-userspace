#include "sys_reader.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STATE_DIR "/sys/devices/system/cpu/cpu0/cpuidle"

int read_attribute(const char *attr_path, char *value, size_t value_size) {
    FILE *file = fopen(attr_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    if (fgets(value, value_size, file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return -1;
    }

    // Remove newline character if present
    size_t len = strlen(value);
    if (len > 0 && value[len - 1] == '\n') {
        value[len - 1] = '\0';
    }

    fclose(file);
    return 0;
}

void read_sys_states(State* states[MAX_STATES]) {
    char state_dir[50];
    for (int i = 0; i < MAX_STATES; ++i) {
        snprintf(state_dir, sizeof(state_dir), STATE_DIR "/state%d/", i);

        // Open the state directory
        DIR* dir = opendir(state_dir);
        if (dir == NULL) {
            break;
        }

        // Read each attribute
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            char attr_path[256];
            snprintf(attr_path, sizeof(attr_path), "%s", state_dir);

            size_t attr_path_len = strlen(attr_path);
            size_t remaining_space = sizeof(attr_path) - attr_path_len;
            strncat(attr_path, entry->d_name, remaining_space);

            states[i]->number = i;
            if (strcmp(entry->d_name, "name") == 0) {
                read_attribute(attr_path, states[i]->name, sizeof(states[i]->name));
            } else if (strcmp(entry->d_name, "below") == 0) {
                char value[100];
                read_attribute(attr_path, value, sizeof(value));
                states[i]->below = atoi(value);
            } else if (strcmp(entry->d_name, "above") == 0) {
                char value[100];
                read_attribute(attr_path, value, sizeof(value));
                states[i]->above = atoi(value);
            } else if (strcmp(entry->d_name, "latency") == 0) {
                char value[100];
                read_attribute(attr_path, value, sizeof(value));
                states[i]->latency = atoi(value);
            } else if (strcmp(entry->d_name, "residency") == 0) {
                char value[100];
                read_attribute(attr_path, value, sizeof(value));
                states[i]->residency = atoi(value);
            }


        }
        closedir(dir);
    }
}
