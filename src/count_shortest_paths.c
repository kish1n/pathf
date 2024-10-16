#include "../inc/pathfinder.h"

int count_shortest_paths(Bridge *bridges, int bridge_count, char *islands[], int island_count, char *start, char *end) {
    // Выделяем память для массивов расстояний, посещённых островов, количества путей
    int *distances = (int *)malloc(island_count * sizeof(int));  // Кратчайшие расстояния
    bool *visited = (bool *)malloc(island_count * sizeof(bool));  // Флаг посещения вершин
    int *previous = (int *)malloc(island_count * sizeof(int));    // Для восстановления пути
    int *path_counts = (int *)malloc(island_count * sizeof(int)); // Количество путей до каждой вершины

    // Проверка на успешное выделение памяти
    if (!distances || !visited || !previous || !path_counts) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    // Инициализация массивов
    for (int i = 0; i < island_count; i++) {
        distances[i] = INFINITY;  // Все расстояния — бесконечность
        visited[i] = false;       // Все вершины непосещённые
        previous[i] = -1;         // Нет предыдущих вершин
        path_counts[i] = 0;       // Изначально количество путей до каждой вершины равно 0
    }

    // Находим индексы стартовой и конечной точки
    int start_index = get_island_index(start, islands, island_count);
    int end_index = get_island_index(end, islands, island_count);
    if (start_index == -1 || end_index == -1) {
        free(distances);
        free(visited);
        free(previous);
        free(path_counts);
        return 0;  // Возвращаем 0, если одна из точек не найдена
    }

    distances[start_index] = 0;  // Начальная точка получает расстояние 0
    path_counts[start_index] = 1; // До начальной точки есть один путь (сама точка)

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

        // Если достигли конечного острова, завершаем цикл
        if (current == end_index) break;

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

                // Если найден более короткий путь
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    previous[neighbor] = current;  // Обновляем предыдущую вершину
                    path_counts[neighbor] = path_counts[current]; // Количество путей до этой вершины равно количеству путей до текущей
                }
                // Если найден другой путь с такой же длиной
                else if (new_distance == distances[neighbor]) {
                    path_counts[neighbor] += path_counts[current]; // Добавляем количество путей до текущей вершины
                }
            }
        }
    }

    int total_paths = path_counts[end_index];  // Количество кратчайших путей до конечной вершины

    // Освобождаем выделенную память
    free(distances);
    free(visited);
    free(previous);
    free(path_counts);

    return total_paths;  // Возвращаем количество кратчайших путей
}

