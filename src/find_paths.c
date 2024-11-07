#include "../inc/pathfinder.h"

void find_paths(
    int current,
    int end_index,
    Bridge *bridges,
    int bridge_count,
    int island_count,
    int *distances,
    int *temp_path,
    int path_len,
    int *temp_distances,
    int dist_len,
    int total_distance,
    Result *results,
    int *result_count,
    int max_results,
    char *islands[]
) {
    temp_path[path_len++] = current;

    if (current == end_index) {
        Result new_result;
        new_result.length = path_len;
        new_result.total_distance = total_distance;

        new_result.path = (char **)malloc(path_len * 8);
        for (int i = 0; i < path_len; i++) {
            new_result.path[i] = mx_strdup(islands[temp_path[i]]);
        }

        new_result.distances = (int *)malloc(dist_len * 4);
        for (int i = 0; i < dist_len; i++) {
            new_result.distances[i] = temp_distances[i];
        }

        if (*result_count < max_results) {
            results[*result_count] = new_result;
            (*result_count)++;
        } else {
            for (int i = 0; i < path_len; i++) {
                free(new_result.path[i]);
            }
            free(new_result.path);
            free(new_result.distances);
            return;
        }
    } else {
        for (int i = 0; i < bridge_count; i++) {
            int neighbor = -1;
            int edge_weight = bridges[i].distance;
            if (current == get_island_index(bridges[i].island1, islands, island_count)) {
                neighbor = get_island_index(bridges[i].island2, islands, island_count);
            } else if (current == get_island_index(bridges[i].island2, islands, island_count)) {
                neighbor = get_island_index(bridges[i].island1, islands, island_count);
            }
            if (neighbor != -1) {
                if (distances[current] + edge_weight == distances[neighbor]) {
                    temp_distances[dist_len++] = edge_weight;
                    total_distance += edge_weight;

                    find_paths(
                        neighbor,
                        end_index,
                        bridges,
                        bridge_count,
                        island_count,
                        distances,
                        temp_path,
                        path_len,
                        temp_distances,
                        dist_len,
                        total_distance,
                        results,
                        result_count,
                        max_results,
                        islands
                    );

                    dist_len--;
                    total_distance -= edge_weight;
                }
            }
        }
    }
    path_len--;
}

