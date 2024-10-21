#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    if (!s1) {
        return NULL;
    }

    size_t len = mx_strlen(s1);
    if (len > n) {
        len = n;
    }

    char *new_str = mx_strnew(len);
    if (!new_str) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        new_str[i] = s1[i];
    }

    return new_str;
}
