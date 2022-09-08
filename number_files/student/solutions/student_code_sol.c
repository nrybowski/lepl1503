#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int get_number_of_files_sol (file_t * file) {
    if (file == NULL) 
    {
        return -1;
    }
    if (file->folder == 0)
    {
        return 1;
    }
    else {
        int n_files = 0;
        for (int i = 0; i < file->n_files; i++) {
            n_files += get_number_of_files(file->files[i]);
        }
        return n_files;
    }
}
