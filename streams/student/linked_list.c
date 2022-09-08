#include "linked_list.h"
#include <stdlib.h>

node_t *init_node(int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL){return NULL;}
    new_node->next = NULL;
    new_node->value = value;
    return new_node;
}

int add_node(list_t *list, int value) {
    if(list == NULL){return 1;}
    if(list->size == 0){
        list->first = init_node(value);
        list->size = 1;
        return 0;
    }
    node_t *temp = init_node(value);
    if(temp == NULL){return 1;}
    temp->next = list->first;
    list->first = temp;
    list->size ++;
    return 0;
}