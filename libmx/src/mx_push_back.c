#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data){
    if (!*list) {
        *list = mx_create_node(data);
        return;
    } else {
        t_list *song = *list;
        while (song -> next)
            song = song -> next;
        song -> next = mx_create_node(data);
    }
}


