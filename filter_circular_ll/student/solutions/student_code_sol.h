typedef struct node {
    struct node* next;
    int value;
} node_t;

typedef struct circular_linked_list{
    struct node* tail;
    int size;
} list_t;

/**
 * Filters out the nodes of a circular linked list based on a predicate.
 * 
 * @param list : the circular linked list to filter
 * @param predicate : a function that returns 1 if the node with value "val" must be kept in the filtered list, and 0 otherwise.
 * 
 * @return list_t* : a new circular linked list that contains all the nodes which passed the conditions of the predicate. 
 * Its tail must be the node that was the closest to the tail of the initial list.
 * The nodes of the returned list must be independant from those of the initial one (malloc required).
 * 
 * /!\ If anything goes wrong, return NULL.
 */
list_t* filter_sol(list_t* list, int (*predicate) (int val));
