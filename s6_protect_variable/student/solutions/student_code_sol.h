#include <stdlib.h>
#include <pthread.h>

int protect_sol(void inc(void), int nb, pthread_mutex_t* mutex);