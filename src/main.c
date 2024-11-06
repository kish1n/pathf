#include "../inc/pathfinder.h"

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        mx_printstr("usage: ./pathfinder [filename]\n");
        return 1;
    }

    int bridge_count = get_bridge_count(argv[1]); //good
    Bridge *bridges = get_bridges(argv[1], &bridge_count);
    int island_count = get_island_count(argv[1]);
    char *islands[island_count];
    int current_island_count = 0;

    for (int i = 0; i < bridge_count; i++) {
        if (is_island_unique(bridges[i].island1, islands, current_island_count)) {
            islands[current_island_count] = mx_strdup(bridges[i].island1);
            current_island_count++;
            printf("add %s\n", bridges[i].island1);
        }
        if (is_island_unique(bridges[i].island2, islands, current_island_count)) {
            islands[current_island_count] = mx_strdup(bridges[i].island2);
            current_island_count++;
            printf("add %s\n", bridges[i].island2);
        }
    }

    if (current_island_count != island_count) {
        mx_printstr("error: invalid number of islands\n");
        exit(1);
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

                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(res.path[0]);
                mx_printstr(" -> ");
                mx_printstr(res.path[res.length - 1]);
                mx_printstr("\n");
                mx_printstr("Route: ");
                for (int l = 0; l < res.length; l++) {
                    mx_printstr(res.path[l]);
                    if (l < res.length - 1)
                        mx_printstr(" -> ");
                }
                mx_printstr("\nDistance: ");
                int sum = 0;
                for (int l = 0; l < res.length - 1; l++) {
                    char *dist_str = mx_itoa(res.distances[l]);
                    mx_printstr(dist_str);
                    free(dist_str);
                    sum += res.distances[l];
                    if (l < res.length - 2)
                        mx_printstr(" + ");
                }
                if (res.length > 2) {
                    mx_printstr(" = ");
                    char *sum_str = mx_itoa(sum);
                    mx_printstr(sum_str);
                    free(sum_str);
                    mx_printstr("\n");
                } else {
                    mx_printstr("\n");
                }
                mx_printstr("========================================\n");
            }

            free_results(result_array);
        }
    }

    for (int i = 0; i < island_count; i++) {
        free(islands[i]);
    }

    free(bridges);

    return 0;
}
