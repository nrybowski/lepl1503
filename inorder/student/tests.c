#include <stdlib.h>
#include "student_code.h"

#include "../../course/common/student/CTester/CTester.h"

tree_t *insertNode(tree_t *tree, int value){
    if (tree == NULL){
        tree_t *new = malloc(sizeof(tree_t));
        new->number_elements = 1;
        new->left = NULL;
        new->right = NULL;
        new->value = value;
        return new;
    }
    tree->number_elements++;
    if (value >= tree->value && tree->right != NULL){
        insertNode(tree->right, value);
        return tree;
    }
    if (value < tree->value && tree->left != NULL){
        insertNode(tree->left, value);
        return tree;
    }
    tree_t *new = malloc(sizeof(tree_t));
    new->number_elements = 1;
    new->left = NULL;
    new->right = NULL;
    new->value = value;
    if (value >= tree->value && tree->right == NULL){
        tree->right = new;
        return tree;
    }else{
        tree->left = new;
        return tree;
    }
}

void freeTree(tree_t *tree){
    if (tree == NULL) return;
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}

tree_t *createTree(int *values, int number){
    tree_t *tree = NULL;
    for (int i = 0; i < number; i++)
    {
        tree = insertNode(tree, *(values+i));
    }
    return tree;
    
}

int flag = 1;

char *array_to_string(int *array, int nbElem){
    char *ret = malloc(nbElem*6 + 2);
    strcpy(ret, "[");
    for (int i = 0; i< nbElem; i++){
        char *temp = i == nbElem - 1 ? "%d" : "%d, ";
        char msg[strlen(temp)];
        sprintf(msg, temp, *(array+i));
        strcat(ret, msg);
    }
    strcat(ret, "]");
    return ret;
}

void logError(int *exp, int *ret, int nbElem){
    char *err = _("You didn't travel correctly the tree. The expected array is %s, while you returned %s");
    char errmsg[strlen(err) + 200];
    char *exp_str = array_to_string(exp, nbElem);
    char *ret_str = array_to_string(ret, nbElem);
    sprintf(errmsg, err, exp_str, ret_str);
    push_info_msg(errmsg);
    flag = 0;
    free(exp_str);
    free(ret_str);
}

void logErrorMalloc(int nbMalloc, int nbFree){
    char *err = _("You didn't free all your memory : called malloc %d times and free %d times");
    char errmsg[strlen(err)];
    sprintf(errmsg,err, nbMalloc, nbFree);
    push_info_msg(errmsg);
    flag = 0;
}



void test1(){

    set_test_metadata("inorder", _("Test in-order for a simple balanced binary tree"), 1);

    int values[] = {1,0,2};  

    int number = 3;

    tree_t *t = createTree(values, number);
    int expected[] = {0,1,2};

    int *ret = NULL;

    flag = 1;

    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;
    

    CU_ASSERT_EQUAL(stats.malloc.called - stats.free.called, 1);    // check if all memory was freed (should only remain the malloc of the return value)
    if (stats.malloc.called - stats.free.called != 1) {
        logErrorMalloc(stats.malloc.called, stats.free.called);
    }

    for (int i = 0; i < t->number_elements; i++)
    {
     
        if (ret+i){
            CU_ASSERT_EQUAL(*(ret+i), expected[i]);
            if (*(ret+i) != expected[i]){
                logError(expected, ret, number);
                break;
            } ;
        }

    }

    freeTree(t);
    if (ret) free(ret);

}


void test2(){

    set_test_metadata("inorder", _("Test in-order linear binary tree (only right child)"), 1);

    int values[] = {0,5,10};

    int number = 3;

    tree_t *t = createTree(values, number);
    int expected[] = {0,5,10};
    int *ret;

    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(stats.malloc.called - stats.free.called, 1);    // check if all memory was freed (should only remain the malloc of the return value)
    if (stats.malloc.called - stats.free.called != 1) {
        logErrorMalloc(stats.malloc.called, stats.free.called);
    }
    for (int i = 0; i < t->number_elements; i++)
    {
        CU_ASSERT_EQUAL(*(ret+i), expected[i]);
        if (*(ret+i) != expected[i]){
            logError(expected, ret, number);
            break;
        }
    }

    freeTree(t);
    free(ret);

    if (flag){
        set_tag("q1");
    }
    
}

void test3(){

    set_test_metadata("inorder", _("Test in-order linear binary tree (only left child)"), 1);

    int values[] = {15,0,-3}; 
    int number = 3;


    tree_t *t = createTree(values, number);
    int expected[] = {-3,0,15};

    int *ret;

    monitored.malloc = true;
    monitored.free = true;
    
    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(stats.malloc.called - stats.free.called, 1);    // check if all memory was freed (should only remain the malloc of the return value)
    if (stats.malloc.called - stats.free.called != 1) {
        logErrorMalloc(stats.malloc.called, stats.free.called);
    }
    for (int i = 0; i < t->number_elements; i++)
    {
        CU_ASSERT_EQUAL(*(ret+i), expected[i]);
        if (*(ret+i) != expected[i]){
            logError(expected, ret, number);
            break;
        }
    }

    freeTree(t);
    free(ret);

    if (flag){
        set_tag("q1");
    }
    
}

void test4(){

    set_test_metadata("inorder", _("Test in-order binary tree (with missing right/left children)"), 1);

    int values[] = {15, 0, 22, -3, 1, 20, 21}; 
    int number = 7;


    tree_t *t = createTree(values, number);
    int expected[] = {-3,0,1, 15, 20, 21, 22};

    int *ret;

    monitored.malloc = true;
    monitored.free = true;
    
    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(stats.malloc.called - stats.free.called, 1);    // check if all memory was freed (should only remain the malloc of the return value)
    if (stats.malloc.called - stats.free.called != 1) {
        logErrorMalloc(stats.malloc.called, stats.free.called);
    }
    for (int i = 0; i < t->number_elements; i++)
    {
        CU_ASSERT_EQUAL(*(ret+i), expected[i]);
        if (*(ret+i) != expected[i]){
            logError(expected, ret, number);
            break;
        }
    }

    freeTree(t);
    free(ret);

    if (flag){
        set_tag("q1");
    }
    
}

void test5(){

    set_test_metadata("inorder", _("Test in-order binary tree (random tree)"), 1);
    srand( time( NULL ) );
    

    int values[1000];
    int expected[1000];
    int number = 1000;

    for (int i = 0; i < number; i++)
    {
        expected[i] = 0;
    }

    for (int i = 0; i < number; i++)
    {
        int random = rand() % number;
        values[i] = random;
        expected[random]++;
    }
    

    tree_t *t = createTree(values, number);

    int *ret;

    monitored.malloc = true;
    monitored.free = true;
    
    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(stats.malloc.called - stats.free.called, 1);    // check if all memory was freed (should only remain the malloc of the return value)
    if (stats.malloc.called - stats.free.called != 1) {
        logErrorMalloc(stats.malloc.called, stats.free.called);
    }

    for (int i = 0; i < t->number_elements; i++)   // check if all elements appeared the right number of times
    {
        CU_ASSERT(expected[*(ret+i)] > 0);
        if (expected[*(ret+i)] <= 0){
            flag = 0;
        }
        expected[*(ret+i)]--;
    }

    for (int i = 0; i < t->number_elements - 1; i++)   // check if all elements appeared in the expected order
    {
        CU_ASSERT(*(ret+i) <= *(ret+i+1));
        if (*(ret+i) > *(ret+i+1)){
            flag = 0;
        }
    }

    freeTree(t);

    free(ret);

    if (flag){
        set_tag("q1");
    }
    
}

void test6(){

    set_test_metadata("inorder", _("Test in-order binary tree with failed malloc"), 1);

    int a[] = {0,1,2};
    int number = 3;

    tree_t *t = createTree(a, number);

    monitored.malloc = true;
    monitored.free = true;

    failures.malloc = FAIL_ALWAYS;              // make malloc fail

    flag = 1;

    int *res = &flag;
    
    SANDBOX_BEGIN;
    res = in_order(t);
    SANDBOX_END;

    failures.malloc = 0;

    CU_ASSERT(res == NULL);
    if (res!=NULL){
        flag = 0;
    }

    free(res);
    freeTree(t);

    if(flag){
        set_tag("q1");
    }
}


void test7(){

    set_test_metadata("inorder", _("Test in-order binary tree with NULL tree"), 1);
    

    tree_t *t = NULL;

    monitored.malloc = true;
    monitored.free = true;

    failures.malloc = FAIL_ALWAYS;


    flag = 1;

    int *ret = &flag;

    SANDBOX_BEGIN;
    ret = in_order(t);
    SANDBOX_END;

    CU_ASSERT( ret == NULL);
    CU_ASSERT(stats.malloc.called == 0);
    CU_ASSERT(stats.free.called == 0);
    if (ret != NULL || stats.malloc.called != 0 || stats.free.called  != 0) flag=0;

    if (ret != NULL){
        push_info_msg("You returned a pointer different from NULL");
    }

    if (stats.malloc.called != 0) push_info_msg("Why did you call any malloc ?");

    if (stats.free.called != 0) push_info_msg("How did you even free something ?");

    if (flag){
        set_tag("q1");
    }
}


int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7);
}
