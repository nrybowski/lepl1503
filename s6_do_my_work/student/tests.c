#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

int flag = 1;
char* str = NULL;
int ret_value;
int ret1;
int ret2;

void init_str(){
	char* temp = "ceci est un string de longueur moyenne pour le computing.";
	str = (char*) malloc(sizeof(char)*(strlen(temp)+1));
	if(str==NULL){
		push_info_msg(_("Internal error occured when allocating string, please contact your tutor or an administrator"));
		return;
	}
	memcpy(str, temp, sizeof(char)*(strlen(temp)+1));
	ret_value = sizeof(char)*strlen(temp);
}

void clean_str(){
	free(str);
}

void* long_computing(void* str){
	char* string = (char*) str;

	ret1 = strlen(string);
	void* func_ret = (void*) &ret1;

	return func_ret;
}

void* backup_computing(void* str){
	char* string = (char*) str;

	ret2 = strlen(string);
	void* func_ret = (void*) &ret2;

	return func_ret;
}

void test_first_thread() {
	set_test_metadata("q1", _("Test for first thread returning the right value"), 1);

	int ret;
	init_str();

	if(str==NULL){
		CU_FAIL();
		return;
	}

	monitored.pthread_create = true;
	monitored.pthread_join = true;

	SANDBOX_BEGIN;
	
	ret = doMyWork(&long_computing, &backup_computing, str, ret_value);

	SANDBOX_END;

	monitored.pthread_create = false;
	monitored.pthread_join = false;

	CU_ASSERT_EQUAL(stats.pthread_create.called,1);
	CU_ASSERT_EQUAL(stats.pthread_join.called,1);
	/* It's funny to see that someone thought this test was working, we should give a refresh on the memory to tutors :-) */
	/* CU_ASSERT_EQUAL(*(stats.pthread_create.last_params.thread), stats.pthread_join.last_params.thread); */
	CU_ASSERT_PTR_EQUAL(stats.pthread_create.last_params.start_routine, &long_computing);
	CU_ASSERT_PTR_EQUAL(stats.pthread_create.last_params.arg, str);
	CU_ASSERT_PTR_NULL(stats.pthread_create.last_params.attr);
	CU_ASSERT_EQUAL(ret,ret_value);
	CU_ASSERT_STRING_EQUAL(str,"ceci est un string de longueur moyenne pour le computing.");

	if(stats.pthread_create.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly once for this test"));
	}
	if(stats.pthread_join.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_join exactly once for this test"));
	}
	/*
	if(*(stats.pthread_create.last_params.thread) != stats.pthread_join.last_params.thread){
		flag = 0;
		push_info_msg(_("You have to call pthread_join and pthread_create on the same thread to wait for its return value"));
	}
	*/
	if(stats.pthread_create.last_params.start_routine != &long_computing){
		flag = 0;
		push_info_msg(_("You didn't start the thread with the right start_routine, you have to launch the first thread with long_computing"));
	}
	if(stats.pthread_create.last_params.arg != str){
		flag = 0;
		push_info_msg(_("You didn't call the start_routine with the right argument, don't forget that your last argument to pthread_create is the argument passed to the start_routine"));
	}
	if(stats.pthread_create.last_params.attr != NULL){
		flag = 0;
		push_info_msg(_("You don't have to call pthread_create with attributes, usually you want to use NULL"));
	}
	if(ret != ret_value){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value"));
	}
	if(ret==-1 || ret==-2 || ret==-3 || ret==-4){
		set_tag("error_normal_case");
	}
	if(strcmp(str,"ceci est un string de longueur moyenne pour le computing.")){
		flag = 0;
		push_info_msg(_("You can't modify the string"));
	}
}

void test_second_thread() {
	set_test_metadata("q1", _("Test for first thread returning the wrong value"), 1);

	int ret;
	char* backup_str = "Hello World!";
	int backup_ret = strlen(backup_str);

	monitored.pthread_create = true;
	monitored.pthread_join = true;

	SANDBOX_BEGIN;
	
	ret = doMyWork(&long_computing, &backup_computing, backup_str, ret_value);

	SANDBOX_END;

	monitored.pthread_create = false;
	monitored.pthread_join = false;

	CU_ASSERT_EQUAL(stats.pthread_create.called,2);
	CU_ASSERT_EQUAL(stats.pthread_join.called,2);
	/* It's funny to see that someone thought this test was working, we should give a refresh on the memory to tutors :-) */
	/* CU_ASSERT_EQUAL(*(stats.pthread_create.last_params.thread), stats.pthread_join.last_params.thread); */
	CU_ASSERT_PTR_EQUAL(stats.pthread_create.last_params.start_routine, &backup_computing);
	CU_ASSERT_PTR_EQUAL(stats.pthread_create.last_params.arg, backup_str);
	CU_ASSERT_PTR_NULL(stats.pthread_create.last_params.attr);
	CU_ASSERT_EQUAL(ret,backup_ret);

	if(stats.pthread_create.called!=2){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly twice for this test"));
	}
	if(stats.pthread_join.called!=2){
		flag = 0;
		push_info_msg(_("You should call pthread_join exactly twice for this test"));
	}
	/*
	if(*(stats.pthread_create.last_params.thread) != stats.pthread_join.last_params.thread){
		flag = 0;
		push_info_msg(_("You have to do a second call to pthread_join and pthread_create on the same thread to wait for its return value (but a different thread from the first one)"));
	}
	*/
	if(stats.pthread_create.last_params.start_routine != &backup_computing){
		flag = 0;
		push_info_msg(_("You didn't start the second thread with the right start_routine, you have to launch it with backup_computing"));
	}
	if(stats.pthread_create.last_params.arg != backup_str){
		flag = 0;
		push_info_msg(_("You didn't call the start_routine with the right argument, don't forget that your last argument to pthread_create is the argument passed to the start_routine"));
	}
	if(stats.pthread_create.last_params.attr != NULL){
		flag = 0;
		push_info_msg(_("You don't have to call pthread_create with attributes, usually you want to use NULL"));
	}
	if(ret != backup_ret){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value"));
	}
	if(ret==-1 || ret==-2 || ret==-3 || ret==-4){
		set_tag("error_normal_case");
	}
}

void test_first_create_fail(){
	set_test_metadata("q1", _("Test the error handling when first create fails"), 1);

	int ret;

	failures.pthread_create = FAIL_FIRST;
	failures.pthread_create_ret = -1;
	monitored.pthread_create = true;

	SANDBOX_BEGIN;

	ret = doMyWork(&long_computing, &backup_computing, str, ret_value);

	SANDBOX_END;

	monitored.pthread_create = false;

	CU_ASSERT_EQUAL(stats.pthread_create.called,1);
	CU_ASSERT_EQUAL(ret,-1);

	if(stats.pthread_create.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly once for this test"));
	}
	if(ret != -1){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value when the first pthread_create failed"));
		set_tag("failure_handling");
	}
}

void test_first_join_fail(){
	set_test_metadata("q1", _("Test the error handling when first join fails"), 1);

	int ret;

	failures.pthread_join = FAIL_FIRST;
	failures.pthread_join_ret = -1;
	monitored.pthread_join = true;
	monitored.pthread_create = true;

	SANDBOX_BEGIN;

	ret = doMyWork(&long_computing, &backup_computing, str, ret_value);

	SANDBOX_END;

	monitored.pthread_join = false;
	monitored.pthread_create = false;

	CU_ASSERT_EQUAL(stats.pthread_join.called,1);
	CU_ASSERT_EQUAL(stats.pthread_create.called,1);
	CU_ASSERT_EQUAL(ret,-2);

	if(stats.pthread_join.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_join exactly once for this test"));
	}
	if(stats.pthread_create.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly once for this test"));
	}
	if(ret != -2){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value when the first pthread_join failed"));
		set_tag("failure_handling");
	}
}

void test_second_create_fail(){
	set_test_metadata("q1", _("Test the error handling when second create fails"), 1);

	int ret;

	failures.pthread_create = FAIL_SECOND;
	failures.pthread_create_ret = -1;
	monitored.pthread_create = true;
	monitored.pthread_join = true;

	SANDBOX_BEGIN;

	ret = doMyWork(&long_computing, &backup_computing, str, 0);

	SANDBOX_END;

	monitored.pthread_create = false;
	monitored.pthread_join = false;

	CU_ASSERT_EQUAL(stats.pthread_create.called,2);
	CU_ASSERT_EQUAL(stats.pthread_join.called,1);
	CU_ASSERT_EQUAL(ret,-3);

	if(stats.pthread_create.called!=2){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly twice for this test"));
	}
	if(stats.pthread_join.called!=1){
		flag = 0;
		push_info_msg(_("You should call pthread_join exactly once for this test"));
	}
	if(ret != -3){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value when the second pthread_create failed"));
		set_tag("failure_handling");
	}
}

void test_second_join_fail(){
	set_test_metadata("q1", _("Test the error handling when second join fails"), 1);

	int ret;

	failures.pthread_join = FAIL_SECOND;
	failures.pthread_join_ret = -1;
	monitored.pthread_join = true;
	monitored.pthread_create = true;

	SANDBOX_BEGIN;

	ret = doMyWork(&long_computing, &backup_computing, str, 0);

	SANDBOX_END;

	monitored.pthread_join = false;
	monitored.pthread_create = false;

	CU_ASSERT_EQUAL(stats.pthread_join.called,2);
	CU_ASSERT_EQUAL(stats.pthread_create.called,2);
	CU_ASSERT_EQUAL(ret,-4);

	if(stats.pthread_join.called!=2){
		flag = 0;
		push_info_msg(_("You should call pthread_join exactly twice for this test"));
	}
	if(stats.pthread_create.called!=2){
		flag = 0;
		push_info_msg(_("You should call pthread_create exactly twice for this test"));
	}
	if(ret != -4){
		flag = 0;
		push_info_msg(_("Your function didn't return the right value when the second pthread_join failed"));
		set_tag("failure_handling");
	}

	if(flag){
		set_tag("q1");
	}

	clean_str();
}

int main(int argc,char** argv)
{
	BAN_FUNCS(pthread_mutex_init,sem_init,set_tag);
	RUN(test_first_thread, test_second_thread, test_first_create_fail, test_first_join_fail, test_second_create_fail, test_second_join_fail);
}

