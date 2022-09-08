#include "student_code_sol.h"

int doMyWork_sol(void* long_computing(void*), void* backup_computing(void*), char* string, int ret_value){
	pthread_t first_thread;
	pthread_t second_thread;
	void* first_ret;
	void* second_ret;

	int err = pthread_create(&first_thread, NULL, long_computing, (void* restrict) string);
	if(err){
		return -1;
	}

	err = pthread_join(first_thread, &first_ret);
	if(err){
		return -2;
	}

	int* ret1 = (int*) first_ret;
	if(*ret1 == ret_value){
		return ret_value;
	}

	err = pthread_create(&second_thread, NULL, backup_computing, (void* restrict) string);
	if(err){
		return -3;
	}

	err = pthread_join(second_thread, &second_ret);
	if(err){
		return -4;
	}

	int* ret2 = (int*) second_ret;
	return *ret2;
}

