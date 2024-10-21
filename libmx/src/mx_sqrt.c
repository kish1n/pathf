#include "../inc/libmx.h"

int mx_sqrt(int x) {
    if (x < 0) {
        return 0;
    }

    if (x == 0 || x == 1) {
        return x;
    }

    int start = 2, end = x / 2, result = 0;
    while (start <= end) {
        int mid = start + (end - start) / 2;

        long midSquared = (long)mid * (long)mid;

        if (midSquared == x) {
            return mid;
        }

        if (midSquared < x) {
            start = mid + 1;
            result = mid;
        } else {
            end = mid - 1;
        }
    }

    long resultSquared = (long)result * (long)result;
    if (resultSquared == x) {
        return result;
    } else {
        return 0;
    }
}


