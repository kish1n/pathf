#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str) return NULL;

    char *trimmed_str = mx_strtrim(str);
    if (!trimmed_str) return NULL;

    int len = mx_strlen(trimmed_str);
    char *result = mx_strnew(len);
    if (!result) {
        free(trimmed_str);
        return NULL;
    }

    int j = 0;
    bool space_found = false;

    for (int i = 0; trimmed_str[i] != '\0'; i++) {
        if (mx_isspace(trimmed_str[i])) {
            if (!space_found) {
                result[j++] = ' ';
                space_found = true;
            }
        }
        else {
            result[j++] = trimmed_str[i];
            space_found = false;
        }
    }

    free(trimmed_str);
    return result;
}
