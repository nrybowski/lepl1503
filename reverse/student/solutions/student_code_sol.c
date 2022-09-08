#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

node_t* reverse_sol(node_t* head){
   if(head == NULL) {return NULL;}
   if(head->next == NULL) return head;
   node_t* rest = reverse_sol(head->next);
   head->next->next = head; 
   head->next = NULL;
   return rest;
}
