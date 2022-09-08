#ifndef SCODE
#define SCODE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>

int special_fread_count;

size_t xfread(void * ptr,size_t size, size_t n , FILE * file);

typedef
	@@file_struct@@
file_t;

void load_header_data(FILE * input_file, struct file * ptr);
int compare_indexes(const void * first, const void * second, void *ptr);
int make_ranking(char * file_path, char * output_file);
#endif