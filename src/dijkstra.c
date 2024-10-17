#include "../inc/pathfinder.h"

int get_island_index(char *island, char *islands[], int island_count) {
    for (int i = 0; i < island_count; i++) {
        if (mx_strcmp(islands[i], island) == 0) {
            return i;
        }
    }
    return -1;  // Остров не найден
}

void dijkstra(Bridge *bridges, int bridge_count, char *islands[], int island_count, int start_index, int *distances) {
    bool *visited = (bool *)malloc(island_count * sizeof(bool));

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

        // Обновляем расстояния до соседей
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

void find_paths(int current, int end_index, Bridge *bridges, int bridge_count, int island_count, int *distances, int *temp_path, int path_len, AllPaths *all_paths, char *islands[]) {
    temp_path[path_len++] = current;
    if (current == end_index) {
        // Копируем путь в all_paths
        Path new_path;
        new_path.length = path_len;
        new_path.path = (int *)malloc(path_len * sizeof(int));
        for (int i = 0; i < path_len; i++) {
            new_path.path[i] = temp_path[i];
        }
        if (all_paths->count < MAX_PATHS) {
            all_paths->paths[all_paths->count++] = new_path;
        } else {
            free(new_path.path);
            return;
        }
    } else {
        // Идем по всем соседям
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
                    find_paths(neighbor, end_index, bridges, bridge_count, island_count, distances, temp_path, path_len, all_paths, islands);
                }
            }
        }
    }
    path_len--;
}

AllPaths get_all_shortest_paths(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end) {
    int start_index = get_island_index(start, islands, island_count);
    int end_index = get_island_index(end, islands, island_count);

    AllPaths all_paths;
    all_paths.count = 0;
    all_paths.paths = (Path *)malloc(MAX_PATHS * sizeof(Path));

    int *distances = (int *)malloc(island_count * sizeof(int));
    dijkstra(bridges, bridge_count, islands, island_count, start_index, distances);

    int *temp_path = (int *)malloc(island_count * sizeof(int));
    find_paths(start_index, end_index, bridges, bridge_count, island_count, distances, temp_path, 0, &all_paths, islands);

    free(distances);
    free(temp_path);

    return all_paths;
}
