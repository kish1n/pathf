#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (!ptr) {
        return malloc(size);
    }

    void *new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }

    size_t current_size = malloc_usable_size(ptr);
    size_t copy_size = (current_size < size) ? current_size : size;

    mx_memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}
