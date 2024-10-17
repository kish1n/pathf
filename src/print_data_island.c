#include "../inc/pathfinder.h"

void print_data_island(Result island) {
    if (island.result != -1) {
        printf("========================================\n");
        printf("Path: %s -> %s\n", island.visited[island.visited_count - 1], island.visited[0]);
        printf("Route: ");
        for (int i = 0; i < island.visited_count; i++) {  // Проходим по пути в прямом порядке
            printf("%s", island.visited[i]);
            if (i < island.visited_count - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        printf("Distance: ");
        if (island.distance_count == 1) {
            printf("%d\n", island.distances[0]);
        } else {
            int total_distance = 0;
            for (int i = 0; i < island.distance_count; i++) {  // Считаем расстояния в прямом порядке
                printf("%d", island.distances[i]);
                total_distance += island.distances[i];
                if (i < island.distance_count - 1) {
                    printf(" + ");
                }
            }
            printf(" = %d\n", total_distance);
        }

        printf("========================================\n");
    } else {
        printf("No path found.\n");
    }

    // Освобождение памяти
    for (int i = 0; i < island.visited_count; i++) {
        free(island.visited[i]);
    }
    free(island.visited);
    free(island.distances);
}
