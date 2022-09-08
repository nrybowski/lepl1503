#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

void leftOneTime(int array[], int n){

    int first = array[0];
    for (int i = 0; i < n - 1; i++) {
        array[i] = array[i + 1];
    }
    array[n-1] = first;
}



void leftNTime_sol(int array[], int r, unsigned int n){
    if(r < 0) return;
    for (int i = 0; i < r; i++) {
        leftOneTime(array, n);
    }
}
