typedef struct node {
    struct node* next;
    unsigned int value;
} node_t;


/*
 * Retourne la valeur du n-ième noeud @n d'une liste chaînée dont la tête est @head
 *
 * @head : la tête de la liste chaînée
 * @n : le noeud dont la valeur doit être retournée
 *
 * @post retourne la valeur du n-ième noeud, 0 si n est supérieur à la taille de la liste
 *                                       et -1 si n <=0 et si la tête de la liste n'est pas valide.
 */
int findValue(node_t* head, int n);
