#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    t_list *res = (t_list*)malloc(16);
    res -> next = NULL;
    res -> data = data;
    return res;
}
