typedef struct node {
    struct node* next;
    int value;
} node_t;

typedef struct circular_linked_list{
    struct node* tail;
    int size;
} list_t;

list_t* filter(list_t* list, int (*predicate) (int val));
