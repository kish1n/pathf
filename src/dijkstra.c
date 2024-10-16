#include "../inc/pathfinder.h"

// Максимальное количество путей, которое будем обрабатывать (для примера)

// Функция для поиска индекса острова в массиве островов
int get_island_index(char *island, char *islands[], int island_count) {
    for (int i = 0; i < island_count; i++) {
        if (mx_strcmp(islands[i], island) == 0) {
            return i;
        }
    }
    return -1;  // Остров не найден
}

// Восстановление пути на основе массива previous
void restore_path(int *previous, int start_index, int end_index, int *path, int *path_len) {
    int current = end_index;
    while (current != start_index && current != -1) {
        path[(*path_len)++] = current;
        current = previous[current];
    }
    path[(*path_len)++] = start_index;
}

// Алгоритм Дейкстры для поиска всех кратчайших путей между двумя островами
Result* dijkstra(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end, int *path_count) {
    // Выделяем память для массивов расстояний, посещённых островов и предыдущих вершин
    int *distances = (int *)malloc(island_count * sizeof(int));  // Кратчайшие расстояния
    bool *visited = (bool *)malloc(island_count * sizeof(bool));  // Флаг посещения вершин
    int *previous = (int *)malloc(island_count * sizeof(int));  // Для восстановления пути

    // Проверка на успешное выделение памяти
    if (!distances || !visited || !previous) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    // Инициализация массивов
    for (int i = 0; i < island_count; i++) {
        distances[i] = INFINITY;  // Все расстояния — бесконечность
        visited[i] = false;       // Все вершины непосещённые
        previous[i] = -1;         // Нет предыдущих вершин
    }

    // Находим индексы стартовой и конечной точки
    int start_index = get_island_index(start, islands, island_count);
    int end_index = get_island_index(end, islands, island_count);
    if (start_index == -1 || end_index == -1) {
        *path_count = 0;
        free(distances);
        free(visited);
        free(previous);
        return NULL;  // Возвращаем пустой результат, если одна из точек не найдена
    }

    distances[start_index] = 0;  // Начальная точка получает расстояние 0

    // Массив для хранения нескольких путей
    Result* results = (Result *)malloc(MAX_PATHS * sizeof(Result));
    *path_count = 0;

    // Основной цикл алгоритма Дейкстры
    while (true) {
        // Находим непосещённую вершину с минимальным расстоянием
        int min_distance = INFINITY;
        int current = -1;
        for (int i = 0; i < island_count; i++) {
            if (!visited[i] && distances[i] < min_distance) {
                min_distance = distances[i];
                current = i;
            }
        }

        // Если не найдено доступных вершин, завершить алгоритм
        if (current == -1) break;

        // Отмечаем текущую вершину как посещённую
        visited[current] = true;

        // Если достигли конечного острова, сохраняем путь
        if (current == end_index) {
            // Восстановление пути
            int *path = (int *)malloc(island_count * sizeof(int));  // Массив для хранения индексов пути
            int path_len = 0;
            restore_path(previous, start_index, end_index, path, &path_len);

            // Заполняем структуру Result
            Result res;
            res.distances = (int *)malloc((path_len - 1) * sizeof(int));  // Для хранения расстояний между островами
            res.visited = (char **)malloc(path_len * sizeof(char *));     // Для хранения посещённых островов

            // Заполняем массивы visited и distances
            res.visited_count = path_len;
            res.distance_count = path_len - 1;
            res.result = distances[end_index];

            for (int i = 0; i < path_len; i++) {
                res.visited[i] = mx_strdup(islands[path[i]]);
                if (i > 0) {
                    // Находим расстояние между соседними островами на пути
                    for (int j = 0; j < bridge_count; j++) {
                        if ((mx_strcmp(islands[path[i - 1]], bridges[j].island1) == 0 &&
                             mx_strcmp(islands[path[i]], bridges[j].island2) == 0) ||
                            (mx_strcmp(islands[path[i - 1]], bridges[j].island2) == 0 &&
                             mx_strcmp(islands[path[i]], bridges[j].island1) == 0)) {
                            res.distances[i - 1] = bridges[j].distance;
                            break;
                        }
                    }
                }
            }

            // Сохраняем путь в массив results
            if (*path_count < MAX_PATHS) {
                results[*path_count] = res;
                (*path_count)++;
            }

            free(path);  // Освобождаем временный путь
        }

        // Обновляем расстояния до соседей текущей вершины
        for (int j = 0; j < bridge_count; j++) {
            int neighbor = -1;
            if (mx_strcmp(islands[current], bridges[j].island1) == 0) {
                neighbor = get_island_index(bridges[j].island2, islands, island_count);
            } else if (mx_strcmp(islands[current], bridges[j].island2) == 0) {
                neighbor = get_island_index(bridges[j].island1, islands, island_count);
            }

            // Если сосед существует и не посещён
            if (neighbor != -1 && !visited[neighbor]) {
                int new_distance = distances[current] + bridges[j].distance;
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    previous[neighbor] = current;  // Обновляем предыдущую вершину
                } else if (new_distance == distances[neighbor]) {
                    // Если найден путь с такой же длиной, сохраняем его
                    previous[neighbor] = current;
                }
            }
        }
    }

    // Освобождаем выделенную память
    free(distances);
    free(visited);
    free(previous);

    return results;  // Возвращаем массив результатов
}
