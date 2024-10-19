#include "../inc/pathfinder.h"

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        mx_printstr("Usage: ./pathfinder [filename]\n");
        return 1;
    }

    int bridge_count = get_bridge_count(argv[1]);
    Bridge *bridges = get_bridges(argv[1], &bridge_count);
    int island_count = get_island_count(argv[1]);

    char *islands[island_count];
    int current_island_count = 0;

    for (int i = 0; i < bridge_count; i++) {
        if (is_island_unique(bridges[i].island1, islands, current_island_count)) {
            islands[current_island_count] = mx_strdup(bridges[i].island1);
            current_island_count++;
        }
        if (is_island_unique(bridges[i].island2, islands, current_island_count)) {
            islands[current_island_count] = mx_strdup(bridges[i].island2);
            current_island_count++;
        }
    }

    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            if (mx_strcmp(islands[i], islands[j]) > 0) {
                char *temp = islands[i];
                islands[i] = islands[j];
                islands[j] = temp;
            }
        }
    }

    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            ResultArray result_array = get_all_shortest_paths(bridges, bridge_count, islands, island_count, islands[i], islands[j]);
            for (int k = 0; k < result_array.count; k++) {
                Result res = result_array.results[k];

                printf("=======================================\n");
                printf("Path: %s -> %s\n", res.path[0], res.path[res.length - 1]);
                printf("Route: ");
                for (int l = 0; l < res.length; l++) {
                    printf("%s", res.path[l]);
                    if (l < res.length - 1)
                        printf(" -> ");
                }
                printf("\nDistance: ");
                int sum = 0;
                for (int l = 0; l < res.length - 1; l++) {
                    printf("%d", res.distances[l]);
                    sum += res.distances[l];
                    if (l < res.length - 2)
                        printf(" + ");
                }
                if (res.length > 2) {
                    printf(" = %d\n", sum);
                } else if (res.length == 2) {
                    printf(" = %d\n", sum);
                } else {
                    printf("%d\n", sum);
                }
                printf("=======================================\n");
            }

            free_results(result_array);
        }
    }

    for (int i = 0; i < island_count; i++) {
        free(islands[i]);
    }

    for (int i = 0; i < bridge_count; i++) {
        free(bridges[i].island1);
        free(bridges[i].island2);
    }
    free(bridges);

    return 0;
}
