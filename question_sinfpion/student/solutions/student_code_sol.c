#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int findMinIndex_sol(node_l* LLhead){
    node_l * current= LLhead;
    int MinVal=current->value;
    int MinIndex=0;
    int Index=0;
    while (current!=NULL ) {
        if ( MinVal > (int) current->value) {
            MinVal = current->value;
            MinIndex = Index; }
        Index++;
        current = current->next; }
    return MinIndex;
}

int removeTheMinIndex_sol(node_l ** LLhead, int MinIndex){
    int i = 0;
    int retval;
    node_l * current = *LLhead;
    node_l * temp = NULL;
    if (*LLhead == NULL) {
            return -1;}

    if (MinIndex == 0) {
        temp = (*LLhead)->next;
        retval = (*LLhead)->value;
        free(*LLhead);
        *LLhead = temp;
        return retval; }

    for (i = 0; i < MinIndex-1; i++) {
        if (current->next == NULL) {
            return -1; }
        current = current->next; }

    if (current->next == NULL) {
        return -1; }

    temp = current->next;
    retval = temp->value;
    current->next = temp->next;
    free(temp);
    return retval;


}
