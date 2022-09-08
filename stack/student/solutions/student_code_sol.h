#include "../student_code.h"

int push_sol(struct stack** s, int x);

void sortStack_sol(struct stack** s);

int pop_sol(struct stack** s);

// Fonction utilitaire pour utilialiser la stack 
void initStack_sol(struct stack** s);
 
// Fonction utilitaire pour verifier si la stack est vide
int isEmpty_sol(struct stack* s);

// Function utilitaire qui renvoit l'élément au dessus de la pile
int top_sol(struct stack* s);
 
// Fonction utilitaire pour inserer l'element x de façon trier
void sortedInsert_sol(struct stack** s, int x);