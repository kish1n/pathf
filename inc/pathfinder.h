#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include <limits.h>

typedef struct {
    char *island1;
    char *island2;
    int distance;
} Bridge;

typedef struct {
    char **path;
    int *distances;
    int total_distance;
    int length;
} Result;

typedef struct {
    Result *results;
    int count;
} ResultArray;


#define BUFFER_SIZE 1024
#define MAX_RESULTS 1000

Bridge *get_bridges(const char *filename, int *bridge_count);
ResultArray get_all_shortest_paths(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end);

void dijkstra(Bridge *bridges, int bridge_count, char *islands[], int island_count, int start_index, int *distances);
bool is_island_unique(char *island, char **islands, int count);

void free_results(ResultArray result_array);
int get_bridge_count(const char *filename);
int get_island_count(const char *filename);
int get_island_index(char *island, char *islands[], int island_count);

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
);
#endif //PATHFINDER_H
