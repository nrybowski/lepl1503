#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 200

void free_list(node_t *list){
    if (!list) return;
    node_t *next = list->next;
    free(list);
    free_list(next);
}


char *str_list(node_t* node){
    if (node == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(SIZE);
    char *template = "%d";
    strcpy(ret, "[");
    while (node){
        char temp[strlen(template)];
        sprintf(temp, template, node->value);
        strcat(ret, temp);
        if (node->next) strcat(ret, ", ");
        node = node->next;
    }
    strcat(ret, "]");
    return ret;
}

void error(node_t *list, int index,  int ret, int exp){
    char *template = _("Wrong return value. With the list %s and index=%d, the expected return was %d, while you returned %d");
    char msg[strlen(template) + SIZE];
    char *list_str = str_list(list);
    sprintf(msg, template, list_str, index, exp, ret);
    push_info_msg(msg);
    free(list_str);
}

void test1() {

    set_test_metadata("find", "Test dernier noeud de la liste 11->3->6->2->8", 1);
    //test de base minimaliste
    node_t* n1 = malloc(sizeof(node_t));    n1->value = 8;    n1->next = NULL;
    node_t* n2 = malloc(sizeof(node_t));    n2->value = 2;    n2->next = n1;
    node_t* n3 = malloc(sizeof(node_t));    n3->value = 6;    n3->next = n2;
    node_t* n4 = malloc(sizeof(node_t));    n4->value = 3;    n4->next = n3;
    node_t* n5 = malloc(sizeof(node_t));    n5->value = 11;    n5->next = n4;

    int res;
    SANDBOX_BEGIN;
    res = findValue(n5, 5);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, 8);
    if (res != 8) error(n5, 5, res, 8);
    free_list(n5);
}

void test2() {

    set_test_metadata("find", "Test premier noeud de la liste 11->3->6->2->8", 1);

    //test de base minimaliste
    node_t* n1 = malloc(sizeof(node_t));    n1->value = 8;    n1->next = NULL;
    node_t* n2 = malloc(sizeof(node_t));    n2->value = 2;    n2->next = n1;
    node_t* n3 = malloc(sizeof(node_t));    n3->value = 6;    n3->next = n2;
    node_t* n4 = malloc(sizeof(node_t));    n4->value = 3;    n4->next = n3;
    node_t* n5 = malloc(sizeof(node_t));    n5->value = 11;    n5->next = n4;

    int res;
    SANDBOX_BEGIN;
    res = findValue(n5, 1);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, 11);
    if (res != 11) error(n5, 1, res, 11);
    free_list(n5);
}

void test3() {

    set_test_metadata("find", "Test troisième noeud de la liste 11->3->6->2->8", 1);

    //test de base minimaliste
    node_t* n1 = malloc(sizeof(node_t));    n1->value = 8;    n1->next = NULL;
    node_t* n2 = malloc(sizeof(node_t));    n2->value = 2;    n2->next = n1;
    node_t* n3 = malloc(sizeof(node_t));    n3->value = 6;    n3->next = n2;
    node_t* n4 = malloc(sizeof(node_t));    n4->value = 3;    n4->next = n3;
    node_t* n5 = malloc(sizeof(node_t));    n5->value = 11;    n5->next = n4;


    int res;
    SANDBOX_BEGIN;
    res = findValue(n5, 3);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, 6);
    if (res != 6) error(n5, 3, res, 6);

    free_list(n5);
}

void test4() {

    set_test_metadata("find", "Test pointeur passé en argument est NULL", 1);

    //test permettant de vérifier le comportement de la fonction lorsque le pointeur passé en argument est NULL
    node_t* n1 = NULL;

    int res;
    SANDBOX_BEGIN;
    res = findValue(n1, 4);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, -1);
    if (res != -1) error(n1, 4, res, -1);
}

void test5() {

    set_test_metadata("find", "Test n supérieur à la taille de la liste", 1);

    //test permettant de vérifier le comportement de la fonction lorsque n est supérieur à la taille de la liste
    node_t* n1 = malloc(sizeof(node_t));    n1->value = 8;    n1->next = NULL;
    node_t* n2 = malloc(sizeof(node_t));    n2->value = 2;    n2->next = n1;
    node_t* n3 = malloc(sizeof(node_t));    n3->value = 6;    n3->next = n2;
    node_t* n4 = malloc(sizeof(node_t));    n4->value = 3;    n4->next = n3;
    node_t* n5 = malloc(sizeof(node_t));    n5->value = 11;    n5->next = n4;

    int res;
    SANDBOX_BEGIN;
    res = findValue(n5, 10);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, -1);
    if (res != -1) error(n5, 10, res, -1);

    free_list(n5);
}

void test6() {

    set_test_metadata("find", "Test n<=0", 1);

    //test permettant de vérifier le comportement de la fonction lorsque n <= 0
    node_t* n1 = malloc(sizeof(node_t));    n1->value = 8;    n1->next = NULL;
    node_t* n2 = malloc(sizeof(node_t));    n2->value = 2;    n2->next = n1;
    node_t* n3 = malloc(sizeof(node_t));    n3->value = 6;    n3->next = n2;
    node_t* n4 = malloc(sizeof(node_t));    n4->value = 3;    n4->next = n3;
    node_t* n5 = malloc(sizeof(node_t));    n5->value = 11;    n5->next = n4;

    int res = 0;
    SANDBOX_BEGIN;
    res = findValue(n5, 0);
    SANDBOX_END;

    char msg[15];
    char *temp = "%d";
    sprintf(msg, temp, res);

    push_info_msg(msg);

    CU_ASSERT_EQUAL(res, -1);
    if (res != -1) error(n5, 0, res, -1);

    free_list(n5);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6);
}
