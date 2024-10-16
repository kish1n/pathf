#include "../inc/pathfinder.h"

Bridge *mx_read_bridges(const char *filename, int *bridge_count) {
    // Предполагаем, что функция mx_size корректно реализована
    int file_size = mx_size(filename);
    if (file_size == -1) {
        mx_printstr("Error: cannot determine file size\n");
        exit(1);
    }

    // Открываем файл
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        mx_printstr("Error: cannot open file\n");
        exit(1);
    }

    // Выделяем память для содержимого файла
    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL) {
        mx_printstr("Error: malloc failed\n");
        close(fd);  // Закрываем файл при ошибке
        exit(1);
    }

    // Читаем данные из файла
    ssize_t bytes_read = read(fd, file_content, file_size);
    if (bytes_read != file_size) {
        mx_printstr("Error: could not read entire file\n");
        free(file_content);
        close(fd);  // Закрываем файл при ошибке
        exit(1);
    }
    file_content[file_size] = '\0';  // Завершаем строку нуль-символом
    close(fd);

    // Разделяем содержимое файла на строки
    char **lines = mx_strsplit(file_content, '\n');
    free(file_content);  // Освобождаем память, выделенную под содержимое файла

    // Определяем количество мостов (строк, кроме первой)
    *bridge_count = 0;
    for (int i = 1; lines[i] != NULL; i++) {
        (*bridge_count)++;
    }

    // Выделяем память под массив структур Bridge
    Bridge *bridges = (Bridge *)malloc(sizeof(Bridge) * (*bridge_count));
    if (!bridges) {
        mx_printstr("Error: malloc failed for bridges\n");
        mx_del_strarr(&lines);  // Освобождаем память
        exit(1);
    }

    // Заполняем структуры Bridge
    for (int i = 0; i < *bridge_count; i++) {
        // Разбиваем строку на части
        char **bridge_parts = mx_strsplit(lines[i + 1], '-');  // lines[i + 1], так как 0-я строка пропущена
        if (!bridge_parts || !bridge_parts[1]) {
            printf("Error in bridge_parts for line %d: %s\n", i + 1, lines[i + 1]);
            mx_printstr("Error: invalid bridge format\n");
            mx_del_strarr(&lines);
            free(bridges);
            exit(1);
        }

        // Разбиваем вторую часть строки на остров и расстояние
        char **bridge_info = mx_strsplit(bridge_parts[1], ',');
        if (!bridge_info || !bridge_info[1]) {
            printf("Error in bridge_info for line %d: %s\n", i + 1, lines[i + 1]);
            mx_printstr("Error: invalid bridge info\n");
            mx_del_strarr(&bridge_parts);
            mx_del_strarr(&lines);
            free(bridges);
            exit(1);
        }

        // Копируем информацию в структуру Bridge
        bridges[i].island1 = mx_strdup(bridge_parts[0]);
        bridges[i].island2 = mx_strdup(bridge_info[0]);
        bridges[i].distance = mx_atoi(bridge_info[1]);

        // Освобождаем промежуточные массивы
        mx_del_strarr(&bridge_parts);
        mx_del_strarr(&bridge_info);
    }

    // Освобождаем память от строк
    mx_del_strarr(&lines);

    return bridges;
}
