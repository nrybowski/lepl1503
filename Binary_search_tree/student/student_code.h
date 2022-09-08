#ifndef SCODE
#define SCODE
struct node {
    struct node *left, *right;
    int value;
};

/**
 * Cette fonction ajoute un noeud avec la valeur "value" dans l'arbre.
 * Si cette valeur existe déjà, l'arbre n'est pas modifié.
 *
 * @param root le noeud root de l'arbre (peut être NULL)
 * @param value créer un noeud avec la valeur "value" et l'ajoute dans l'arbre
 * @return le root de l'arbre
 */
struct node *add(struct node *root, int value);

/**
 * Cette fonction vérifie si "value" se trouve dans l'arbre
 * @param root le noeud root de l'arbre (peut être NULL)
 * @param value la valeur à chercher dans l'arbre
 * @return 1 si "value" se trouve dans l'arbre, 0 sinon
 */
int search(struct node *root, int value);
#endif