#include "../inc/libmx.h"

bool mx_isspace(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

char *mx_strtrim(const char *str) {
    if (str == NULL) return NULL;
    int size = 0, sp_left = 0, sp_right = 0;
    while (*str) {
        size++;
        str++;
    }
    str -= size;
    while (*str && mx_isspace(*str)) {
        str++;
        sp_left++;
    }
    str -= sp_left;

    for (int i = size - 1; i >= sp_left; i--) {
        if (!mx_isspace(str[i])) {
            break;
        }
        sp_right++;
    }

    char *arr = mx_strnew(size - sp_left - sp_right);

    for (int i = sp_left, j = 0; i <= size - 1 - sp_right; i++, j++)
        arr[j] = str[i];

    return arr;
}



