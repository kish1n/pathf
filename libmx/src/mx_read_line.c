#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0 || !lineptr || buf_size == 0) {
        return -2;
    }

    *lineptr = mx_strnew(buf_size);
    if (!*lineptr) {
        return -2;
    }

    static char buffer[1];
    static ssize_t bytes_read = 0;
    static int index = 0;

    size_t total_bytes = 0;
    char *temp = *lineptr;

    while (1) {
        if (index >= bytes_read) {
            bytes_read = read(fd, buffer, 1);
            if (bytes_read <= 0) {
                return (total_bytes == 0) ? -1 : (int)total_bytes;
            }
            index = 0;
        }

        if (buffer[index] == delim) {
            index++;
            break;
        }

        temp[total_bytes++] = buffer[index++];

        if (total_bytes >= buf_size) {
            buf_size *= 2;
            temp = mx_strnew(buf_size);
            if (!temp) return -2;
            mx_strcpy(temp, *lineptr);
            free(*lineptr);
            *lineptr = temp;
        }
    }

    temp[total_bytes] = '\0';
    return (int)total_bytes;
}
