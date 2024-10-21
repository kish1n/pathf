#include "../inc/libmx.h"

void mx_printstr(const char *string){
    int index = 0;
    char symbol = string[0];
    while(symbol != 0){
        write(1, &symbol, 1);
        index++;
        symbol = string[index];
    }
}
