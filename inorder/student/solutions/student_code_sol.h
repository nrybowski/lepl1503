typedef struct tree{
    int value;              // the value at root of this tree
    int number_elements;    // number of elements in the tree bellow this root (including self)  (ex : tree(1, 
                            //                                                                              left: tree(2) , 
                            //                                                                              right : tree(3)).number_elements == 3   )
    struct tree *left;      // left sub-tree
    struct tree *right;     // right sub-tree
}tree_t;

int *in_order_sol(tree_t *tree);