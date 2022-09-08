#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

typedef enum error_type{MALLOC, FREE} error_t;

char *errMsg[] = {"malloc", "free"};

void error_mf(int nb, int exp, error_t e){
    char *template = _("Wrong number of %s. You should call %s %d times, but you called it %d times");
    char msg[strlen(template) + 20];
    sprintf(msg, template, errMsg[e], errMsg[e], exp, nb);
    push_info_msg(msg);
}

int check_malloc(int nb, int exp){
    CU_ASSERT_EQUAL(nb, exp);
    if (nb != exp) {
        set_tag("failed");
        error_mf(nb, exp, MALLOC);
        return 1;
    }
    return 0;
}

int check_free(int nb, int exp){
    CU_ASSERT_EQUAL(nb, exp);
    if (nb !=  exp){
        set_tag("failed");
        error_mf(nb, exp, FREE);
        return 1;
    } 
    return 0;
}

void test1(){
    //test basique, on teste que les mallocs marchent bien

    set_test_metadata("clean", "Test avec number = NULL et matrix = NULL", 1);

    data* datasIn = (data*) malloc(sizeof(data));
    datasIn->number = NULL;
    datasIn->matrix = NULL;
    int oldnombreDeCours = 0;
    int newnombreDeCours = 3;
    int noma = 21352100;

    int check;

    monitored.malloc = true;
    monitored.free = true;

    int exp_malloc = 1 + 3 + 1;

    int exp_free = 0;
    
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    if (check_malloc(stats.malloc.called, exp_malloc) != 0) return;
    if (check_free(stats.free.called, exp_free) != 0) return;

    CU_ASSERT_EQUAL(check,0);
    if (check != 0) push_info_msg("Wrong returned value");

    CU_ASSERT(malloced(datasIn->number))
    if (!malloced(datasIn->number)) return push_info_msg("You didn't malloc the space necessary for the number");  

    if (datasIn->number != NULL){
        CU_ASSERT_EQUAL(*(datasIn->number),21352100);
        if (*(datasIn->number) != 21352100) push_info_msg("You didn't update correctly the noma");
    }

    CU_ASSERT(malloced(datasIn->matrix))
    if (!malloced(datasIn->matrix))  return push_info_msg("You didn't malloc the space necessary for the matrix");  

    for (int i = 0; i < newnombreDeCours; i++){
        CU_ASSERT(malloced(datasIn->matrix[i]));      
        if (!malloced(datasIn->matrix[i]))  return push_info_msg("You didn't malloc the space necessary for the rows of the matrix");
    }

    for (int i = 0; i < newnombreDeCours; i++){
        free(datasIn->matrix[i]);
    }
    free(datasIn->matrix);
    free(datasIn->number);
    free(datasIn);

}
    
void test2(){
    set_test_metadata("clean", "Test avec number != NULL et matrix = NULL", 1);

    data* datasIn = (data*) malloc(sizeof(data));
    int* oldnoma = (int*) malloc(sizeof(int));
    *oldnoma = 58882000;
    datasIn->number = oldnoma;
    datasIn->matrix = NULL;
    int oldnombreDeCours = 0;
    int newnombreDeCours = 3;
    int noma = 21352100;

    monitored.malloc = true;
    monitored.free = true;

    int exp_malloc =  newnombreDeCours + 1;
    int exp_free = 0;

    int check;
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    if (check_malloc(stats.malloc.called, exp_malloc) != 0) return;
    if (check_free(stats.free.called, exp_free) != 0) return;

    CU_ASSERT_EQUAL(check,0);
    if (check != 0) push_info_msg("Wrong returned value");

    CU_ASSERT_EQUAL(*(datasIn->number),21352100);
    if (*(datasIn->number) != 21352100) push_info_msg("You didn't update correctly the noma");

    CU_ASSERT(malloced(datasIn->matrix))
    if (!malloced(datasIn->matrix))  return push_info_msg("You didn't malloc the space necessary for the matrix");    

    for (int i = 0; i < newnombreDeCours; i++){
        CU_ASSERT(malloced(datasIn->matrix[i]));   
        if (!malloced(datasIn->matrix[i]))  return push_info_msg("You didn't malloc the space necessary for the rows of the matrix");             
    }

    for (int i = 0; i < newnombreDeCours; i++){
        free(datasIn->matrix[i]);
    }
    free(datasIn->matrix);
    free(datasIn->number);
    free(datasIn);
    
}

void test3(){

    set_test_metadata("clean", "Test avec number = NULL et matrix != NULL", 1);
    //test basique, on teste que le cas matrix != NULL marche bien plus precisement les free de la matrice

    data* datasIn = (data*) malloc(sizeof(data));
    datasIn->number = NULL;
    int oldnombreDeCours = 3;
    int newnombreDeCours = 3;
    int** matrice = (int **) malloc(sizeof(int*)*oldnombreDeCours);
    for (int i = 0; i < oldnombreDeCours; i++){
        *(matrice+i) = (int*) malloc(sizeof(int)*2);
    }

    matrice[0][0] = 0;
    matrice[0][1] = 5;
    matrice[1][0] = 1;
    matrice[1][1] = 9;
    matrice[2][0] = 2;
    matrice[2][1] = 12;
    datasIn->matrix = matrice;
    int noma = 21352100;

    monitored.malloc = true;
    monitored.free = true;

    int exp_malloc = 1 + 1 + 3;
    int exp_free =  oldnombreDeCours + 1;

    int check;
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    if (check_malloc(stats.malloc.called, exp_malloc) != 0) return;
    if (check_free(stats.free.called, exp_free) != 0) return;

    CU_ASSERT_EQUAL(check,0);
    if (check != 0) push_info_msg("Wrong returned value");

    CU_ASSERT(malloced(datasIn->number))
    if (!malloced(datasIn->number)) return push_info_msg("You didn't malloc the space necessary for the number");  

    if (datasIn->number != NULL){
        CU_ASSERT_EQUAL(*(datasIn->number),21352100);
        if (*(datasIn->number) != 21352100) push_info_msg("You didn't update correctly the noma");
    }

        CU_ASSERT(malloced(datasIn->matrix))
    if (!malloced(datasIn->matrix))  return push_info_msg("You didn't malloc the space necessary for the matrix");  

    for (int i = 0; i < newnombreDeCours; i++){
        CU_ASSERT(malloced(datasIn->matrix[i]));  
        if (!malloced(datasIn->matrix[i]))  return push_info_msg("You didn't malloc the space necessary for the rows of the matrix");         
    }

    for (int i = 0; i < newnombreDeCours; i++){
        free(datasIn->matrix[i]);
    }
    free(datasIn->matrix);
    free(datasIn->number);
    free(datasIn);
    
}

void test4(){

    set_test_metadata("clean", "Test complet avec number != NULL et matrix != NULL", 1);
    //test complet, on prends en considération un cas réel

    data* datasIn = (data*) malloc(sizeof(data));
    int* oldnoma = (int*) malloc(sizeof(int));
    *oldnoma = 58882000;
    datasIn->number = oldnoma;
    int oldnombreDeCours = 6;
    int newnombreDeCours = 5;
    int** matrice = (int **) malloc(sizeof(int*)*oldnombreDeCours);
    for (int i = 0; i < oldnombreDeCours; i++){
        *(matrice+i) = (int*) malloc(sizeof(int)*2);
    }

    matrice[0][0] = 1101;
    matrice[0][1] = 5;
    matrice[1][0] = 1201;
    matrice[1][1] = 9;
    matrice[2][0] = 1803;
    matrice[2][1] = 12;
    matrice[3][0] = 1503;
    matrice[3][1] = 20;
    matrice[4][0] = 1402;
    matrice[4][1] = 18;
    matrice[5][0] = 1210;
    matrice[5][1] = 14;
    datasIn->matrix = matrice;
    int noma = 25668952;

    monitored.malloc = true;
    monitored.free = true;

    int exp_free = oldnombreDeCours + 1;
    int exp_malloc = newnombreDeCours + 1;

    int check;
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    if (check_malloc(stats.malloc.called, exp_malloc) != 0) return;
    if (check_free(stats.free.called, exp_free) != 0) return;

    CU_ASSERT_EQUAL(check,0);
    if (check != 0) push_info_msg("Wrong returned value");

    CU_ASSERT_EQUAL(*(datasIn->number),25668952);
    if (*(datasIn->number) != 25668952) push_info_msg("You didn't update correctly the noma");

    CU_ASSERT(malloced(datasIn->matrix))
    if (!malloced(datasIn->matrix))  return push_info_msg("You didn't malloc the space necessary for the matrix");  

    for (int i = 0; i < newnombreDeCours; i++){
        CU_ASSERT(malloced(datasIn->matrix[i]));    
        if (!malloced(datasIn->matrix[i]))  return push_info_msg("You didn't malloc the space necessary for the rows of the matrix");          
    }

    for (int i = 0; i < newnombreDeCours; i++){
        free(datasIn->matrix[i]);
    }
    free(datasIn->matrix);
    free(datasIn->number);
    free(datasIn);
    
}

void test5(){

    set_test_metadata("clean", "Test 5 avec number = 00000000 et matrix vide", 1);
    //test avec matrice vide et NOMA = 00000000

    data* datasIn = (data*) malloc(sizeof(data));
    int* oldnoma = (int*) malloc(sizeof(int));
    *oldnoma = 00000000;
    int oldnombreDeCours = 10;
    int newnombreDeCours = 12;
    datasIn->number = oldnoma;
    int** matrice = (int **) malloc(sizeof(int*)*oldnombreDeCours);
    for (int i = 0; i < oldnombreDeCours; i++){
        *(matrice+i) = (int*) malloc(sizeof(int)*2);
    }

    datasIn->matrix = matrice;
    int noma = 54665222;

    monitored.malloc = true;
    monitored.free = true;

    int exp_free = oldnombreDeCours + 1;
    int exp_malloc = newnombreDeCours + 1;

    int check;
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    if (check_malloc(stats.malloc.called, exp_malloc) != 0) return;
    if (check_free(stats.free.called, exp_free) != 0) return;

    CU_ASSERT_EQUAL(check,0);
    if (check != 0) push_info_msg("Wrong returned value");
    
    CU_ASSERT_EQUAL(*(datasIn->number),54665222);
    if (*(datasIn->number) != 54665222) push_info_msg("You didn't update correctly the noma");

    CU_ASSERT(malloced(datasIn->matrix))
    if (!malloced(datasIn->matrix))  return push_info_msg("You didn't malloc the space necessary for the matrix");  

    for (int i = 0; i < newnombreDeCours; i++){
        CU_ASSERT(malloced(datasIn->matrix[i]));    
        if (!malloced(datasIn->matrix[i]))  return push_info_msg("You didn't malloc the space necessary for the rows of the matrix");         
    }
    

    for (int i = 0; i < newnombreDeCours; i++){
        free(datasIn->matrix[i]);
    }
    free(datasIn->matrix);
    free(datasIn->number);
    free(datasIn);
    
}

void test6(){

    set_test_metadata("clean", "Test avec malloc qui échoue", 1);

    data* datasIn = (data*) malloc(sizeof(data));
    datasIn->number = NULL;
    datasIn->matrix = NULL;
    int oldnombreDeCours = 0;
    int newnombreDeCours = 3;
    int noma = 21352100;

    monitored.malloc = true;
    failures.malloc = FAIL_ALWAYS;

    int check;
    SANDBOX_BEGIN;
    check = CleanMyStructure(noma,oldnombreDeCours,newnombreDeCours,datasIn);
    SANDBOX_END;

    CU_ASSERT_EQUAL(check,-1);
    if (check != -1){
        set_tag("failed");
        return push_info_msg("You don't return -1 when malloc fails");
    } 
    free(datasIn);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6);
}
