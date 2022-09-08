#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

// Fonction pour ajouter un élément dans la stack
int push_sol(struct stack** s, int x)
{
    struct stack* p = (struct stack*)malloc(sizeof(*p));
 
    if (p == NULL) {
        return -1;
    }
 
    p->data = x;
    p->next = *s;
    *s = p;
    return 0;
}

int pop_sol(struct stack** s)
{
    int x;
    struct stack* temp;
 
    x = (*s)->data;
    temp = *s;
    (*s) = (*s)->next;
    free(temp);
 
    return x;
}

// Fonction utilitaire pour utilialiser la stack 
void initStack_sol(struct stack** s) { *s = NULL; }
 
// Fonction utilitaire pour verifier si la stack est vide
int isEmpty_sol(struct stack* s)
{
    if (s == NULL)
        return 1;
    return 0;
}

// Function utilitaire qui renvoit l'élément au dessus de la pile
int top_sol(struct stack* s) { return (s->data); }
 
// Fonction utilitaire pour inserer l'element x de façon trier
void sortedInsert_sol(struct stack** s, int x)
{
    // Si la stack est vide ou nouvellement insérer
    // si l'element est plus grand que tout ce qu'il ya dans la stack
    if (isEmpty_sol(*s) || x < top_sol(*s)) {
        push_sol(s, x);
        return;
    }
 
    // Si l'element au dessus de la stack est plus grand que X
    int temp = pop_sol(s);
    sortedInsert_sol(s, x);
 
    // On remet l'element supprimer précedemment
    push_sol(s, temp);
}

// FOnction finale qui trie la Stack
void sortStack_sol(struct stack** s)
{
    // Si la stack n'est pas vide
    if (!isEmpty_sol(*s)) {
        // Supprimer l'element au dessus de la stack
        int x = pop_sol(s);
 
        // Trier ce qui reste
        sortStack_sol(s);
 
        // Rajouter l'element dans la stack trier
        sortedInsert_sol(s, x);
    }
   
}

