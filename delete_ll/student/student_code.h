#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
   int data;  
   struct node *next;
}node_t;

typedef struct  list {
  struct node* head;
  struct node* last;
  int size;
}list_t;

/*
*@pre liste != NULL 
*@pre value : la valeur à supprimer
*@post retourne le nombre d'élements supprimé
*/ 
int deletevalue(list_t* liste, int value);
