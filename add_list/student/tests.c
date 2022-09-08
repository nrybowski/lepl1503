#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 200

node_t *createLinkedList(int arr[], int n){
    node_t *ans = (node_t *)malloc(sizeof(node_t));
    node_t *current = ans;
    for(int i=0; i<n; i++){
        current->val = arr[i];
        if (i < n-1){
            current->next = (node_t *)malloc(sizeof(node_t));
        }
        else current->next = NULL;
        current = current->next;
    }
    return ans;
}

void freeLinkedList(node_t *head){
    node_t *current = head;
    while (current != NULL){
        node_t *tmp = current;
        current = current->next;
        free(tmp);
    }
}

int areEqual(node_t *head1, node_t *head2){
    node_t *current1 = head1, *current2 = head2;
    while (current1 != NULL && current2 != NULL){
        if (current1->val != current2->val) return 0;
        current1 = current1->next;
        current2 = current2->next;
    }
    return current1 == NULL && current2 == NULL;
}

char *str_list(node_t *head){
    if (head == NULL){
        char *msg = malloc(strlen("NULL")+1);
        strcpy(msg, "NULL");
        return msg;
    }
    char *msg = malloc(SIZE);
    char *template = "%d";
    strcpy(msg, "[");
    while (head){
        char temp[strlen(template)];
        sprintf(temp, template, head->val);
        strcat(msg, temp);
        head = head->next;
    }
    strcat(msg, "]");
    return msg;
}

void error(node_t *first, node_t *second, node_t *ret, node_t *exp){
    char *template = _("Wrong return value. With the list %s and %s, the expected answer was %s, but you returned %s");
    char msg[strlen(template) + 4*SIZE];
    char *fs = str_list(first);
    char *ss = str_list(second);
    char *rs = str_list(ret);
    char *es = str_list(exp);
    sprintf(msg, template, fs, ss, es, rs);
    push_info_msg(msg);
    free(fs);
    free(ss);
    free(rs);
    free(es);
}

void test1(){

    set_test_metadata("add_list", "Test somme de [1,2,3] et [2, 3, 4]", 1);

    int tab1[] = {1, 2, 3}, n1 = 3;
    int tab2[] = {2, 3, 4}, n2 = 3;
    int ansTab[] = {3, 5, 7}, ansN = 3;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;

    int ret1 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret1);
    if (ret1 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
}
    
void test2(){

    set_test_metadata("add_list", "Test somme de [9, 9, 9] et [1]", 1);

    int tab1[] = {9, 9, 9}, n1 = 3;
    int tab2[] = {1}, n2 = 1;
    int ansTab[] = {0, 0, 0, 1}, ansN = 4;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;
    int ret2 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret2);
    if (ret2 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test3(){

    set_test_metadata("add_list", "Test somme de [5, 9, 2] et [1, 2, 2, 4]", 1);

    int tab1[] = {5, 9, 2}, n1 = 3;
    int tab2[] = {1, 2, 2, 4}, n2 = 4;
    int ansTab[] = {6, 1, 5, 4}, ansN = 4;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;
    
    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;

    int ret3 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret3);
    if (ret3 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test4(){

    set_test_metadata("add_list", "Test somme de [0] et [1, 2, 3, 4]", 1);

    int tab1[] = {0}, n1 = 1;
    int tab2[] = {1, 2, 3, 4}, n2 = 4;
    int ansTab[] = {1, 2, 3, 4}, ansN = 4;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;

    int ret4 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret4);
    if (ret4 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test5(){

    set_test_metadata("add_list", "Test somme de [1,2, 3, 4] et [0]", 1);

    int tab1[] = {1, 2, 3, 4}, n1 = 4;
    int tab2[] = {0}, n2 = 1;
    int ansTab[] = {1, 2, 3, 4}, ansN = 4;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;

    int ret5 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret5);
    if (ret5 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test6(){

    set_test_metadata("add_list", "Test somme de [0] et [0]", 1);

    int tab1[] = {0}, n1 = 1;
    int tab2[] = {0}, n2 = 1;
    int ansTab[] = {0}, ansN = 1;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;
    int ret6 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret6);
    if (ret6 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test7(){

    set_test_metadata("add_list", "Test somme de [9, 9, 9, 9, 9, 9] et [9, 9, 9]", 1);

    int tab1[] = {9, 9, 9, 9, 9, 9}, n1 = 6;
    int tab2[] = {9, 9, 9}, n2 = 3;
    int ansTab[] = {8, 9, 9, 0, 0, 0, 1}, ansN = 7;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *expectedAns = createLinkedList(ansTab, ansN);
    node_t *actualAns = NULL;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;
    int ret7 = areEqual(expectedAns, actualAns);

    CU_ASSERT_EQUAL(1, ret7);
    if (ret7 != 1) error(head1, head2, actualAns, expectedAns);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(expectedAns);
    freeLinkedList(actualAns);
    
}

void test8(){
    set_test_metadata("add_list", "Test malloc fail", 1);

    int tab1[] = {9, 9, 9, 9, 9, 9}, n1 = 6;
    int tab2[] = {9, 9, 9}, n2 = 3;
    node_t *head1 = createLinkedList(tab1, n1);
    node_t *head2 = createLinkedList(tab2, n2);
    node_t *actualAns = NULL;

    monitored.malloc = true;
    failures.malloc = FAIL_ALWAYS;

    SANDBOX_BEGIN;
    actualAns = addLinkedLists(head1, head2);
    SANDBOX_END;

    CU_ASSERT_EQUAL(actualAns, NULL);
    if (actualAns != NULL) error(head1, head2, actualAns, NULL);

    freeLinkedList(head1);
    freeLinkedList(head2);
    freeLinkedList(actualAns);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7, test8);
}
