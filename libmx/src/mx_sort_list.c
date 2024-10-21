#include "../inc/libmx.h"

t_list* mx_sort_list( t_list*list, bool (*cmp)(void*a, void*b)){
    if (cmp == NULL || list == NULL) return list;
    for (t_list *i = list; i != NULL; i = i->next) {
        for (t_list *j = i->next; j != NULL; j = j->next) {
            if (cmp(i->data, j->data)) {
                void *temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    return list;
}


