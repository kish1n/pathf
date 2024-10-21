#include "../inc/libmx.h"

void mx_swap_char(char*s1, char*s2) {
    char fst = *s1;
    char sec = *s2;
    *s1 = sec;
    *s2 = fst;
}
