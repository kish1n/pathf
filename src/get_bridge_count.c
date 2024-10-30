#include "../inc/pathfinder.h"

int get_bridge_count(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printstr("error: file ");
        mx_printstr((char *)filename);
        mx_printstr(" does not exist\n");
        exit(1);
    }

    char c;
    while (read(fd, &c, 1) > 0 && c != '\n');

    int bridge_count = 0;
    int line_started = 0;
    while (read(fd, &c, 1) > 0) {
        if (c == '\r') continue;

        if (c == '\n') {
            if (line_started) {
                bridge_count++;
                line_started = 0;
            }
        } else {
            line_started = 1;
        }
    }

    if (line_started) {
        bridge_count++;
    }

    close(fd);
    return bridge_count;
}
