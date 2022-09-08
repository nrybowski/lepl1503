#include "../student_code.h"

/**
struct file{
    uint32_t nb_students;
    uint16_t code;
    uint8_t average_grade;
    uint8_t median_grade;
    uint8_t max_grad;
    uint8_t min_grade;
}*/

void load_header_data_sol(FILE * input_file, file_t * ptr);
int compare_indexes_sol(const void * first, const void * second, void *ptr);
int make_ranking_sol(char * file_path, char * output_file);
