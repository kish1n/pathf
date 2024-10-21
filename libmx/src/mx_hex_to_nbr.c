#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) return 0;
    unsigned long res = 0;
    int len = 0;
    while (hex[len]) {
        len++;
    }
    for (int i = 0; i < len; i++) {
        unsigned long val;
        if(hex[i]>='0' && hex[i]<='9') {
            val = hex[i] - '0';
        }
        else if(hex[i]>='a' && hex[i]<='f') {
            val = hex[i] - 'a' + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F') {
            val = hex[i] - 'A' + 10;
        }
        else {
            return 0;
        }

        unsigned long c = 1;
        for (int j = 0; j < len - i - 1; j++) {
            c *= 16;
        }
        res += val * c;
    }
    return res;
}

