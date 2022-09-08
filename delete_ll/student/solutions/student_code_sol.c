#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int deletevalue_sol(list_t* liste, int value) {
   int nombre=0;
   for (int i = 0; i < liste->size; i++)
   {
      if (liste->head->data==value){
         node_t *tempLink = liste->head;
         liste->head=liste->head->next;
         liste->last->next=liste->head;
         nombre++;
         free(tempLink);
      }
      else{
         liste->head=liste->head->next;
         liste->last=liste->last->next;
      }
   }
   liste->size=liste->size-nombre;
   if (liste->size == 0) {
       liste->head=NULL;
       liste->last=NULL;
   }
   return nombre;

}

/**
2ème version
int deletevalue_sol(list_t* liste, int value) {
   node_t *curr = liste->last;
   int size = liste->size;
   for (int i = 0; i < size; i++){
      if (curr ==  NULL || curr->next == NULL) break;
      if (curr->next->data == value){
         liste->size--;
         node_t *temp = curr->next->next;
         if(curr->next == liste->head) liste->head = temp;
         if(curr->next == liste->last) liste->last = temp;
         free(curr->next);
         curr->next = temp;
      }else{
          curr = curr->next;
      }
      
   }
   if (liste->size == 0){
      liste->head = 0;
      liste->last = 0;
   }
   return size - liste->size;
  }
*/