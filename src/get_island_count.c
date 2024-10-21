#include "../inc/pathfinder.h"

int get_island_count(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printstr("error: file ");
        mx_printstr((char *)filename);
        mx_printstr(" does not exist\n");
        exit(1);
    }

    char buffer[1];
    int bytes_read = read(fd, buffer, 1);
    if (bytes_read == 0) {
        mx_printstr("error: file ");
        mx_printstr((char *)filename);
        mx_printstr(" is empty\n");
        close(fd);
        exit(1);
    }

    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        mx_printstr("Error opening file");
        exit(1);
    }

    char number_str[256];
    int index = 0;
    char c;
    while (read(fd, &c, 1) > 0 && c != '\n') {
        number_str[index++] = c;
    }
    number_str[index] = '\0';

    if (index == 0) {
        mx_printstr("error: line 1 is not valid\n");
        close(fd);
        exit(1);
    }

    for (int i = 0; i < index; i++) {
        if (!mx_isdigit(number_str[i])) {
            mx_printstr("error: line 1 is not valid\n");
            close(fd);
            exit(1);
        }
    }

    int island_count = mx_atoi(number_str);
    if (island_count <= 0) {
        mx_printstr("error: line 1 is not valid\n");
        close(fd);
        exit(1);
    }

    close(fd);
    return island_count;
}
