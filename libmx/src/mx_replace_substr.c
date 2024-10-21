#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) {
        return NULL;
    }

    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);

    if (sub_len == 0) {
        return mx_strdup(str);
    }

    int count = mx_count_substr(str, sub);

    int new_len = mx_strlen(str) + (replace_len - sub_len) * count;

    char *result = mx_strnew(new_len);
    if (!result) return NULL;

    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (mx_strncmp(&str[i], sub, sub_len) == 0) {
            mx_strcpy(&result[j], replace);
            i += sub_len;
            j += replace_len;
        } else {
            result[j++] = str[i++];
        }
    }

    return result;
}
