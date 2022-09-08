#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <stdint.h>
#include "student_code_sol.h"
#include "../student_code.h"


void load_header_data_sol(FILE * input_file, file_t * ptr){
    fread(ptr, sizeof(uint8_t),10,input_file);
}

int compare_indexes_sol(const void * first, const void * second, void *ptr){
    uint8_t *grades = (uint8_t *)ptr;
    return -((grades[* (uint32_t*)first] - grades[* (uint32_t*)second]));
}

int make_ranking_sol(char * file_path, char * output_file){
    FILE * input_file = fopen(file_path, "r");
    
    if (input_file == NULL) return 1;

    struct file * infos = (struct file *) malloc(sizeof(file_t));
    if(infos == NULL) {
        fclose(input_file);
        return 2;
    }
    
    fread(infos, 1, 10,input_file);
    infos->nb_students=be32toh(infos->nb_students);
    infos->code=be16toh(infos->code);

    
    //printf("nb_students %d \n code %d \n  average_grade  %d \n median_grade %d \n max_grad %d \n min_grade %d \n", infos->nb_students,infos->code,infos->average_grade,
    //infos->median_grade,infos->max_grad,infos->min_grade);
    

    uint8_t * grades = (uint8_t *) malloc(1*infos->nb_students);
    if(grades == NULL) {
        free(infos);
        fclose(input_file);
        return 2;
    }
    uint32_t * nomas= (uint32_t *) malloc(4*infos->nb_students);
    if(nomas == NULL) {
        free(infos);
        free(grades);
        fclose(input_file);
        return 2;
    }
    
    fread(grades,sizeof(uint8_t),infos->nb_students,input_file);
    fread(nomas,sizeof(uint32_t),infos->nb_students,input_file);
    uint32_t i;
    for (i=0 ; i< infos->nb_students ; i++) {
        *(nomas+i)=be32toh(*(nomas+i));
    }

    if (fclose(input_file)!=0){
        free(infos);
        free(grades);
        free(nomas);
        return 3;
    }

    qsort_r((void *) nomas, infos->nb_students, sizeof(uint32_t), *compare_indexes,(void *) grades);
    for (i=0 ; i< infos->nb_students ; i++) {                        
        *(nomas+i)=htobe32(*(nomas+i));
    }
    free(grades);

    FILE * output = fopen(output_file,"r+");
    if (output==NULL){
        free(nomas);
        free(infos);
        return 4;
    }
    fwrite(nomas,sizeof(uint32_t),infos->nb_students,output);
    free(nomas);
    free(infos);
    if (fclose(output)!=0){
        return 5;
    }
    return 0;
};