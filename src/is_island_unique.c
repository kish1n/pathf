#include "../inc/pathfinder.h"

bool is_island_unique(const char *island, char *island_array[], int count) {
    for (int i = 0; i < count; i++) {
        if (mx_strcmp(island_array[i], island) == 0) {
            return false;
        }
    }
    return true;
}
