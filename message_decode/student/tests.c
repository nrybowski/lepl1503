#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 200

int isAccepted(char c){
    return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c==' ');
}

//Crée une liste de noeuds contenant dess nombres aléatoires entre 0 et 127.
node_t* random_nbr(int size, char **exp){
    int lower = 0; int upper = 127; 
    *exp = malloc(size);
    int index = 0;

    node_t* curr = NULL;
    node_t * ret = NULL;
    for (size_t i = 0; i < size; i++)
    {
        char rng = (rand() % (upper - lower + 1)) + lower;
        if (isAccepted(rng)){
            *((*exp) + index) = rng;
            index++;
        }
        if (!ret){
            ret = malloc(sizeof(node_t));
            ret->value = rng;
            ret->next = NULL;
            curr = ret;
        }else{
            node_t *new = malloc(sizeof(node_t));
            new->value = rng;
            new->next = NULL;
            if (curr) curr->next = new;
            curr = new;
        }
    }
    *((*exp) + index) = '\0';
    return ret;
}

node_t *make_list(int *data, int number, char **expected){
    *expected = malloc(number);
    int index = 0;
    node_t *curr = NULL;
    node_t *ret = NULL;
    for (size_t i = 0; i < number; i++)
    {
        if (isAccepted(data[i])){
            *((*expected) + index) = (char) data[i];
            index++;
        } 
        if (!ret){
            ret = malloc(sizeof(node_t));
            ret->value = data[i];
            ret->next = NULL;
            curr = ret;
        }else{
            node_t *new = malloc(sizeof(node_t));
            new->value = data[i];
            new->next = NULL;
            if (curr) curr->next = new;
            curr = new;
        }
    }
    *((*expected) + index) = '\0';
    return ret;
}

void free_list(node_t *list){
    if (!list) return;
    node_t *temp = list->next;
    free(list);
    free_list(temp);
}

char *str_list(node_t* node){
    if (node == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(SIZE);
    char *template = "%c";
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

void error(char *ret, char *exp, node_t *init){
    char *template = _("Wrong return value. With the initial list %s, the expected return is %s, while you returned %s");
    char msg[strlen(template) + 3*SIZE];
    char *ret_str = ret ? ret : "NULL";
    char *exp_str = exp ? exp : "NULL";
    char *init_str = str_list(init);
    sprintf(msg, template, init_str,exp_str, ret_str);
    push_info_msg(msg);
    free(init_str);
    if (ret) free(ret);
    if (exp) free(exp);
    if (init) free_list(init);
}

void compare(char *ret, char *exp, node_t *init){
    if (exp == NULL){
        CU_ASSERT_EQUAL(ret, NULL);
        if (ret != NULL) return error(ret, exp, init);
    }else{
        CU_ASSERT_PTR_NOT_NULL(ret);
        if (ret == NULL) return error(ret, exp, init);
        CU_ASSERT_STRING_EQUAL(ret,exp);
        if (strcmp(ret, exp) != 0) return error(ret, exp, init);
    }

    if (ret) free(ret);
    if (exp) free(exp);
    if (init) free_list(init);
}


void test1(){
    set_test_metadata("decode", "test message NULL", 1);
    // test si liste nulle
    node_t* node = NULL;
    int size_mess = 0;
    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(node,size_mess);
    SANDBOX_END;
    char* expected = NULL;

    if (res != expected) error(res, expected, node);
}
    
void test2(){

    set_test_metadata("decode", "test helloworld", 1);
    // test de base minimaliste

    int size_mess = 16;
    int data[] = {104,45,101,108,108,33,111,41,32,119,111,114,108,40,38,100};
    char* expected = NULL;
    node_t *final = make_list(data, size_mess, &expected);

    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;
    compare(res, expected, final);
}

void test3(){

    set_test_metadata("decode", "test oublie du \\0", 1);
    // test oublie du "\0"
    node_t* node = NULL;
    node_t* final = NULL;
    int size_mess = 16;
    int data[] = {104,45,101,108,108,33,111,41,32,119,111,114,108,40,38,100};

    for (size_t i = 0; i < size_mess; i++)
    {
        node = malloc(sizeof(node_t));
        if (!final) final = node;
        node->value = data[i];
        node->next = NULL;
        node = node->next;
    }

    char* expected = "hello world";
    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;
    CU_ASSERT_STRING_NOT_EQUAL(res, expected);
    if (strcmp(res, expected) == 0) push_info_msg("Don't forget to add a \\0 at the end of your string");
    free_list(final);
    free(res);
    
}

void test4(){

    set_test_metadata("decode", "test random 1", 1);
    // test random 1
    int upper = 15; int lower = 10;
    int size_mess = (rand() % (upper - lower + 1)) + lower;
    char* expected = NULL;
    node_t* final = random_nbr(size_mess, &expected);
    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;

    compare(res, expected, final);

}


void test5(){
    set_test_metadata("decode", "test random 2", 1);
    
    int upper = 20; 
    int lower = 15;
    int size_mess = (rand() % (upper - lower + 1)) + lower;
    char* expected = NULL;
    node_t* final = random_nbr(size_mess, &expected);
    char* res = NULL;

    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;
    
    compare(res, expected, final);
    
}

void test6(){
    set_test_metadata("decode", "test oubli de l'espace", 1);

  // test oublie de l'espace
  
    int size_mess = 16;
    int data[] = {104,45,101,108,108,33,111,41,32,119,111,114,108,40,38,100};
    char* expected = NULL;
    node_t* final = make_list(data, size_mess, &expected);

    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;

    compare(res, expected, final);

}

void test7(){
    set_test_metadata("decode", "test malloc fail", 1);

    int size_mess = 16;
    int data[] = {104,45,101,108,108,33,111,41,32,119,111,114,108,40,38,100};
    char* expected = NULL;
    node_t* final = make_list(data, size_mess, &expected);

    monitored.malloc = true;
    failures.malloc = FAIL_ALWAYS;

    char* res = NULL;
    SANDBOX_BEGIN;
    res = filter(final,size_mess);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, NULL);
    if (res) push_info_msg("You should return NULL when malloc fails");
    free_list(final);
    free(expected);
    free(res);
}

int main(int argc,char** argv){
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7);
}

