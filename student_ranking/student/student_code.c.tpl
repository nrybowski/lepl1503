#include<stdio.h>
#include<stdlib.h>
#include "student_code.h"

int special_fread_count=0;

size_t xfread(void * ptr,size_t size, size_t n , FILE * file)
{
    special_fread_count++;
    return fread(ptr,size,n,file);
}

@@load_header_data@@

int compare_indexes(const void * first, const void * second, void *ptr){
	@@compare_indexes@@
}
int make_ranking(char * file_path, char * output_file){
	@@make_ranking@@
}
