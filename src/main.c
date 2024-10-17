#include "../inc/pathfinder.h"

bool is_island_unique(char *island, char *island_array[], int count) {
    for (int i = 0; i < count; i++) {
        if (mx_strcmp(island_array[i], island) == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
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

    // Находим кратчайшие пути между всеми парами островов
    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            AllPaths all_paths = get_all_shortest_paths(bridges, bridge_count, islands, island_count, islands[i], islands[j]);

            // Вывод результатов
            for (int k = 0; k < all_paths.count; k++) {
                mx_printstr("Path ");
                mx_printint(k + 1);
                mx_printstr(": ");
                for (int l = 0; l < all_paths.paths[k].length; l++) {
                    mx_printstr(islands[all_paths.paths[k].path[l]]);
                    if (l < all_paths.paths[k].length - 1)
                        mx_printstr(" -> ");
                }
                mx_printchar('\n');
            }

            // Освобождение памяти
            for (int k = 0; k < all_paths.count; k++) {
                free(all_paths.paths[k].path);
            }
            free(all_paths.paths);
        }
    }

    // Освобождение памяти для islands
    for (int i = 0; i < island_count; i++) {
        free(islands[i]);  // Освобождаем каждую строку в массиве islands
    }

    // Освобождение памяти для мостов bridges
    for (int i = 0; i < bridge_count; i++) {
        free(bridges[i].island1);  // Освобождаем память для island1
        free(bridges[i].island2);  // Освобождаем память для island2
    }
    free(bridges);

    return 0;
}


// int main(void) {
//     // Пример данных
//     int bridge_count = 6;
//     Bridge bridges[6] = {
//         {"A", "B", 11},
//         {"A", "C", 10},
//         {"B", "D", 5},
//         {"C", "D", 6},
//         {"C", "E", 15},
//         {"D", "E", 4}
//     };
//
//     char *islands[] = {"A", "B", "C", "D", "E"};
//     int island_count = 5;
//
//     AllPaths all_paths = get_all_shortest_paths(bridges, bridge_count, islands, island_count, "A", "E");
//
//     // Вывод результатов
//     for (int i = 0; i < all_paths.count; i++) {
//         printf("Path %d: ", i + 1);
//         for (int j = 0; j < all_paths.paths[i].length; j++) {
//             printf("%s", islands[all_paths.paths[i].path[j]]);
//             if (j < all_paths.paths[i].length - 1)
//                 printf(" -> ");
//         }
//         printf("\n");
//     }
//
//     // Освобождение памяти
//     for (int i = 0; i < all_paths.count; i++) {
//         free(all_paths.paths[i].path);
//     }
//     free(all_paths.paths);
//
//     return 0;
// }
//
//
