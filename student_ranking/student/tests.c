#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

//#define _GNU_SOURCE

int compare_binary_files(FILE *reference, FILE *evaluated) { 
    uint64_t idx=0;
    int r=1;
    int e=1;
    while (r==e && r!=EOF){
        r = getc(reference);
        e= getc(evaluated);
        idx++;
    }

    if (e == r) {
        printf("files are identical \n");
        return 0;  
    } else
    if (r == EOF) {
        printf("Student file is larger than reference file, the first %lu bytes are identical\n", idx);
        return 1;
    } else
    if (e == EOF) {
        printf("Student file is included in reference file but is too short, the first %lu bytes are identical\n", idx);
        return 2;
    } else {
        printf("Files differ at position %lu: 0x%02X <> 0x%02X\n", idx, r, e);
        return 3;
    }
}

uint64_t get_size(char * file){
    
    FILE * f = fopen(file,"r");
    if (f == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
    fseek(f, 0L, SEEK_END);
    uint64_t f_size = ftell(f);
    fclose(f);
    return f_size;
}

void test_compare_indexes_1(){
  set_test_metadata("compare_indexes","Test d'un nombre pair de nomas pour des notes aléatoires",1);
  uint32_t res[] = {0, 5, 1, 7, 9, 4, 3, 6, 2, 8};
  uint32_t nomas[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  uint8_t grades[] = {93, 83, 31, 45, 66, 92, 33, 79, 3, 76};
  SANDBOX_BEGIN;
  qsort_r((void *) nomas, 10, sizeof(uint32_t), *compare_indexes,(void *) grades);
  SANDBOX_END;
  CU_ASSERT_EQUAL(0, memcmp(nomas, res, 10));
}

void test_compare_indexes_2(){
   set_test_metadata("compare_indexes","Test d'un nombre impair de nomas pour des notes aléatoires",1);
  uint32_t res[] = {0, 5, 1, 7, 4, 3, 6, 2, 8};
  uint32_t nomas[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  uint8_t grades[] = {93, 83, 31, 45, 66, 92, 33, 79, 3};
  SANDBOX_BEGIN;
  qsort_r((void *) nomas, 9, sizeof(uint32_t), *compare_indexes,(void *) grades);
  SANDBOX_END;
  CU_ASSERT_EQUAL(0, memcmp(nomas, res, 9));
}

void test_compare_indexes_3(){
   set_test_metadata("compare_indexes","Test de nomas triés du plus bas au plus haut",1);
  uint32_t res[] = {9,8,7,6,5,4,3,2,1,0};
  uint32_t nomas[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,9};
  uint8_t grades[] = {10,20,30,40,50,60,70,80,90,100};
  SANDBOX_BEGIN;
  qsort_r((void *) nomas, 10, sizeof(uint32_t), *compare_indexes,(void *) grades);
  SANDBOX_END;
  CU_ASSERT_EQUAL(0, memcmp(nomas, res, 10));
}

void test_compare_indexes_4(){
  set_test_metadata("compare_indexes","Test de nomas déjà trié du plus haut score au plus bas",1);
  uint32_t res[] = {0,1,2,3,4,5,6,7,8,9};
  uint32_t nomas[] = {0, 1, 2, 3, 4, 5, 6, 7, 8,9};
  uint8_t grades[] = {100,90,80,70,60,50,40,30,20,10};
  SANDBOX_BEGIN;
  qsort_r((void *) nomas, 10, sizeof(uint32_t), *compare_indexes,(void *) grades);
  SANDBOX_END;
  CU_ASSERT_EQUAL(0, memcmp(nomas, res, 10));
}

void test_make_ranking(){
  set_test_metadata("make_ranking","Tests sur un fichier de 10,1000 et 10000 étudiants",1);
  char bases[3][9]= {"1101.bin","1103.bin","1503.bin"};
  uint8_t idx;

  for (idx=0 ; idx<3; idx++){
    char input[100] = "input/";
    char output[100] ="student_output/";
    char expected_output[100] = "expected_output/";
    strcat(input,bases[idx]);
    strcat(output,bases[idx]);
    strcat(expected_output,bases[idx]);

    SANDBOX_BEGIN;
    make_ranking(input,output);
    SANDBOX_END;

    FILE * stdf= fopen(output,"r");
    FILE * reff= fopen(expected_output,"r");
    
    CU_ASSERT_EQUAL(compare_binary_files(reff,stdf), 0);
    fclose(stdf);
    fclose(reff);
  }
}


void test_check_size(){
  set_test_metadata("make_ranking","Comparaison entre la taille du fichier rendu et celle attendue",1);
  char bases[3][9]= {"1101.bin","1103.bin","1503.bin"};
  uint8_t idx;

  for (idx=0 ; idx<3; idx++){
    char input[100] = "input/";
    char output[100] ="student_output/";
    char expected_output[100] = "expected_output/";
    strcat(input,bases[idx]);
    strcat(output,bases[idx]);
    strcat(expected_output,bases[idx]);

    SANDBOX_BEGIN;
    make_ranking(input,output);
    SANDBOX_END;


    FILE * stdf= fopen(output,"r");
    FILE * reff= fopen(expected_output,"r");
    CU_ASSERT_EQUAL(get_size(output), get_size(expected_output));
    fclose(stdf);
    fclose(reff);
  }
  
}

void test_fichier_input_inexistant(){
  set_test_metadata("make_ranking","Fichier d'input inexistant",1);
  char input[100]="non_existing_file.bin";
  char output[100]="trash.bin";

  int res;
  SANDBOX_BEGIN;
  res = make_ranking(input,output);
  SANDBOX_END;

  CU_ASSERT_EQUAL(res,1);
}

void test_fichier_output_inexistant(){
  set_test_metadata("make_ranking","Fichier d'output inexistant",1);
  char input[100] = "input/1503.bin";
  char output[100] ="student_output/non_existing_file.bin";

  int res;
  SANDBOX_BEGIN;
  res = make_ranking(input,output);
  SANDBOX_END;

  CU_ASSERT_EQUAL(res,4);
}


void test_fread_calls(){
  
  char input[100] = "input/1503.bin";
  char output[100] ="student_output/1503.bin";
  special_fread_count=0;
  printf("Count : %d : \n",special_fread_count);
  make_ranking(input,output);
  printf("Count : %d : \n",special_fread_count);
  CU_ASSERT_EQUAL(special_fread_count, 3);

}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_compare_indexes_1, test_compare_indexes_2, test_compare_indexes_3,test_compare_indexes_4,
    test_check_size, test_make_ranking, test_fichier_input_inexistant, test_fichier_output_inexistant);
}
