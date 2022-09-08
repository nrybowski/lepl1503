#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

void map_sol(list_t *list, int (*f)(int)){
    if(list == NULL){return;}
    if(list->first == NULL){return;}
    node_t *current = list->first;
    while(current != NULL){
        current->value = (*f)(current->value);
        current = current->next;
    }
}

void filter_sol(list_t *list, int (*f)(int)){
    if(list == NULL){return;}
    if(list->first == NULL){return;}
    node_t *prev = NULL;
    node_t *current = list->first;
    while(current != NULL){
        if((*f)(current->value)){
            if(prev == NULL){
                list->first = current;
                prev = list->first;
            }
            else{
                prev->next = current;
                prev = current;
            }
            current = current->next;
        }
        else{
            node_t *temp = current;
            current = current->next;
            list->size --;
            free(temp);
        }
    }
    if(prev == NULL){
        list->first = NULL;
    }
    else{
        prev->next = NULL; 
    }
}

