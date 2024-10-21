#include "../inc/pathfinder.h"

void dijkstra(Bridge *bridges, int bridge_count, char *islands[], int island_count, int start_index, int *distances) {
    bool *visited = (bool *)malloc(island_count * 2);

    for (int i = 0; i < island_count; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[start_index] = 0;

    while (true) {
        int min_distance = INT_MAX;
        int current = -1;
        for (int i = 0; i < island_count; i++) {
            if (!visited[i] && distances[i] < min_distance) {
                min_distance = distances[i];
                current = i;
            }
        }
        if (current == -1)
            break;
        visited[current] = true;

        // Update distances to neighbors
        for (int i = 0; i < bridge_count; i++) {
            int neighbor = -1;
            if (current == get_island_index(bridges[i].island1, islands, island_count)) {
                neighbor = get_island_index(bridges[i].island2, islands, island_count);
            } else if (current == get_island_index(bridges[i].island2, islands, island_count)) {
                neighbor = get_island_index(bridges[i].island1, islands, island_count);
            }
            if (neighbor != -1) {
                int new_distance = distances[current] + bridges[i].distance;
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                }
            }
        }
    }
    free(visited);
}
