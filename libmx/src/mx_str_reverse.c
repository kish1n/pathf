#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int length = mx_strlen(s);
    int i = 0;
    while(i < length/2){
        mx_swap_char(&s[i], &s[length - i - 1]);
        i++;
    }
}
