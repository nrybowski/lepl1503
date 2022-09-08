#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int CleanMyStructure_sol(int NOMA, int oldNumberOfCourses, int newNumberOfCourses, data* datas){

    if (datas->number == NULL){
        datas->number = (int*) malloc(sizeof(int));
        if (datas->number == NULL){
            return -1;
        }
    }

    *(datas->number) = NOMA;

    if (datas->matrix != NULL){
        for (int i = 0; i < oldNumberOfCourses; i++){
            free(datas->matrix[i]);
        }
        free(datas->matrix);
    }

    datas->matrix = (int**) malloc(sizeof(int*)*newNumberOfCourses);
    if (datas->matrix == NULL){
        return -1;
    }
    for (int i = 0; i < newNumberOfCourses; i++){
        *(datas->matrix+i) =(int *) malloc(2*sizeof(int));
        if (datas->matrix[i] == NULL){
            return -1;
        }
    }

    return 0;

}
