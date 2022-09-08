#include "student_code_sol.h"

int protect_sol(void inc(void), int nb, pthread_mutex_t* mutex){
	int err;
	for(int i = 0; i<nb; i++){
		err = pthread_mutex_lock(mutex);
	    if(err){
	        return err;
	    }
	    inc();
	    err = pthread_mutex_unlock(mutex);
	    if(err){
	        return err;
	    }    
	}
	return 0;
}

