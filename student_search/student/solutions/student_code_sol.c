#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

struct obtree* insert_sol(struct obtree *tree, int noma, char* name, double grade) {

    struct element *current = tree->head;
    struct element *current1l;
    struct element *current1r;

    while (current != NULL){
        current1l = NULL;
        current1r = NULL;
        if (current->noma == noma) {       // si jamais le noma est déjà présent dans l'arbre, remplacer les anciennes données
            current->name = name;          // de l étudiant par les nouvelles données passées en arguments
            current->grade = grade;
            return tree;
        }
        else {
            if (current->noma < noma) {
                current1r = current;
                current = current->right;
            } else {
                current1l = current;
                current = current->left;
            }
        }
    }
    struct element *to_add = (struct element *) malloc(sizeof(struct element));
    if (to_add == NULL){
        return NULL;
    }
    to_add->noma = noma;
    to_add->name = name;
    to_add->left = NULL;
    to_add->right = NULL;
    to_add->grade = grade;

    if (current1l == NULL && current1r != NULL){
        current1r->right = to_add;
        current1r = NULL;
        return tree;
    }
    if (current1r == NULL && current1l != NULL) {
        current1l->left = to_add;
        current1l = NULL;
        return tree;
    }
    if (tree->head == NULL) {
        tree->head = to_add;
        return tree;
    }
    return NULL;
}


struct linked_list* push_sol(struct element * head, struct linked_list * n){               //sous-fonction utilisée pour implémenter convert

    struct linked_node* to_add = (struct linked_node *) calloc(1, sizeof(struct linked_node));
    to_add->noma = head->noma;
    to_add->grade = head->grade;
    to_add->name = head->name;
    to_add->next = NULL;

    if (n->nbr_of_element == 0){
        n->first = to_add;
        n->nbr_of_element++;
        return n;
    }
    struct linked_node* current = n->first;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = to_add;
    n->nbr_of_element++;
    return n;
}



/*
 *@pre n!=NULL
 *@post retourne la liste chainée n contenant tous les éléments présent dans l'arbre passé en argument, dont les étudiants sont triés par
        ordre croissant suivant leur noma
 */

void convert_sol(struct element * head, struct linked_list * n){
    if (head != NULL){
        convert(head->left, n);                 // on utilise un parcours infixe de l'arbre pour obtenir une linked_list avec comme
        n = push_sol(head, n);                      // éléments des étudiants classés par ordre croissant suivant leur noma
        convert(head->right, n);
    }
}



