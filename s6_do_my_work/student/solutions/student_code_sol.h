#include <stdlib.h>
#include <pthread.h>

int doMyWork_sol(void* long_computing(void*), void* backup_computing(void*), char* string, int ret_value);