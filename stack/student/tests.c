#include <stdlib.h>
#include "student_code.h"
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 200

char *str_stack(struct stack *s){
    if (s==NULL){
        char *temp = "NULL";
        char *ret = malloc(strlen(temp)+1);
        strcpy(ret, temp);
        return ret;
    }
    char *ret = malloc(SIZE);
    char *template = "%d";
    strcpy(ret, "[");
    while(s){
        char temp[strlen(template)];
        sprintf(temp, template, s->data);
        strcat(ret, temp);
        if (s->next) strcat(ret, ", ");
        s = s->next;
    }
    strcat(ret, "]");
    return ret;

}

char *str_array(int *arr, int nb){
    char *ret = malloc(4*nb);
    char *template = "%d";
    strcpy(ret, "[");
    for (int i = 0; i < nb; i++){
        char temp[strlen(template)];
        sprintf(temp, template, *(arr+i));
        strcat(ret, temp);
        if (i != nb - 1) strcat(ret, ", ");
    }
    strcat(ret, "]");
    return ret;

}

void error(int *exp, struct stack *s, int nb){
    char *template = _("Wrong stack value. The expected value was %s, but your stack is %s");
    char msg[strlen(template) + 4*nb + SIZE];
    char *stack_str= str_stack(s);
    char *exp_str = str_array(exp, nb);
    sprintf(msg, template, exp_str, stack_str);
    push_info_msg(msg);
    free(exp_str);
    free(stack_str);
}

void test1(){

    set_test_metadata("sort", "Test tri de [30,-5,18,14,-3]", 1);
    // test de base minimaliste pour le trie
    struct stack* s= NULL;
    initStack_sol(&s);
    push_sol(&s, 30);
    push_sol(&s, -5);
    push_sol(&s, 18);
    push_sol(&s, 14);
    push_sol(&s, -3);
    int res[] = {-5,-3,14,18,30};
    int i = 0;

    SANDBOX_BEGIN;
    sortStack(&s);
    SANDBOX_END;

    struct stack* temp = s;

    while (s) {
        CU_ASSERT_EQUAL(s->data,res[i]);
        if (s->data != res[i]) return error(res, temp, 5);
        s = s->next;
        i++;
    }
    free(s);
    
}


void test2(){

    set_test_metadata("sort", "Test tri de [0,-5,18,4,-80]", 1);

    // test de base pour le trie
    struct stack* s1= NULL;
    initStack_sol(&s1);
    push_sol(&s1, 0);
    push_sol(&s1, -5);
    push_sol(&s1, 18);
    push_sol(&s1, 4);
    push_sol(&s1, -80);
    int res[] = {-80,-5,0,4,18};
    int i = 0;

    SANDBOX_BEGIN;
    sortStack(&s1);
    SANDBOX_END;

    struct stack* temp = s1;
    while (s1) {
        CU_ASSERT_EQUAL(s1->data,res[i]);
        if (s1->data != res[i]) return error(res, temp, 5);
        s1 = s1->next;
        i++;
    }
    free(s1);
}



void test3(){

    set_test_metadata("sort", "Test tri de [-1,-1,-1]", 1);
    // test pour le trie afin de voir si la stack contient les mêmes valeurs si l'étudiant auras une stack qui n'aura qu'un element dans sa stack triée en supprimant la duplication 
    struct stack* s2= NULL;
    initStack_sol(&s2);
    push_sol(&s2, -1);
    push_sol(&s2, -1);
    push_sol(&s2, -1);
    int res[] = {-1,-1,-1};
    int i = 0;

    SANDBOX_BEGIN;
    sortStack(&s2);
    SANDBOX_END;

    struct stack *temp = s2;

    while (s2) {
        CU_ASSERT_EQUAL(s2->data,res[i]);
        if (s2->data != res[i]) return error(res, temp, 3);
        s2 = s2->next;
        i++;
    }
    free(s2);
    
}


void test4(){
    set_test_metadata("sort", "Test tri de []", 1);
  
    // test quand la stack est vide pour la fonction trie
    struct stack* s3= NULL;
    initStack_sol(&s3);
    void* res  = NULL;

    SANDBOX_BEGIN;
    sortStack(&s3);
    SANDBOX_END;

    CU_ASSERT_EQUAL(NULL,res);
    if (res != NULL) push_info_msg("Your sorted stack should be NULL when the initial stack is NULL");
    free(s3);
    
}



void test5(){

    set_test_metadata("sort", "Test tri de [30,40,-50,50,60]", 1);

  // test pour la fonction trie afin de voir si la stack contient les mêmes valeurs si l'étudiant auras une stack qui n'aura qu'un element dans sa stack triée en supprimant la duplication 
    struct stack* s4= NULL;
    initStack_sol(&s4);
    push_sol(&s4, 30);
    push_sol(&s4, 40);
    push_sol(&s4, -50);
    push_sol(&s4, 50);
    push_sol(&s4, 60);

    int res[] = {-50,30,40,50,60};
    int i = 0;

    SANDBOX_BEGIN;
    sortStack(&s4);
    SANDBOX_END;

    struct stack *temp = s4;

    while (s4) {
        CU_ASSERT_EQUAL(s4->data,res[i]);
        if (s4->data != res[i]) return error(res, temp, 5);
        s4 = s4->next;
        i++;
    }
    free(s4);
    
}



void test6(){

    set_test_metadata("push", "Test pour push de [3,49,-3]", 1);

  // Fonction Push test
    struct stack* s5= NULL;
    initStack_sol(&s5);

    int ret = 0;

    SANDBOX_BEGIN;
    ret += push(&s5, 3);
    ret += push(&s5, 49);
    ret += push(&s5, -3);
    SANDBOX_END;

    CU_ASSERT_EQUAL(ret, 0);
    if (ret != 0) push_info_msg("You should return 0 when everything works fine");

    struct stack *temp = s5;

    int res[] = {-3,49,3};
    int i = 0;
    while (s5) {
        CU_ASSERT_EQUAL(s5->data,res[i]);
        if (s5->data != res[i]) return error(res, temp, 3);
        s5 = s5->next;
        i++;
    }
    free(s5);
}


void test7(){

    set_test_metadata("push", "Test pour Push de [8,19,13]", 1);
  // fonction push test
    struct stack* s6= NULL;

    initStack_sol(&s6);

    int ret = 0;

    SANDBOX_BEGIN;
    ret += push(&s6, 8);
    ret += push(&s6, 19);
    ret += push(&s6, 13);
    SANDBOX_END;

    CU_ASSERT_EQUAL(ret, 0);
    if (ret != 0) push_info_msg("You should return 0 when everything works fine");

    struct stack *temp = s6;

    int res[] = {13,19,8};
    int i = 0;
    while (s6) {
        CU_ASSERT_EQUAL(s6->data,res[i]);
        if (s6->data != res[i]) return error(res, temp, 3);
        s6 = s6->next;
        i++;
    }
    free(s6);
}


void test8(){

    set_test_metadata("push", "test pour Push de [1,2,3]", 1);
    // fonction push test
    struct stack* s7= NULL;
    initStack_sol(&s7);

    int ret = 0;

    SANDBOX_BEGIN;
    ret += push(&s7, 1);
    ret += push(&s7, 2);
    ret += push(&s7, 3);
    SANDBOX_END;

    CU_ASSERT_EQUAL(ret, 0);
    if (ret != 0) push_info_msg("You should return 0 when everything works fine");

    struct stack *temp = s7;
    int res[] = {3,2,1};
    int i = 0;
    while (s7) {
        CU_ASSERT_EQUAL(s7->data,res[i]);
        if (s7->data != res[i]) return error(res, temp, 3);
        s7 = s7->next;
        i++;
    }
    free(s7);
}



void test9(){

    set_test_metadata("push", "Test pour Push de [30,40,-50,50,60]", 1);

    // test quand la stack est vide
    struct stack* s8= NULL;
    initStack_sol(&s8);

    int ret = 0;

    SANDBOX_BEGIN;
    ret += push(&s8, 30);
    ret += push(&s8, 40);
    ret += push(&s8, -50);
    ret += push(&s8, 50);
    ret += push(&s8, 60);
    SANDBOX_END;

    CU_ASSERT_EQUAL(ret, 0);
    if (ret != 0) push_info_msg("You should return 0 when everything works fine");

    struct stack *temp = s8;
    int res[] = {60,50,-50,40,30};
    int i = 0;
    while (s8) {
        CU_ASSERT_EQUAL(s8->data,res[i]);
        if (s8->data != res[i]) return error(res, temp, 5);
        s8 = s8->next;
        i++;
    }
    free(s8);
}

void test10(){
    set_test_metadata("push", "Test pour push avec un malloc qui échoue", 1);

    struct stack *s = NULL;
    initStack_sol(&s);

    monitored.malloc = true;
    failures.malloc = FAIL_ALWAYS;

    int ret;
    SANDBOX_BEGIN;
    ret = push(&s, 1);
    SANDBOX_END;

    CU_ASSERT_EQUAL(ret, -1);
    if (ret != -1) push_info_msg("You have to return -1 if malloc fails");
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7, test8, test9, test10);
}
