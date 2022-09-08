#include "linked_list.h"

/**
 * @brief Filters a linked list according to the predicate 'f', which will return 0 if the nood has to be deleted, 1 otherwise. 
 * Elements that don't match are thus deleted, don't forget to free when removing them from the linked list.
 * If none of the elements match the predicate, the first node of the list should be set to 'NULL'. 
 * 
 * @param list: A pointer to a linked list.
 * @param f: predicate, takes an int as argument and returns 1 if the value matches the predicate, 0 otherwise.  
 */
void filter(list_t *list, int (*f)(int));

/**
 * @brief Applies the function 'f' to all the elements of the linked list. 
 * 
 * @param list: A pointer to a linked list.
 * @param f: A functions that return the new value generated from the old one that must be put in the node.
 */
void map(list_t *list, int (*f)(int));