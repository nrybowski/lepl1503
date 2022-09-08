#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"


node_t * buildlist(int tab[], int size) {
    node_t *first = malloc(sizeof(node_t));
    first->value = tab[0];
    node_t *tmp = first;

    for(int i = 1; i < size; i++) {
        node_t * new = malloc(sizeof(node_t));
        new->value = tab[i];
        tmp->next = new;
        tmp = new;
    }

    tmp->next = first;

    return first;
}

void freeliste(node_t* list, int size) {
    node_t * tmp;
    for (int i = 0; i < size-1; i++) {
        tmp = list->next;
        free(list);
        list = tmp;
    }
    free(list);
}

char *printList( node_t *list, int size){
    if (list==NULL){
        char *res = malloc(3);
        strcpy(res,"[]");
        return res;
    }
    char *a = malloc(size*2 + 1);
    strcpy(a, "[");
    for (size_t i = 0; i < size; i++)
    {
        char *value;
        if (i < size - 1) value = _("%d,");
        else value = _("%d");

        char temp[strlen(value)];

        sprintf(temp, value, list->value);
        strcat(a, temp);
        list = list->next;
    }
    strcat(a, "]");
    return a;
}

void error(node_t *first, node_t *second, int ret, int size){
    char *error = _("You returned the wrong value. With the lists %s and %s, you returned %d");
    char errorMsg[strlen(error)];
    char *list_first = printList(first, size);
    char *list_second = printList(second, size);
    sprintf(errorMsg, error,list_first, list_second, ret);
    push_info_msg(errorMsg);
    free(list_first);
    free(list_second);
}

void test1(){

    set_test_metadata("isequivalent", _("Test simple avec deux listes circulaires équivalentes"), 1);

    int un[] = {1,2,3,4};
    node_t *first = buildlist(un, 4);

    int deux[] = {4,1,2,3};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }
    freeliste(first,4);
    freeliste(second,4);
}

void test2(){
    set_test_metadata("isequivalent", _("Test simple avec deux listes circulaires équivalentes"), 1);

    int un[] = {18,34,9,2};
    node_t *first = buildlist(un, 4);

    int deux[] = {34,9,2,18};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }
    freeliste(first,4);
    freeliste(second,4);
}

void test3(){
    
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires équivalentes de taille 1"), 1);
    int un[] = {6};
    node_t *first = buildlist(un, 1);

    int deux[] = {6};
    node_t *second = buildlist(deux, 1);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,1);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 1);
    }
    freeliste(first,1);
    freeliste(second,1);
}

void test4(){
    set_test_metadata("isequivalent", _("Test simple avec deux listes circulaires NON équivalentes"), 1);
    int un[] = {6,4,12,3,2};
    node_t *first = buildlist(un, 5);

    int deux[] = {12,3,2,6,5};
    node_t *second = buildlist(deux, 5);

    int rep = 0;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,5);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 5);
    }
    freeliste(first,5);
    freeliste(second,5);
}

void test5(){
    
    set_test_metadata("isequivalent", _("Test simple avec deux listes circulaires NON équivalentes"), 1);
    int un[] = {23,8,12,1,2};
    node_t *first = buildlist(un, 5);

    int deux[] = {2,3,8,12,1};
    node_t *second = buildlist(deux, 5);

    int rep = 0;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,5);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 5);
    }
    freeliste(first,5);
    freeliste(second,5);
}

void test6(){

    set_test_metadata("isequivalent", _("Test avec deux listes circulaires NON équivalentes de taille 1"), 1);
    int un[] = {6};
    node_t *first = buildlist(un, 1);

    int deux[] = {4};
    node_t *second = buildlist(deux, 1);

    int rep = 0;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,1);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 1);
    }
    freeliste(first,1);
    freeliste(second,1);
}

void test7(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires équivalentes alignées"), 1);
    int un[] = {18,23,398,42};
    node_t *first = buildlist(un, 4);

    int deux[] = {18,23,398,42};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }
    freeliste(first,4);
    freeliste(second,4);
}

void test8(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires NON équivalentes (seul le dernier élément change)"), 1);
    int un[] = {6,4,12,3,2};
    node_t *first = buildlist(un, 5);

    int deux[] = {6,4,12,3,5};
    node_t *second = buildlist(deux, 5);

    int rep = 0;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,5);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 5);
    }
    freeliste(first,5);
    freeliste(second,5);
}

void test9(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires NON équivalentes (seul le premier élément change)"), 1);
    int un[] = {6,4,12,3,2};
    node_t *first = buildlist(un, 5);

    int deux[] = {12,4,12,3,2};
    node_t *second = buildlist(deux, 5);

    int rep = 0;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,5);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 5);
    }
    freeliste(first,5);
    freeliste(second,5);
}

void test10(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires équivalentes décalage de 1"), 1);
    int un[] = {34,25,32,40};
    node_t *first = buildlist(un, 4);

    int deux[] = {40,34,25,32};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }
    freeliste(first,4);
    freeliste(second,4);
}

void test11(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires équivalentes décalage de size-1"), 1);
    int un[] = {12,42,32,41};
    node_t *first = buildlist(un, 4);

    int deux[] = {42,32,41,12};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }
    freeliste(first,4);
    freeliste(second,4);
}
void test12(){
    set_test_metadata("isequivalent", _("Test avec deux listes circulaires équivalentes contenant les mêmes valeurs"), 1);
    int un[] = {12,12,12,12};
    node_t *first = buildlist(un, 4);

    int deux[] = {12,12,12,12};
    node_t *second = buildlist(deux, 4);

    int rep = 1;
    int res;
    SANDBOX_BEGIN;
    res= is_equivalent(first,second,4);
    SANDBOX_END;


    CU_ASSERT_EQUAL(rep,res);
    if (rep != res){
        error(first, second, res, 4);
    }

    freeliste(first,4);
    freeliste(second,4);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11, test12);
}
