#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student_code_sol.h"

int sorting_strings(const void * s1,const void * s2){
    return strcmp(*(char **)s1,*(char **)s2);
}

/**
 *
 * Retourne un tableau contenant les prénoms des personnes en troisième génération, triés dans l'ordre alphabétique
 * @param tree: pointeur vers une structure family_tree_t
 * @param res: pointeur vers des chaines de caractères, qui va contenir le résultat retourné par la fonction
 */
char **get_last_generation_sol(family_tree_t *tree, char **res)
{

    int nb_tot_enfants = 0;
    if (tree == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < tree->grand_father->n_children; i++)
    {
        person_t second_gen = tree->grand_father->children[i];
        for (int j = 0; j < second_gen.n_children; j++)
        {
            res[nb_tot_enfants] = (second_gen.children[j]).surname;
            nb_tot_enfants++;
        }
    }
    if (nb_tot_enfants==0)
    {
        res[0]="Pas d'enfant";
        return res;
    }
    // on trie le tableau par ordre alphabétique
    qsort(res,nb_tot_enfants,sizeof(char *),sorting_strings);
    return res;
}
