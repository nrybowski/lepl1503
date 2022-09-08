#include <stdlib.h>
#include <stdlib.h>
#include <mcheck.h>
#include "../../course/common/student/CTester/CTester.h"

#include "student_code.h"

/**
* Add @val value at the head of the @q queue
*
* @val     : the value to enqueue
* @q     : the queue
*
* @return 0 if no error, -1 otherwise
*
* pre : The queue q will always be valid, you don't need to handle the NULL case.
*/
int enqueue(list_t* q, int val) {
    if (q == NULL) 
        return -1;
    node_t *newTail = (node_t *) malloc(sizeof(node_t));
    if (newTail == NULL) 
        return -1;
    newTail->value = val;
    if (q->tail == NULL) 
        q->tail = newTail;
    else 
        newTail->next = q->tail->next;
    q->tail->next = newTail;
    q->size++;
    return 0;
}

/**
 * Frees a circular linked list
 * 
 * @param : the list to free
 */
void free_list(list_t *list) {
    if (list == NULL) 
        return;
    if (list->tail == NULL) {
        free(list);
        return;
    }
    node_t *curr = list->tail->next;
    node_t *nxt;
    for (int i = 0; i < list->size; i++) {
       if(!curr) return;
       nxt = curr->next;
       free(curr);
       curr = nxt;
    }
    free(list);
}

int flag = 1;
/**
 * Applies CUnit assertions to test whether actual and expected are 
 * 
 * @param actual : the first list
 * @param expected : the second list
 */
void assert_lists_equal(list_t* actual, list_t* expected) {
    if  (actual == NULL && expected == NULL) 
        return;
    if  (actual == NULL || expected == NULL) 
        { 
            CU_ASSERT_PTR_EQUAL(actual, expected); 
            if (actual != expected) push_info_msg("Your list should be NULL");
            return; 
        }
    if  (actual->size != expected->size) 
    { 
        CU_ASSERT_EQUAL(actual->size, expected->size); 
        char *error = _("Wrong size for the list expected : %d, returned : %d");
        char errorMsg[strlen(error)];
        sprintf(errorMsg, error, expected->size, actual->size);
        push_info_msg(errorMsg);
        return; 
    }
    node_t *temp1 = actual->tail;
    node_t *temp2 = expected->tail;
    for (int i = 0; i < actual->size; i++) {
        if (temp1 == NULL) return;
        CU_ASSERT_EQUAL(temp1->value, temp2->value);
        if (temp1->value != temp2->value){
            flag = 0;
            return;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    CU_ASSERT_PTR_NOT_NULL(temp1);
    if (temp1 == NULL) push_info_msg("Beware the last node should point toward the first node of the list");
    return;
}

char *printList( list_t *list){
    if (list==NULL){
        char *res = malloc(3);
        strcpy(res,"[]");
        return res;
    }
    node_t *curr = list->tail;
    if (curr == NULL){
        char *res = malloc(3);
        strcpy(res,"[]");
        return res;
    }
    char *a = malloc(list->size*2 + 1);
    strcpy(a, "[");
    for (size_t i = 0; i < list->size; i++)
    {
        char *value;
        if (i < list->size - 1) value = _("%d,");
        else value = _("%d");

        char temp[strlen(value)];

        sprintf(temp, value, curr->value);
        strcat(a, temp);
        curr = curr->next;
    }
    strcat(a, "]");
    return a;
}

typedef enum pred{REJECT, ACCEPT, EVEN} pred_t;

void error(list_t *expected, list_t *ret, list_t* initial, pred_t pred){
    char *error = _("You returned the wrong list. With the list %s and predicate %s, the expected list was : %s while your returned list was : %s");
    char errorMsg[strlen(error)];
    char *list_init = printList(initial);
    char *list_exp = printList(expected);
    char *list_ret = printList(ret);
    char *pred_str;
    switch(pred){
        case REJECT:
            pred_str = "(elem) -> return 0;";
            break;
        case ACCEPT:
            pred_str = "(elem) -> return 1;";
            break;
        case EVEN:
            pred_str = "(elem) -> return elem\%2 == 0;";
            break;
    }
    sprintf(errorMsg, error,list_init, pred_str, list_exp, list_ret);
    push_info_msg(errorMsg);
    free(list_ret);
    free(list_init);
    free(list_exp);
}

int pred_reject_all(int a) { return 0; }
int pred_accept_all(int a) { return 1; }
int pred_accept_even(int a) {return (a%2 == 0) ? 1 : 0;}

void test_null() {
    // Test de base pour un input NULL
    set_test_metadata("filter", _("Test liste NULL"), 1);
    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(NULL, pred_accept_all);
    SANDBOX_END;

    CU_ASSERT_PTR_NULL(got);
    if (got != NULL) push_info_msg("Your list should be NULL with a NULL input");
    free_list(got);
}

void test_empty() {
    // Test de base pour une liste vide
    set_test_metadata("filter", _("Test liste vide"), 1);
    list_t init; init.size = 0; init.tail = NULL;

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_accept_all);
    SANDBOX_END;

    CU_ASSERT_PTR_NOT_NULL(got);
    CU_ASSERT_EQUAL(got->size, 0);
    CU_ASSERT_PTR_NULL(got->tail);
    free_list(got);
}

void test_single_accepted() {
    // Test de base d'une liste d'un élément accepté
    set_test_metadata("filter", _("Test node unique acceptée"), 1);
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 17) != 0) 
        return;
    
    list_t expect; expect.size = 0; expect.tail = NULL;
    enqueue(&expect, 17);

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_accept_all);
    SANDBOX_END;
    
    error(&expect, got, &init, ACCEPT);

    assert_lists_equal(got, &expect);
    if (!flag) error(&expect, got, &init, ACCEPT);
    free_list(got);
}

void test_single_rejected() {
    // Test de base d'une liste d'un élément rejeté
    set_test_metadata("filter", _("Test node unique rejetée"), 1);
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 17) != 0) 
        return;

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_reject_all);
    SANDBOX_END;

    CU_ASSERT_PTR_NOT_NULL(got);
    CU_ASSERT_EQUAL(got->size, 0);
    CU_ASSERT_PTR_NULL(got->tail);
    if (got != NULL && got->size != 0){
        push_info_msg("You dont update the size of the list correctly");
    }
    if(got==NULL || got->tail != NULL){
        error(NULL, got, &init, REJECT);
    }
    free_list(got);
}

void test_triple_even_unchanged_tail() {
    // Test de base sur une liste de taille 3 dont la tail est acceptée
    set_test_metadata("filter", _("Test tail inchangée"), 1);
    flag = 1;
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 18) != 0 ||
        enqueue(&init, 17) != 0 ||
        enqueue(&init, 16) != 0) 
        return;
    list_t exp; exp.size = 0; exp.tail = NULL;
    if (enqueue(&exp, 18) != 0 ||
        enqueue(&exp, 16) != 0) 
        return;

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_accept_even);
    SANDBOX_END;

    

    assert_lists_equal(got, &exp);
    if (!flag){
        error(&exp, got, &init, EVEN);
    }
    free_list(got);
}

void test_triple_even_modified_tail() {
    // Test de base sur une liste de taille 3 dont la tail n'est pas acceptée
    set_test_metadata("filter", _("Test tail modifée"), 1);
    flag = 1;
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 19) != 0 ||
        enqueue(&init, 28) != 0 ||
        enqueue(&init, 17) != 0) 
        return;
    list_t exp; exp.size = 0; exp.tail = NULL;
    if (enqueue(&exp, 28) != 0) 
        return;

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_accept_even);
    SANDBOX_END;
    assert_lists_equal(got, &exp);
    if (!flag){
        error(&exp, got, &init, EVEN);
    }
    free_list(got);
}

void test_five_rejected() {
    // Test sur une longue liste dont aucune node n'est acceptée
    set_test_metadata("filter", _("Test longue liste rejetée"), 1);
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 19) != 0 ||
        enqueue(&init, 28) != 0 ||
        enqueue(&init, 1) != 0 ||
        enqueue(&init, 3) != 0 ||
        enqueue(&init, 17) != 0) 
        return;

    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_reject_all);
    SANDBOX_END;
    CU_ASSERT_PTR_NOT_NULL(got);
    CU_ASSERT_EQUAL(got->size, 0);
    CU_ASSERT_PTR_NULL(got->tail);
    if (got != NULL && got->size != 0){
        push_info_msg("You dont update the size of the list correctly");
    }
    if(got==NULL || got->tail != NULL){
        error(NULL, got, &init, REJECT);
    }
}

void test_unchanged_initial_list() {
    // Vérifie que, lors de l'opération, la liste initiale n'est pas modifiée
    set_test_metadata("filter", _("Test liste initiale inchangée"), 1);
    flag = 1;
    list_t init; init.size = 0; init.tail = NULL;
    if (enqueue(&init, 19) != 0 ||
        enqueue(&init, 28) != 0 ||
        enqueue(&init, 17) != 0) 
        return;
    list_t copy; copy.size = 0; copy.tail = NULL;
    if (enqueue(&copy, 19) != 0 ||
        enqueue(&copy, 28) != 0 ||
        enqueue(&copy, 17) != 0) 
        return;
    
    list_t *got = NULL;

    SANDBOX_BEGIN;
    got = filter(&init, pred_accept_even);
    SANDBOX_END;

    assert_lists_equal(&init, &copy);
    if (!flag){
        push_info_msg("You modify the list in the process");
    }
    free_list(got);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_empty, test_null, test_single_accepted, test_single_rejected, test_triple_even_modified_tail, test_triple_even_unchanged_tail, test_five_rejected, test_unchanged_initial_list);
}
