#include "../inc/libmx.h"

static int get_num_length(int number) {
    int length = (number <= 0) ? 1 : 0;
    while (number != 0) {
        length++;
        number /= 10;
    }
    return length;
}

char *mx_itoa(int number) {
    int length = get_num_length(number);
    char *str = mx_strnew(length);
    if (!str) return NULL;

    if (number == 0) {
        str[0] = '0';
        return str;
    }

    bool eq = (number < 0);
    if (eq) {
        str[0] = '-';
        number = -number;
    }

    for (int i = length - 1; i >= (eq ? 1 : 0); i--) {
        str[i] = (number % 10) + '0';
        number /= 10;
    }

    return str;
}
