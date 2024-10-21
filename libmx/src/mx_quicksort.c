#include "../inc/libmx.h"

static void mx_swap_in_arr(char **arr, int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) {
        return -1;
    }

    int swaps = 0;

    if (left < right) {
        int pivot = (left + right) / 2;
        int i = left;
        int j = right;

        while (i <= j) {
            while (mx_strlen(arr[i]) < mx_strlen(arr[pivot])) {
                i++;
            }
            while (mx_strlen(arr[j]) > mx_strlen(arr[pivot])) {
                j--;
            }
            if (i <= j) {
                if (i != j) {
                    mx_swap_in_arr(arr, i, j);
                    swaps++;
                }
                i++;
                j--;
            }
        }

        swaps += mx_quicksort(arr, left, j);
        swaps += mx_quicksort(arr, i, right);
    }

    return swaps;
}
