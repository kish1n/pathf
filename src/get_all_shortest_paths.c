#include "../inc/pathfinder.h"

ResultArray get_all_shortest_paths(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end) {
    int start_index = get_island_index(start, islands, island_count);
    int end_index = get_island_index(end, islands, island_count);

    int *distances = (int *)malloc(island_count * sizeof(int));
    dijkstra(bridges, bridge_count, islands, island_count, start_index, distances);

    ResultArray result_array;
    result_array.results = (Result *)malloc(MAX_RESULTS * sizeof(Result));
    result_array.count = 0;

    int *temp_path = (int *)malloc(island_count * sizeof(int));
    int *temp_distances = (int *)malloc(island_count * sizeof(int));

    find_paths(
        start_index,
        end_index,
        bridges,
        bridge_count,
        island_count,
        distances,
        temp_path,
        0,
        temp_distances,
        0,
        0,
        result_array.results,
        &result_array.count,
        MAX_RESULTS,
        islands
    );

    free(distances);
    free(temp_path);
    free(temp_distances);

    return result_array;
}
