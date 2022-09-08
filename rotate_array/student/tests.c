#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

char *str_array(int *array, int n){
    if (array == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(4*n);
    char *template = "%d";
    strcpy(ret, "[");
    for (size_t i = 0; i < n; i++)
    {
        char temp[strlen(template)];
        sprintf(temp, template, *(array+i));
        strcat(ret, temp);
        if (i != n - 1) strcat(ret, ", ");
    }
    strcat(ret, "]");
    return ret;
}

void error(int *ret, int n, int r, char *init){
    char *template = _("Wrong return value. With the array %s and r=%d, you returned %s");
    char msg[strlen(template) + 8*n];
    char *ret_str = str_array(ret, n);
    sprintf(msg, template, init, r, ret_str);
    push_info_msg(msg);
    free(ret_str);
}

void check(int *exp, int *ret, int n, int r, char *init){
    for (size_t i = 0; i < n; i++)
    {
        CU_ASSERT_EQUAL(*(exp+i), *(ret+i));
        if (*(exp+i) != *(ret+i)) return error(ret, n, r, init);
    }
    free(init);
}

void test1(){
    set_test_metadata("left_rotate","Test de leftNTime pour [1, 2, 3, 4, 5,6,7] et r = 2 ",1);
    int arr[] = { 1, 2, 3, 4, 5,6,7 };
    int rep[] = {3,4,5,6,7,1,2};
    int r = 2;
    int n = sizeof(arr)/sizeof(arr[0]);
    char *init = str_array(arr, n);
    SANDBOX_BEGIN;
    leftNTime(arr, r, n);
    SANDBOX_END;
    check(rep, arr, n, r, init);
}
    // cas classique
void test2(){
    set_test_metadata("left_rotate","Test de leftNTime pour [1, 2, 3, 4, 5] et r = 1 ",1);

    int arr2[] = { 1, 2, 3, 4, 5 };
    int rep2[] = { 2, 3, 4, 5, 1};
    int r2 = 1;
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    char *init = str_array(arr2, n2);
    SANDBOX_BEGIN;
    leftNTime(arr2, r2, n2);
    SANDBOX_END;

    check(rep2, arr2, n2, r2, init);
 
}

// cas classique
void test3(){

    set_test_metadata("left_rotate","Test de leftNTime pour [-1, -2, -3, -4, 5] et r = 1 ",1);

    int arr3[] = { -1, -2, -3, -4, 5 };
    int rep3[] = { -2, -3, -4, 5, -1};
    int r3 = 1;
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    char *init = str_array(arr3, n3);
    SANDBOX_BEGIN;
    leftNTime(arr3, r3, n3);
    SANDBOX_END;
    check(rep3, arr3, n3, r3, init);
 
}
// valeur de r < 0
void test4(){

    set_test_metadata("left_rotate","Test de leftNTime pour [-1, -2, -3, -4, 5 ] et r = -1",1);

    int arr4[] = { -1, -2, -3, -4, 5 };
    int rep4[] = { -1, -2, -3, -4, 5 };
    int r4 = -1;
    int n4 = sizeof(arr4)/sizeof(arr4[0]);
    char *init = str_array(arr4, n4);
    SANDBOX_BEGIN;
    leftNTime(arr4, r4, n4);
    SANDBOX_END;
    check(rep4, arr4, n4, r4, init);
 
}

 
// test pour r>1
void test5(){

    set_test_metadata("left_rotate","Test de leftNTime pour [-1, -2, -3, -4, 5 ] et r = 2",1);

    int arr5[] = { -1, -2, -3, -4, 5 };
    int rep5[] = { -3,-4,5,-1,-2};
    int r5 = 2;
    int n5 = sizeof(arr5)/sizeof(arr5[0]);
    char *init = str_array(arr5, n5);
    SANDBOX_BEGIN;
    leftNTime(arr5, r5, n5);
    SANDBOX_END;
    check(rep5, arr5, n5, r5, init);
 
}
 
// test pour r>2
void test6(){

    set_test_metadata("left_rotate","Test de leftNTime pour [-1, -2, -3, -4, 5 ] et r = 4",1);

    int arr6[] = { -1, -2, -3, -4, 5 };
    int rep6[] = { 5,-1,-2,-3,-4};
    int r6 = 4;
    int n6 = sizeof(arr6)/sizeof(arr6[0]);
    char *init = str_array(arr6, n6);
    SANDBOX_BEGIN;
    leftNTime(arr6, r6, n6);
    SANDBOX_END;
    check(rep6, arr6, n6, r6, init);
 
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6);
}
