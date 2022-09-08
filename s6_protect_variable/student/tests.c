#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;
int sum = 0;

void inc(){
	sum++;
}

void* test_inc(void* arg){
	int* ret = (int*) malloc(sizeof(int));
	if(ret==NULL){
		push_info_msg(_("Internal malloc failed, please contact your tutor or an administrator"));
		return NULL;
	}
		
	*ret = protect(&inc, 1000, (pthread_mutex_t*) arg);
	if((*ret)!=0){
		free(ret);
		return NULL;
	}

	return (void*) ret;
}

void test_protect() {
	set_test_metadata("q1", _("Test if the variable is protected"), 1);

	sum = 0; //test for unlock_fail set it to one so we reset the value

	int ret;
	int flag_lock = 0;
	pthread_t threads[4];
	pthread_mutex_t mutex;

	ret = pthread_mutex_init(&mutex,NULL);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't init mutex");
		push_info_msg(_("Can't init internal mutex, please contact your tutor or an administrator"));
		return;
	}

	monitored.pthread_mutex_lock = true;
	monitored.pthread_mutex_unlock = true;

	SANDBOX_BEGIN;
	for(int i = 0; i<4; i++){
		ret = pthread_create(&threads[i], NULL, &test_inc, (void*) &mutex);
		if(ret){
			flag = 0;
			CU_FAIL("Can't launch the threads");
			push_info_msg(_("Can't launch internal threads, please contact your tutor or an administrator"));
			return;
		}
	}

	void* out;

	for(int i = 0; i<4; i++){
		ret = pthread_join(threads[i], &out);
		if(ret){
			flag = 0;
			CU_FAIL("Can't join the threads");
			push_info_msg(_("Can't join internal threads, please contact your tutor or an administrator"));
			return;
		}
		int* out2 = (int*) out;
		if(out2==NULL){
			CU_FAIL();
			push_info_msg(_("Your code does not return the correct value, you should return 0 when everything is fine"));
			set_tag("error_normal_case");
			flag = 0;
		}
		else{
			free(out2);
		}
	}

	SANDBOX_END;

	monitored.pthread_mutex_lock = false;
	monitored.pthread_mutex_unlock = false;

	ret = pthread_mutex_destroy(&mutex);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't destroy mutex");
		char* msg = _("Can't destroy internal mutex, please contact your tutor or an administrator : %d");
		char errmsg[strlen(msg)+30];
		sprintf(errmsg,msg,ret);
		push_info_msg(errmsg);
		return;
	}

	CU_ASSERT_EQUAL(sum,4000);
	if(sum!=4000){
		push_info_msg(_("You didn't protect correctly the variable or didn't call inc() enough"));
		flag = 0;
	}

	CU_ASSERT_EQUAL(stats.pthread_mutex_lock.called,4000);
	CU_ASSERT_EQUAL(stats.pthread_mutex_unlock.called,4000);
	CU_ASSERT_EQUAL(stats.pthread_mutex_unlock.called, stats.pthread_mutex_lock.called);
	CU_ASSERT_PTR_EQUAL(stats.pthread_mutex_lock.last_arg,stats.pthread_mutex_unlock.last_arg);

	if(stats.pthread_mutex_lock.called > 4000){
		push_info_msg(_("Your number of calls to pthread_mutex_lock is higher than expected"));
		flag = 0;
	}
	if(stats.pthread_mutex_lock.called < 4000){
		if(stats.pthread_mutex_lock.called==4){
			flag_lock = 1;
			push_info_msg(_("You call lock only once per thread. That's not what you want to do when using threads because if you lock the threads one by one, it's like not using them : your program is not concurrent anymore. Ask your tutor for more information."));
		}
		else{
			push_info_msg(_("Your number of calls to pthread_mutex_lock is lower than expected"));
		}
		flag = 0;
	}
	if(stats.pthread_mutex_unlock.called > 4000){
		push_info_msg(_("Your number of calls to pthread_mutex_unlock is higher than expected"));
		flag = 0;
	}
	if(stats.pthread_mutex_unlock.called < 4000){
		if(stats.pthread_mutex_lock.called==4 && flag_lock){
			push_info_msg(_("Don't forget to change the number of times you call unlock too."));
		}
		else{
			push_info_msg(_("Your number of calls to pthread_mutex_lock is lower than expected"));
		}
		flag = 0;
	}
	if(stats.pthread_mutex_unlock.called!=stats.pthread_mutex_lock.called){
		push_info_msg(_("You didn't call pthread_mutex_lock as many times as pthread_mutex_unlock"));
		flag = 0;
	}
	if(stats.pthread_mutex_lock.last_arg != stats.pthread_mutex_unlock.last_arg){
		push_info_msg(_("You didn't call lock and unlock on the same mutex"));
	}

	if(flag){
		set_tag("q1");
	}
}

void test_lock_fail(){
	set_test_metadata("q1", _("Test the error handling when lock fails"), 1);

	int ret;
	pthread_t thread;
	pthread_mutex_t mutex;
	void* out;

	ret = pthread_mutex_init(&mutex,NULL);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't init mutex");
		push_info_msg(_("Can't init internal mutex, please contact your tutor or an administrator"));
		return;
	}

	failures.pthread_mutex_lock = FAIL_FIRST;
	failures.pthread_mutex_lock_ret = 22;
	monitored.pthread_mutex_lock = true;

	SANDBOX_BEGIN;

	ret = pthread_create(&thread, NULL, &test_inc, (void*) &mutex);
	if(ret){
		flag = 0;
		CU_FAIL("Can't launch the thread");
		push_info_msg(_("Can't launch internal thread, please contact your tutor or an administrator"));
		return;
	}

	ret = pthread_join(thread, &out);
	if(ret){
		flag = 0;
		CU_FAIL("Can't join the thread");
		push_info_msg(_("Can't join internal thread, please contact your tutor or an administrator"));
		return;
	}

	SANDBOX_END;

	monitored.pthread_mutex_lock = false;

	ret = pthread_mutex_destroy(&mutex);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't destroy mutex");
		char* msg = _("Can't destroy internal mutex, please contact your tutor or an administrator : %d");
		char errmsg[strlen(msg)+30];
		sprintf(errmsg,msg,ret);
		push_info_msg(errmsg);
		return;
	}

	int* out2 = (int*) out;
	if(out2!=NULL){
		CU_FAIL();
		push_info_msg(_("You don't return an error code when the call to lock fails"));
		set_tag("failure_handling");
		flag = 0;
	}
	else{
		CU_PASS();
	}

}

void test_unlock_fail(){
	set_test_metadata("q1", _("Test the error handling when unlock fails"), 1);

	int ret;
	pthread_t thread;
	pthread_mutex_t mutex;
	void* out;

	ret = pthread_mutex_init(&mutex,NULL);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't init mutex");
		push_info_msg(_("Can't init internal mutex, please contact your tutor or an administrator"));
		return;
	}

	failures.pthread_mutex_unlock = FAIL_FIRST;
	failures.pthread_mutex_unlock_ret = 22;
	monitored.pthread_mutex_unlock = true;

	SANDBOX_BEGIN;

	ret = pthread_create(&thread, NULL, &test_inc, (void*) &mutex);
	if(ret){
		flag = 0;
		CU_FAIL("Can't launch the thread");
		push_info_msg(_("Can't launch internal thread, please contact your tutor or an administrator"));
		return;
	}

	ret = pthread_join(thread, &out);
	if(ret){
		flag = 0;
		CU_FAIL("Can't join the thread");
		push_info_msg(_("Can't join internal thread, please contact your tutor or an administrator"));
		return;
	}

	SANDBOX_END;

	monitored.pthread_mutex_unlock = false;

	ret = pthread_mutex_unlock(&mutex); //Necessary because the mutex is used inside the student function so can't be destroyed if not unlocked
	if(ret){
	    flag = 0;
		CU_FAIL("Can't unlock mutex");
		char* msg = _("Can't unlock internal mutex, please contact your tutor or an administrator : %d");
		char errmsg[strlen(msg)+30];
		sprintf(errmsg,msg,ret);
		push_info_msg(errmsg);
		return;
	}

	ret = pthread_mutex_destroy(&mutex);
	if(ret){
	    flag = 0;
		CU_FAIL("Can't destroy mutex");
		char* msg = _("Can't destroy internal mutex, please contact your tutor or an administrator : %d");
		char errmsg[strlen(msg)+30];
		sprintf(errmsg,msg,ret);
		push_info_msg(errmsg);
		return;
	}

	int* out2 = (int*) out;
	if(out2!=NULL){
		CU_FAIL();
		push_info_msg(_("You don't return an error code when the call to unlock fails"));
		set_tag("failure_handling");
		flag = 0;
	}
	else{
		CU_PASS();
	}

}

int main(int argc,char** argv)
{
	BAN_FUNCS(pthread_mutex_trylock,sem_init,pthread_mutex_init,pthread_mutex_destroy,set_tag);
	RUN(test_lock_fail, test_unlock_fail, test_protect);
}

