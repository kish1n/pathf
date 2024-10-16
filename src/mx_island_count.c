#include "../inc/pathfinder.h"

int mx_island_count(const char *filename) {
    int fd = open(filename, O_RDONLY);  // Открываем файл для чтения
    if (fd == -1) {
        write(2, "Error: cannot open file\n", 24);  // Сообщаем об ошибке
        exit(1);
    }

    // Буфер для чтения данных
    char buffer[256];
    int bytes_read = read(fd, buffer, 255);  // Читаем первые 255 байт файла
    if (bytes_read <= 0) {
        write(2, "Error: cannot read file\n", 24);
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0';  // Завершаем строку нуль-символом

    // Закрываем файл
    close(fd);

    // Преобразуем строку в число
    int number = 0;
    for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            number = number * 10 + (buffer[i] - '0');  // Преобразование символов в цифры
        } else {
            write(2, "Error: invalid number format\n", 29);
            exit(1);
        }
    }

    return number;
}
