/*
* Structure node
*
* @next: pointer to the next node
* @value: value of the node
*
*/
typedef struct node {
    struct node *next;
    int value;
} node_t;

/*
 * Check if two circular linked list with the same size or equals
 *
 * @first: a pointer to a node of one circular linked list
 * @second: a pointer to a node of an other circular linked list
 * @size: the size of the circular linked list
 *
 * @return: 1 if they are equals, 0 otherwise
 *
 */
int is_equivalent(node_t*, node_t*, int);
