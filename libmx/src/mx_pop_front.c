#include "../inc/libmx.h"

void mx_pop_front(t_list **list) {
    if (*list == NULL) return;
    t_list *song = *list;
    *list = song -> next;
    free(song);
    song = NULL;
}


