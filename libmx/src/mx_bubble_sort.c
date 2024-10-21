#include "../inc/libmx.h"

int mx_bubble_sort(char**arr, int size) {
    int z = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == NULL) return -1;
        for (int j = 0; j < size - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                z ++;
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return z;
}


