#include "student_code_sol.h"

int put_sol(data_t** buf, int len, int* first, int* last, int* in, data_t* d){
	if(*in==len){
		return -1;
	}

	buf[*last] = d;
	*last = (*last + 1) % len;
	(*in)++;

	return 0;
}

data_t* get_sol(data_t** buf, int len, int* first, int* last, int* in){
	if(*in==0){
		return NULL;
	}

	data_t* d = buf[*first];
	buf[*first] = NULL;
	*first = (*first + 1) % len;
	(*in)--;

	return d;
}