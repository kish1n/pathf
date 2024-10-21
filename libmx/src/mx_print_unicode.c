#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c) {
    char buffer[4];
    int size = 0;

    if (c < 0x80) {
        buffer[0] = (char)c;
        size = 1;
    }
    else if (c < 0x800) {
        buffer[0] = (char)((c >> 6) | 0xC0);
        buffer[1] = (char)((c & 0x3F) | 0x80);
        size = 2;
    }
    else if (c < 0x10000) {
        buffer[0] = (char)((c >> 12) | 0xE0);
        buffer[1] = (char)(((c >> 6) & 0x3F) | 0x80);
        buffer[2] = (char)((c & 0x3F) | 0x80);
        size = 3;
    }
    else if (c < 0x200000) {
        buffer[0] = (char)((c >> 18) | 0xF0);
        buffer[1] = (char)(((c >> 12) & 0x3F) | 0x80);
        buffer[2] = (char)(((c >> 6) & 0x3F) | 0x80);
        buffer[3] = (char)((c & 0x3F) | 0x80);
        size = 4;
    }

    write(1, buffer, size);
}
