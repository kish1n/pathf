#include "../inc/pathfinder.h"

int get_island_index(char *island, char *islands[], int island_count) {
    for (int i = 0; i < island_count; i++) {
        if (mx_strcmp(islands[i], island) == 0) {
            return i;
        }
    }
    return -1;  // Island not found
}
