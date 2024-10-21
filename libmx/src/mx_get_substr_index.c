#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) {
        return -2;
    }

    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);

    if (sub_len > str_len) {
        return -1;
    }

    for (int i = 0; i <= str_len - sub_len; i++) {
        if (mx_strncmp(&str[i], sub, sub_len) == 0) {
            return i;
        }
    }

    return -1;
}
