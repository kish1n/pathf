#include "../../inc/pathfinder.h"

int mx_size(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return -1;
    }

    char buffer[BUFFER_SIZE];
    int size = 0;
    int bytes_read = 0;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        size += bytes_read;
    }

    close(fd);
    return size;
}
