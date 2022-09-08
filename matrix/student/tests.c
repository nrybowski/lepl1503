#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 100

char *str_list(list_t *list){
    if (list == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *template = "%d";
    char *ret = malloc(SIZE);
    strcpy(ret, "[");
    node_t *curr = list->first;
    for (int i = 0; i < list->size; i++){
        char temp[strlen(template)];
        sprintf(temp, template, curr->value);
        strcat(ret, temp);
        if (i != list->size -1) strcat(ret, ", ");
        curr = curr->next;
    }
    strcat(ret, "]");
    return ret;
}

char *str_matrix(int **matrix, int n, int m){
    if (matrix == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(4*SIZE);
    char *template = "%d";
    strcpy(ret, "[");
    for (int i = 0; i < n; i++){
        if (matrix[i] == NULL) strcat(ret, "NULL");
        else{
            strcat(ret, "[");
            for (int j = 0; j < m; j++){
                char temp[strlen(template)];
                sprintf(temp, template, *(*(matrix+i)+j));
                strcat(ret, temp);
                if (j != m - 1) strcat(ret, ", ");
            }
            strcat(ret, "]");
        }
        if (i != n - 1) strcat(ret, ", ");
    }
    strcat(ret, "]");
    return ret;
}

char *arr_str(int *arr, int n, int m)
{
    char *ret = malloc(4*SIZE);
    char *template = "%d";
    strcpy(ret, "[");

    for (int i = 0; i < n; i++){
        strcat(ret, "[");

        for (int j = 0; j < m; j++){
            char buffer[strlen(template)];
            sprintf(buffer, template, *((arr + i*m) + j));
            strcat(ret, buffer);
            if (j != m - 1) strcat(ret, ", ");
        }

        strcat(ret, "]");
        if (i != n - 1) strcat(ret, ", ");
    }
    strcat(ret, "]");
    return ret;
}
 

void error(int *exp, int **ret, list_t *init, int n, int m){
    char *template = _("Wrong returned matrix with list %s, n=%d, m=%d. Expected matrix was %s, but you returned %s");
    char buffer[strlen(template) + 9*SIZE];
    char *exp_str = arr_str(exp, n, m);
    char *ret_str = str_matrix(ret, n, m);
    char *list_str = str_list(init);
    sprintf(buffer, template, list_str, n, m, exp_str, ret_str);
    push_info_msg(buffer);
    free(exp_str);
    free(ret_str);
    free(list_str);
}

void check_matrix(int *exp, int **ret, list_t *init, int n, int m){
    CU_ASSERT_PTR_NOT_NULL(ret);
    if (ret == NULL) return error((int *) exp, ret, init, n, m);

    for (int i = 0; i < n; i++) {

        CU_ASSERT_PTR_NOT_NULL(ret[i]);
        if (ret[i] == NULL) return error((int *) exp, ret, init, n, m);

        for (int j = 0; j < m; j++) {

            CU_ASSERT_EQUAL(*((exp +i*m) + j), ret[i][j]);
            if (*(exp +i*n + j) != ret[i][j]) return error((int *) exp, ret, init, n, m);

        }
    }
}

void free_matrix(int **matrix, int n){
    for (size_t i = 0; i < n; i++)
    {
        free(*(matrix+i));
    }
    free(matrix);
}

void free_list(list_t *list){
    node_t *curr = list->first;
    for (size_t i = 0; i < list->size; i++)
    {
        node_t *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(list);
}

void test1() {

    set_test_metadata("transform", "Test basique pour matrice 3*3 avec liste de size 9", 1);
    // test basique pour matrice 3*3 avec liste de size 9
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int sol[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    int n = 3;
    int m = 3;
    int** matrix;

    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);

}

void test2() {
    set_test_metadata("transform", "Test basique pour matrice 3*2 avec liste de size 9", 1);
    // test basique pour matrice 3*2 avec liste de size 9
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int sol[3][2] = {{1, 2}, {3, 4}, {5, 6}};

    int n = 3;
    int m = 2;
    int** matrix;
    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);
}

void test3() {
    set_test_metadata("transform", "Test basique pour matrice 2*3 avec liste de size 9", 1);
    // test basique pour matrice 2*3 avec liste de size 9
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int sol[2][3] = {{1, 2, 3}, {4, 5, 6}};

    int n = 2;
    int m = 3;
    int** matrix;
    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);
}

void test4() {
    set_test_metadata("transform", "Test basique pour matrice 4*3 avec liste de size 9, chiffres manquants = -1", 1);
    // test basique pour matrice 4*3 avec liste de size 9, chiffres manquants = -1
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int sol[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {-1, -1, -1}};

    int n = 4;
    int m = 3;
    int** matrix;
    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);
}

void test5() {
    set_test_metadata("transform", "Test basique pour matrice 3*4 avec liste de size 9, chiffres manquants = -1", 1);
    // test basique pour matrice 3*4 avec liste de size 9, chiffres manquants = -1
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int sol[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, -1, -1, -1}};

    int n = 3;
    int m = 4;
    int** matrix;
    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);
}

void test6() {
    set_test_metadata("transform", "test avec lst->first = NULL, lst.size = 0", 1);

    // test avec lst->first = NULL, lst.size = 0
    list_t *lst = (list_t *) malloc(sizeof(list_t));
    lst->size = 0;
    lst->first = NULL;

    int sol[3][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};

    int n = 3;
    int m = 4;
    int** matrix;
    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    check_matrix((int *) sol, matrix, lst, n, m);

    free_matrix(matrix, n);
    free_list(lst);
}

void test7(){
    set_test_metadata("transform", "test avec malloc échouant", 1);

    list_t *lst = (list_t *) malloc(sizeof(list_t));
    node_t *current = (node_t *) malloc(sizeof(node_t));
    current->value = 1;
    lst->first = current;
    lst->size = 1;
    for (int i = 2; i < 10; ++i) {
        node_t *new = (node_t *) malloc(sizeof(node_t));
        new->value = i;
        current->next = new;
        current = current->next;
        lst->size++;
    }

    int n = 3;
    int m = 3;
    int** matrix;

    monitored.malloc = true;
    failures.malloc = 0x04;

    SANDBOX_BEGIN;
    matrix = linked_list_to_matrix(lst, n, m);
    SANDBOX_END;

    CU_ASSERT_EQUAL(matrix, NULL);
    if (matrix != NULL) push_info_msg("You should return NULL when malloc fails");

    free_list(lst);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7);
}
