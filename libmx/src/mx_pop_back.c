#include "../inc/libmx.h"

void mx_pop_back(t_list **list) {
    if (*list == NULL) return;
    t_list *song = *list;
    while (song -> next -> next)
        song = song -> next;

    free(song -> next);
    song -> next = NULL;
    song = NULL;
}

