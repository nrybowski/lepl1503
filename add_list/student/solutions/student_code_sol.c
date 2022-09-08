#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

node_t* addLinkedLists_sol(node_t* head1, node_t* head2){
    node_t *ans = (node_t *)malloc(sizeof(node_t));
    if (ans == NULL) return NULL;
    node_t *current = ans;
    node_t *current1 = head1;
    node_t *current2 = head2;
    int report = 0;
    while (current1 != NULL || current2 != NULL){
        int tmp = (current1 != NULL ? current1->val : 0) + (current2 != NULL ? current2->val : 0) + report;
        if (tmp >= 10) report = 1;
        else report = 0;
        current->next = (node_t *)malloc(sizeof(node_t));
        if (current->next == NULL) return NULL;
        current->next->val = tmp % 10;
        current = current->next;
        if (current1 != NULL) current1 = current1->next;
        if (current2 != NULL) current2 = current2->next;
    }
    if (report > 0){
        current->next = (node_t *)malloc(sizeof(node_t));
        if (current->next == NULL) return NULL;
        current->next->val = 1;
        current = current->next;
    }
    current->next = NULL;
    return ans->next;
}
