#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int** linked_list_to_matrix_sol(list_t *lst, int n, int m){
    int** matrix = (int**) malloc(n * sizeof(int*));
    if (matrix == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc(m * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    node_t *current = lst->first;
    int count = 0;
    for (int i = 0; i < lst->size; i++)
    {
        if (i >= n*m) return matrix;
        matrix[count / m][count % m] = current->value;
        current = current->next;
        count++;
    }
    for (int i = count ; i < n*m; i++)
    {
        matrix[count / m][count % m] = -1;
        count++;
    }

    return matrix;
}
