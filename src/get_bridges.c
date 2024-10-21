#include "../inc/pathfinder.h"

Bridge *get_bridges(const char *filename, int *bridge_count) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printstr("error: file ");
        mx_printstr((char *)filename);
        mx_printstr(" does not exist\n");
        exit(1);
    }

    // Пропускаем первую строку (число островов)
    char c;
    while (read(fd, &c, 1) > 0 && c != '\n');

    Bridge *bridges = (Bridge *)malloc((*bridge_count) * 24); // Используем 24 байта на каждый Bridge
    if (!bridges) {
        mx_printstr("error: memory allocation failed\n");
        close(fd);
        exit(1);
    }

    char line[256];
    int index = 0;
    int line_number = 2; // Начинаем с 2, так как первую строку пропустили
    int total_bridge_length = 0;

    int bridge_index = 0;

    while (1) {
        index = 0;
        while (read(fd, &c, 1) > 0 && c != '\n') {
            if (index < 255) {
                line[index++] = c;
            }
        }
        line[index] = '\0';

        if (index == 0 && c != '\n') {
            break; // Конец файла
        }

        if (index == 0) {
            continue; // Пропускаем пустые строки
        }

        int delimiter1 = mx_get_char_index(line, '-');
        int delimiter2 = mx_get_char_index(line, ',');
        if (delimiter1 == -1 || delimiter2 == -1 || delimiter1 >= delimiter2) {
            mx_printstr("error: line ");
            char *line_num_str = mx_itoa(line_number);
            mx_printstr(line_num_str);
            free(line_num_str);
            mx_printstr(" is not valid\n");
            close(fd);
            free(bridges);
            exit(1);
        }

        // Извлекаем названия островов и длину
        char *island1 = mx_strndup(line, delimiter1);
        char *island2 = mx_strndup(line + delimiter1 + 1, delimiter2 - delimiter1 -1);
        char *distance_str = mx_strdup(line + delimiter2 + 1);

        // Проверяем, что названия островов не пустые
        if (mx_strlen(island1) == 0 || mx_strlen(island2) == 0) {
            mx_printstr("error: line ");
            char *line_num_str = mx_itoa(line_number);
            mx_printstr(line_num_str);
            free(line_num_str);
            mx_printstr(" is not valid\n");
            close(fd);
            free(bridges);
            free(island1);
            free(island2);
            free(distance_str);
            exit(1);
        }

        // Проверяем, что длина — положительное число
        for (int i = 0; distance_str[i]; i++) {
            if (!mx_isdigit(distance_str[i])) {
                mx_printstr("error: line ");
                char *line_num_str = mx_itoa(line_number);
                mx_printstr(line_num_str);
                free(line_num_str);
                mx_printstr(" is not valid\n");
                close(fd);
                free(bridges);
                free(island1);
                free(island2);
                free(distance_str);
                exit(1);
            }
        }

        int distance = mx_atoi(distance_str);
        if (distance <= 0) {
            mx_printstr("error: line ");
            char *line_num_str = mx_itoa(line_number);
            mx_printstr(line_num_str);
            free(line_num_str);
            mx_printstr(" is not valid\n");
            close(fd);
            free(bridges);
            free(island1);
            free(island2);
            free(distance_str);
            exit(1);
        }

        // Проверяем на дубликаты мостов
        for (int i = 0; i < bridge_index; i++) {
            if ((mx_strcmp(bridges[i].island1, island1) == 0 && mx_strcmp(bridges[i].island2, island2) == 0) ||
                (mx_strcmp(bridges[i].island1, island2) == 0 && mx_strcmp(bridges[i].island2, island1) == 0)) {
                mx_printstr("error: duplicate bridges\n");
                close(fd);
                // Освобождаем память
                for (int j = 0; j < bridge_index; j++) {
                    free(bridges[j].island1);
                    free(bridges[j].island2);
                }
                free(bridges);
                free(island1);
                free(island2);
                free(distance_str);
                exit(1);
            }
        }

        // Проверяем сумму длин мостов
        if (total_bridge_length > INT_MAX - distance) {
            mx_printstr("error: sum of bridges lengths is too big\n");
            close(fd);
            // Освобождаем память
            for (int j = 0; j < bridge_index; j++) {
                free(bridges[j].island1);
                free(bridges[j].island2);
            }
            free(bridges);
            free(island1);
            free(island2);
            free(distance_str);
            exit(1);
        }
        total_bridge_length += distance;

        // Заполняем структуру моста
        bridges[bridge_index].island1 = island1;
        bridges[bridge_index].island2 = island2;
        bridges[bridge_index].distance = distance;

        free(distance_str);

        bridge_index++;
        line_number++;

        if (c != '\n') {
            break; // Конец файла
        }
    }

    close(fd);

    // Обновляем количество мостов
    *bridge_count = bridge_index;

    return bridges;
}
