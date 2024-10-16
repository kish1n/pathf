//
// Created by trpdjke on 10/13/24.
//

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

typedef struct {
    char *island1;
    char *island2;
    int distance;
    int *distance_arr;
    char *way_arr;
} Bridge;

typedef struct {
    int *distances;  // Массив расстояний между островами на пути
    char **visited;  // Массив посещённых островов
    int result;      // Итоговое расстояние
    int visited_count;  // Количество посещённых островов
    int distance_count; // Количество шагов на пути (расстояний)
} Result;

#define BUFFER_SIZE 1024
#define INFINITY INT_MAX

char **mx_strsplit(char const *s, char c);
int mx_atoi(const char* str);
int mx_size(const char *filename);

Bridge *mx_read_bridges(const char *filename, int *bridge_count);
int mx_island_count(const char *filename);
int mx_read_bridge_count(const char *filename);
Result dijkstra(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end);
void print_data_island(Result result);

#endif //PATHFINDER_H
