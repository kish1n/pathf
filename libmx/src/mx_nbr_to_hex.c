#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    if (size < 0) {
        return NULL;
    }
    char *result = (char *)malloc(size + 1);
    for (int i = 0; i < size+1; i++)
    {
        result[i] = '\0';
    }
    return result;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr < 1) return 0;
    unsigned long size = 0;
    unsigned long f_nbr = nbr;

    while (f_nbr > 0) {
        size++;
        f_nbr /= 16;
    }
    char *res = mx_strnew(size);
    if (!res) return NULL;

    while (nbr) {
        unsigned long r = (nbr % 16);
        if (r > 9) {
            r += (unsigned long) 'a' - 10;
        } else {
            r += (unsigned long) '0';
        }
        res[--size] = (char)r;
        nbr /= 16;
    }

    return res;
}


