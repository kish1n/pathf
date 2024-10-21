#include "../inc/libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    return 0;
}


char* mx_strstr(const char*s1, const char*s2) {
    int len1 = mx_strlen(s1);
    int len2 = mx_strlen(s2);

    if (len1 == 0 || len2 == 0 || len1 < len2) {
        return NULL;
    }

    for (int i = 0; i < len1; i++) {
        if (mx_strncmp(s1 + i, s2, len2) == 0) {
            return (char *)s1 + i;
        }
    }

    return NULL;
}
