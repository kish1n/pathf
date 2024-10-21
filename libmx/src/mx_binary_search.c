#include "../inc/libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        (*count)++;

        int cmp_result = mx_strcmp(arr[mid], s);
        if (cmp_result == 0) {
            return mid;
        } else if (cmp_result < 0) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    *count = 0;
    return -1;
}
