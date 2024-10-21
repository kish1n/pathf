#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }

    char buffer;
    int size = 0;
    while (read(fd, &buffer, 1) > 0) {
        size++;
    }

    if (size == 0) {
        close(fd);
        return NULL;
    }

    close(fd);

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }

    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        close(fd);
        return NULL;
    }

    int bytes_read = read(fd, str, size);
    if (bytes_read < 0) {
        free(str);
        close(fd);
        return NULL;
    }

    str[size] = '\0';

    close(fd);
    return str;
}


