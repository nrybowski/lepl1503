#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int is_equivalent_sol(node_t* first, node_t* second, int size) {
    int ok;

    //check with an other start position for the second circular linked list
    for(int i = 0; i < size; i++) {
        node_t * tmp_a = first;
        node_t * tmp_b = second;
        ok = 1;

        //check if with a start position they are the same
        for(int j = 0; j < size; j++) {
            if(tmp_a->value != tmp_b->value) {
                ok = 0;
                break;
            }
            tmp_a = tmp_a->next;
            tmp_b = tmp_b->next;
        }

        //if 1 every element are the same with this start config (they are the same)
        if (ok==1) {
            return 1;
        }

        //otherwise we change the start configuration
        second = second->next;
    }

    //we have test all the start position and they are not the same
    return 0;
}
