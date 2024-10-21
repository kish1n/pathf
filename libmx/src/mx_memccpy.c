#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    unsigned char stop = (unsigned char)c;

    while (n--) {
        *d = *s;
        if (*s == stop) {
            return (void *)(d + 1);
        }
        d++;
        s++;
    }
    return NULL;
}
