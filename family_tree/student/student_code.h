#include<string.h>
#include<stdlib.h>

// Définitions des structures données dans l'énoncé

typedef struct person
{
    char *surname;
    struct person *children;
    int n_children;

} person_t;

typedef struct family_tree
{
    person_t *grand_father;
    person_t *grand_mother;

} family_tree_t;

char **get_last_generation(family_tree_t *tree, char **res);
