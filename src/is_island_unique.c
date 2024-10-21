#include "../inc/pathfinder.h"

bool is_island_unique(char *island, char **islands, int count) {
    for (int i = 0; i < count; i++) {
        if (mx_strcmp(island, islands[i]) == 0) {
            return false;
        }
    }
    return true;
}

