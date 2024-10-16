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

    int bridge_count = mx_read_bridge_count(argv[1]);
    Bridge *bridges = mx_read_bridges(argv[1], &bridge_count);
    int island_count = mx_island_count(argv[1]);

    char *islands[island_count];
	int current_island_count = 0;  // Счётчик для добавления уникальных островов

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


    for (int i = 0; i < island_count; i++) {
    	for (int j = i + 1; j < island_count; j++) {
        	// Переменная для хранения количества путей, возвращаемого dijkstra
        	int path_count = 0;

        	// Вызов функции для поиска всех кратчайших путей
        	Result *results = dijkstra(bridges, bridge_count, islands, island_count, islands[i], islands[j], &path_count);

        	// Обработка и вывод каждого найденного пути
        	for (int k = 0; k < path_count; k++) {
       		    print_data_island(results[k]);  // Функция для вывода пути
       	 	}
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
