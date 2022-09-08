#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

char* filter_sol(node_t* node, int size_mess){

  if (!node) return NULL;

  char* res = (char*) malloc(sizeof(char)*size_mess);

  if (!res) return NULL;

  int cpt = 0;
  while (node)
  {
    if ((node->value >= 'a' && node->value  <= 'z') || (node->value  >= 'A' && node->value  <= 'Z') || (node->value == ' '))
    {
      res[cpt] = node->value ;
      cpt++;
    }
    node = node->next;
  }
  res[cpt] = '\0';
  return res;
}
