#include "../inc/libmx.h"

int mx_count_substr(const char* str, const char* sub) {
    int count = 0;
    int len = mx_strlen(sub);
    char *s = (char *)str;
    while ((s = mx_strstr(s, sub)) != NULL) {
        count++;
        s += len;
    }
    return count;
}
