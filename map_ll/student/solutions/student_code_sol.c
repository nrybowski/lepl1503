#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int map_sol(int (*mapping_fonction)(product_t*), node_t* head){

    int res;
    node_t* n = head;
    while (n){
        res = mapping_fonction(&(n->product));
        if (res) return 1;
        n = n->next;
    }
    return 0;
};
