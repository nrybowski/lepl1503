typedef struct node{
    int val;
    struct node *next;
} node_t;

/* 
 *@pre head1 != NULL, head2 != NULL. Listes chainées représentant un nombre entier positif à l'envers sans zéros inutiles. Chaque noeud contient un entier entre 0 et 9
 *@post retourne une liste chainée représentant la somme des nombres dans head1 et head2 (nombre écrit à l'envers) ou NULL en cas d'erreur
 */
node_t *addLinkedLists(node_t *head1, node_t *head2);