#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

list_t* filter_sol(list_t* list, int (*predicate) (int val)) {
    // Tests préliminaires pour les cas simples (liste vide ou pointeurs nuls)
    if (list == NULL || predicate == NULL)         // ===== <début 1> ===== //
        return NULL;
    if (list->tail == NULL) {
        list_t *l = (list_t *) malloc(sizeof(list_t));
        l->tail = NULL;
        l->size = 0;
        return l;
    }                                // ===== <fin 1> ===== //

    // Allocation de la mémoire pour contenir la liste à renvoyer
    list_t *new_list = (list_t*) malloc(sizeof(list_t));
    if (new_list == NULL)
        return NULL;
    new_list->size = 0;
    new_list->tail = NULL;

    node_t *first = NULL;    // Contient le pointeur vers la tête de la nouvelle linked liste (ouverte dans un premier temps)
    node_t *curr_iter = list->tail->next;    // Pour itérer sur les nodes de l'ancienne liste
    node_t *curr_make = first;    // Pour construire une à une les nodes de la nouvelle liste

    // Crée une linked list ouverte contenant toutes les nodes acceptées par le predicate
    for (int i = 0; i < list->size; i++) {
        if (predicate(curr_iter->value) == 1) {
            // Création d'une nouvelle node pour la liste
            node_t *new_accepted_node = (node_t*) malloc(sizeof(node_t));
            if (new_accepted_node == NULL) {
                // En cas d'échec, libération des pointeurs de toutes les nodes acceptées jusqu'ici, et de la nouvelle liste
                free(new_list);                // ===== <début 4> ===== //
                node_t* curr_delete = first;
                node_t* next_delete;
                while (curr_delete != NULL) {
                    next_delete = curr_delete->next;
                    free(curr_delete);
                    curr_delete = next_delete;
                }                              // ===== <fin 4> ===== //
                return NULL;
            }

            // On initialise les valeurs de la nouvelle node + on incrémente la taille de la liste
            new_accepted_node->value = curr_iter->value;
            new_accepted_node->next = NULL;
            new_list->size++;                   // ======= <2> ======= //
            // À la fin de chaque itération, curr_make est la dernière node acceptée de la liste
            // Elle agit donc comme une tail temporaire
            if (first == NULL) {                // ===== <début 3> ===== //
                first = new_accepted_node;
                curr_make = first;
            } else {                // ===== <fin 3> ===== //
                curr_make->next = new_accepted_node;
                curr_make = curr_make->next;
            }
        }
        curr_iter = curr_iter->next;
    }

    // Fermeture de la linked list créée, qui était ouverte jusqu'à maintenant
    if (curr_make != NULL) 
        curr_make->next = first;
    new_list->tail = curr_make;
    return new_list;
}
