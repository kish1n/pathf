#include "../inc/pathfinder.h"

// Функция для поиска индекса острова в массиве островов
//int get_island_index(char *island, char *islands[], int island_count) {
//    for (int i = 0; i < island_count; i++) {
//        if (mx_strcmp(islands[i], island) == 0) {
//            return i;
//        }
//    }
//    return -1;  // Остров не найден
//}

// Восстановление пути на основе массива previous
void restore_path(int *previous, int start_index, int end_index, int *path, int *path_len) {
    int current = end_index;
    while (current != start_index && current != -1) {
        path[(*path_len)++] = current;
        current = previous[current];
    }
    path[(*path_len)++] = start_index;
}
