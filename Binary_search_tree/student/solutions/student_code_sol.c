#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

struct node *addCorrect(struct node *root, int value) {
    struct node *rootRet = root;
    struct node *parent = NULL; // Garder le précédent noeud visité

    while (root != NULL) {
        parent = root;
        if (root->value == value) return rootRet;
        else if (root->value > value) root = root->left;
        else root = root->right;
    }

    root = malloc(sizeof(struct node));
    if (!root) return rootRet;

    root->value = value;
    root->right = NULL;
    root->left = NULL;

    if (parent == NULL) return root; // Premier noeud dans l'arbre

    if (parent->value > value) parent->left = root;
    else parent->right = root;

    return rootRet;
}

int searchCorrect(struct node *root, int value) {
    while (root != NULL) {
        if (root->value == value) return 1;
        else if (root->value < value) root = root->right;
        else root = root->left;
    }
    return 0;
}

