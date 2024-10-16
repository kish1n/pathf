#include "../inc/pathfinder.h"

void print_data_island(Result result) {
    if (result.result != -1) {
        // Начало блока вывода
        printf("========================================\n");

        // Вывод пути (Path)
        printf("Path: %s -> %s\n", result.visited[result.visited_count - 1], result.visited[0]);

        // Вывод маршрута (Route)
        printf("Route: ");
        for (int i = result.visited_count - 1; i >= 0; i--) {
            printf("%s", result.visited[i]);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n");

        // Вывод расстояний (Distance)
        printf("Distance: ");
        if (result.distance_count == 1) {
            // Если расстояние одно
            printf("%d\n", result.distances[0]);
        } else {
            // Если расстояний несколько, выводим с символом "+" и итоговой суммой
            int total_distance = 0;
            for (int i = result.distance_count - 1; i >= 0; i--) {
                printf("%d", result.distances[i]);
                total_distance += result.distances[i];
                if (i > 0) {
                    printf(" + ");
                }
            }
            printf(" = %d\n", total_distance);
        }

        // Конец блока вывода
        printf("========================================\n");
    } else {
        printf("No path found.\n");
    }

    // Освобождение памяти
    for (int i = 0; i < result.visited_count; i++) {
        free(result.visited[i]);  // Освобождаем каждую строку в массиве visited
    }
    free(result.visited);  // Освобождаем сам массив указателей на строки
    free(result.distances); // Освобождаем массив расстояний
}
