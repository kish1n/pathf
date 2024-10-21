#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data){
    if (!*list) {
        *list = mx_create_node(data);
        return;
    } else {
        t_list *song = mx_create_node(data);
        song -> next = *list;
        *list = song;
    }
}

