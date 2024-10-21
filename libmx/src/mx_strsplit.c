#include "../../inc/pathfinder.h"

char **mx_strsplit(char const *s, char c) {
    if (s == NULL) return NULL;
    int size = mx_count_words(s, c);
    char **arr = (char **)malloc((size + 1) * 8);
    if (!arr) return NULL;

    int count = 0;

    for (int i = 0; i < size; i++) {
        while (*s == c) s++;

        const char *word_start = s;
        count = 0;
        while (*s != c && *s != '\0') {
            count++;
            s++;
        }

        if (count > 0) {
            arr[i] = mx_strndup(word_start, count);
            if (!arr[i]) {
            }
        }
    }

    arr[size] = NULL;

    return arr;
}

int mx_count_words(const char *str, char delimiter) {
    int state = false;
    int count = 0;
    while (*str) {
        if (*str == delimiter)
            state = false;
        else if (state == false) {
            state = true;
            count++;
        }
        str++;
    }
    return count;
}


