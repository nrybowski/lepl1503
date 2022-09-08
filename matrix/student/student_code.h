typedef struct node{
    struct node* next;
    int value;
} node_t;

typedef struct list{
    struct node* first;
    int size;
} list_t;

/*
 *@pre lst!=NULL, n>0, m>0
 *@post retourne la matrice correspondant à la linked list lst
 */
int** linked_list_to_matrix(list_t *, int, int);
