#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int findValue_sol(node_t* head, int n) {
    if ( (!head) || (n <= 0) ) {
        return -1;
    }
    else {
        node_t* current = head;  int i = 1;
        while (current) {
            if(i == n){
                return current->value;
            }else{
                current = current->next;
                i++;
            }
        }
        return -1;
    }
}

/**
if (!head) return -1;
if (n<=0) return -1;
if (n==1) return head->value;
return findValue(head->next, n-1);
*/
