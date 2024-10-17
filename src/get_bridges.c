#include "../inc/pathfinder.h"

Bridge *get_bridges(const char *filename, int *bridge_count) {
    int file_size = mx_size(filename);
    if (file_size == -1) {
        mx_printstr("Error: cannot determine file size\n");
        exit(1);
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        mx_printstr("Error: cannot open file\n");
        exit(1);
    }

    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL) {
        mx_printstr("Error: malloc failed\n");
        close(fd);
        exit(1);
    }

    ssize_t bytes_read = read(fd, file_content, file_size);
    if (bytes_read != file_size) {
        mx_printstr("Error: could not read entire file\n");
        free(file_content);
        close(fd);
        exit(1);
    }
    file_content[file_size] = '\0';
    close(fd);

    char **lines = mx_strsplit(file_content, '\n');
    free(file_content);

    *bridge_count = 0;
    for (int i = 1; lines[i] != NULL; i++) {
        (*bridge_count)++;
    }

    Bridge *bridges = (Bridge *)malloc(sizeof(Bridge) * (*bridge_count));
    if (!bridges) {
        mx_printstr("Error: malloc failed for bridges\n");
        mx_del_strarr(&lines);
        exit(1);
    }

    for (int i = 0; i < *bridge_count; i++) {
        char **bridge_parts = mx_strsplit(lines[i + 1], '-');
        if (!bridge_parts || !bridge_parts[1]) {
            printf("Error in bridge_parts for line %d: %s\n", i + 1, lines[i + 1]);
            mx_printstr("Error: invalid bridge format\n");
            mx_del_strarr(&lines);
            free(bridges);
            exit(1);
        }

        char **bridge_info = mx_strsplit(bridge_parts[1], ',');
        if (!bridge_info || !bridge_info[1]) {
            printf("Error in bridge_info for line %d: %s\n", i + 1, lines[i + 1]);
            mx_printstr("Error: invalid bridge info\n");
            mx_del_strarr(&bridge_parts);
            mx_del_strarr(&lines);
            free(bridges);
            exit(1);
        }

        bridges[i].island1 = mx_strdup(bridge_parts[0]);
        bridges[i].island2 = mx_strdup(bridge_info[0]);
        bridges[i].distance = mx_atoi(bridge_info[1]);

        mx_del_strarr(&bridge_parts);
        mx_del_strarr(&bridge_info);
    }

    mx_del_strarr(&lines);

    return bridges;
}
