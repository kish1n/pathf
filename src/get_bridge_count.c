#include "../inc/pathfinder.h"

int get_bridge_count(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(2, "Error: cannot open file\n", 24);
        exit(1);
    }

    char buffer[256];
    int bytes_read = read(fd, buffer, 255);
    if (bytes_read <= 0) {
        write(2, "Error: cannot read file\n", 24);
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0';
    close(fd);

    int number = 0;
    for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            number = number * 10 + (buffer[i] - '0');
        } else {
            write(2, "Error: invalid number format\n", 29);
            exit(1);
        }
    }

    return number;
}
