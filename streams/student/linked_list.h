#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
* @brief Structure node
*
* @next: pointer to the next node in the list, NULL if last node_t
* @value: value stored in the node
*/
typedef struct node {
  struct node *next;
  int value;
} node_t;


/**
* @brief Structure list
*
* @param first: first node of the list, NULL if list is empty
* @param size: number of nodes in the list
*/
typedef struct list {
  struct node *first;
  int size;
} list_t;


/**
* @brief Create a new node containing the value 'value'.
*
* @param value: value stored in the node
* @param next: pointer to next node, initialised to NULL.

* @return: returns the pointer to the newly created node, or NULL if an error occured.
*/
node_t *init_node(int value);


/**
* @brief Add a node at the head of the list @list and increment the number of nodes in the list (member `size`)
*
* @param l: linked list
* @param value: value to add to the list
*
* @return: 0 if success, 1 otherwise
*/
int add_node(list_t *list, int value);

//----------------------------------------------------------------------------------------------------------------



#endif