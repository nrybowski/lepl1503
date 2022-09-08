#include <stdlib.h>
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

int put_flag = 1;
int get_flag = 1;
data_t *BAD = (data_t *) NULL;

data_t** init_buffer(int len){
	data_t** buf = (data_t**) malloc(sizeof(data_t*)*len);
	if(buf==NULL){
		push_info_msg(_("Can't malloc buffer, please contact your tutor or an administrator"));
		return NULL;
	}
    /* This is not efficient, but still useful to avoid crashing */
    for (int i = 0; i < len; i++) {
        *(buf + i) = BAD;
    }
	return buf;
}

void clean_buffer(data_t** buf){
	free(buf);
}

void test_put() {
	set_test_metadata("q1", _("Test if the function put() works correctly when empty spaces are available"), 1);

	int ret;
	int ret2;
	int len = 5;
	int first = 0;
	int last = 0;
	int in = 0;
    int is_bad = 0;

	data_t** buffer = init_buffer(len);
	if(buffer==NULL){
		CU_FAIL();
		return;
	}

	data_t a = {52,86,12.3};
	data_t b = {0,1,0.1};
	data_t c = {1,2,0.2};
	data_t d = {2,3,0.3};
	data_t e = {3,4,0.4};
	data_t f = {4,5,0.5};

	SANDBOX_BEGIN;

	ret = put(buffer,len,&first,&last,&in,&a);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret,0);
	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,0);
	CU_ASSERT_EQUAL(last,1);
	CU_ASSERT_EQUAL(in,1);
    
	if (buffer[0] == BAD) {
		is_bad = 1;
		CU_FAIL("Buffer is not allocated at all");
	} else {
		CU_ASSERT_EQUAL(buffer[0]->longitude,52);
		CU_ASSERT_EQUAL(buffer[0]->latitude,86);
		CU_ASSERT_DOUBLE_EQUAL(buffer[0]->avg_temp,12.3,0.00001);   
	}

	if(ret!=0){
		put_flag = 0;
		push_info_msg(_("You didn't return 0 when everything is fine"));
	}
	if(len!=5){
		put_flag = 0;
		push_info_msg(_("You modified the variable len but you mustn't do that"));
	}
	if(first!=0){
		put_flag = 0;
		push_info_msg(_("You modified the value pointed to by first while you should modify last"));
	}
	if(last!=1){
		put_flag = 0;
		push_info_msg(_("You didn't (correctly) modify the value pointed to by last while you should have because you inserted one new element"));
	}
	if(in!=1){
		put_flag = 0;
		push_info_msg(_("You didn't modify the value pointed to by in while you should have because you inserted one new element"));
	}
	if (is_bad) {
		put_flag = 0;
		push_info_msg(_("You do not insert any element in the structure"));
	} else {
        if(buffer[0]->longitude!=52){
            put_flag = 0;
            push_info_msg(_("You didn't insert the structure correctly, the longitude is incorrect"));
        }
        if(buffer[0]->latitude!=86){
            put_flag = 0;
            push_info_msg(_("You didn't insert the structure correctly, the latitude is incorrect"));
        }
        if(fabs(buffer[0]->avg_temp - 12.3) >= 0.00001){
            put_flag = 0;
            push_info_msg(_("You didn't insert the structure correctly, the avg_temp is incorrect"));
        }
    }
	

	if(!put_flag){
		return;
	}

	ret = put_sol(buffer,len,&first,&last,&in,&b);
	ret = put_sol(buffer,len,&first,&last,&in,&c);
	ret = put_sol(buffer,len,&first,&last,&in,&d);
	data_t* getRet = get_sol(buffer,len,&first,&last,&in);

	SANDBOX_BEGIN;

	ret = put(buffer,len,&first,&last,&in,&e);
	ret2 = put(buffer,len,&first,&last,&in,&f);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret,0);
	CU_ASSERT_EQUAL(ret2,0);
	CU_ASSERT_PTR_EQUAL(getRet,&a);

	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,1);
	CU_ASSERT_EQUAL(in,5);
    
    if (first != 1) {
        put_flag = 0;
        push_info_msg(_("You do not properly handle the `first` variable when inserting multiple elements"));
    }
    if (last != 1) {
        put_flag = 0;
        push_info_msg(_("You do not properly handle the `last` variable when inserting multiple elements"));
    }
    if (in != 5) {
        put_flag = 0;
        push_info_msg(_("You do not properly handle the `in` variable when inserting multiple elements"));
    }
    
    if (buffer[0] == BAD || buffer[1] == BAD || buffer[2] == BAD || buffer[3] == BAD || buffer[4] == BAD) {
        put_flag = 0;
        CU_FAIL("Buffer not correctly allocated");
        push_info_msg(_("You do not initialize correctly elements when there are multiple insertions"));
    }
    
    if (!put_flag) {
        return;
    }

	CU_ASSERT_EQUAL(buffer[0]->longitude,4);
	CU_ASSERT_EQUAL(buffer[0]->latitude,5);
	CU_ASSERT_DOUBLE_EQUAL(buffer[0]->avg_temp,0.5,0.00001);

	CU_ASSERT_EQUAL(buffer[1]->longitude,0);
	CU_ASSERT_EQUAL(buffer[1]->latitude,1);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,0.1,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,1);
	CU_ASSERT_EQUAL(buffer[2]->latitude,2);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,0.2,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,2);
	CU_ASSERT_EQUAL(buffer[3]->latitude,3);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,0.3,0.00001);

	CU_ASSERT_EQUAL(buffer[4]->longitude,3);
	CU_ASSERT_EQUAL(buffer[4]->latitude,4);
	CU_ASSERT_DOUBLE_EQUAL(buffer[4]->avg_temp,0.4,0.00001);

	if(ret!=0){
		put_flag = 0;
		push_info_msg(_("You didn't return 0 when everything is fine"));
	}
	if(ret2!=0){
		put_flag = 0;
		push_info_msg(_("You didn't return 0 when going back to the first slot that was actually empty"));
	}
	if(getRet!=&a){
		put_flag = 0;
		push_info_msg(_("You didn't insert the first element correctly in the buffer or modified the values pointed to by last, first or in wrongly"));
	}
	if(first!=1){
		put_flag = 0;
		push_info_msg(_("You modified the value pointed to by first while you should only modify last"));
	}
	if(last!=1){
		put_flag = 0;
		if(last==5 || last==6){
			push_info_msg(_("The value pointed to by last is out of the buffer. When writing to the last slot of the buffer, you have to come back to the first one after"));
		}
		else{
			push_info_msg(_("You didn't modify the value pointed to by last correctly when overlapping the first element in the buffer"));
		}
	}
	if(in!=5){
		put_flag = 0;
		push_info_msg(_("You didn't modify the value pointed to by in while you should have"));
	}
	if(buffer[4]->longitude!=3 || buffer[4]->latitude!=4 || fabs(buffer[4]->avg_temp - 0.4) >= 0.00001
		|| buffer[3]->longitude!=2 || buffer[3]->latitude!=3 || fabs(buffer[3]->avg_temp - 0.3) >= 0.00001
		|| buffer[2]->longitude!=1 || buffer[2]->latitude!=2 || fabs(buffer[2]->avg_temp - 0.2) >= 0.00001
		|| buffer[1]->longitude!=0 || buffer[1]->latitude!=1 || fabs(buffer[1]->avg_temp - 0.1) >= 0.00001
		|| buffer[0]->longitude!=4 || buffer[0]->latitude!=5 || fabs(buffer[0]->avg_temp - 0.5) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("You modified at least one structure that you should not have modified or you didn't insert structures correctly in the buffer"));
	}

	clean_buffer(buffer);
}

void test_get() {
	set_test_metadata("q2", _("Test if the function get() works correctly when data are available in the buffer"), 1);

	int ret;
	int len = 5;
	int first = 0;
	int last = 0;
	int in = 0;

	data_t* getRet = NULL;

	data_t** buffer = init_buffer(len);
	if(buffer==NULL){
		CU_FAIL();
		return;
	}

	data_t d = {52,86,12.3};
	data_t e = {46,105,13.4};
	data_t f = {23,20,16.0};
	data_t g = {2,129,11.5};
	data_t h = {1,2,0.1};
	data_t i = {2,3,0.2};

	ret = put_sol(buffer,len,&first,&last,&in,&d);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&e);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&f);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&g);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&h);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}

	SANDBOX_BEGIN;

	getRet = get(buffer, len, &first, &last, &in);

	SANDBOX_END;

	CU_ASSERT_PTR_EQUAL(getRet,&d);
	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,0);
	CU_ASSERT_EQUAL(in,4);

	CU_ASSERT_EQUAL(buffer[1]->longitude,46);
	CU_ASSERT_EQUAL(buffer[1]->latitude,105);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,13.4,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,23);
	CU_ASSERT_EQUAL(buffer[2]->latitude,20);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,16.0,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,2);
	CU_ASSERT_EQUAL(buffer[3]->latitude,129);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,11.5,0.00001);

	CU_ASSERT_EQUAL(buffer[4]->longitude,1);
	CU_ASSERT_EQUAL(buffer[4]->latitude,2);
	CU_ASSERT_DOUBLE_EQUAL(buffer[4]->avg_temp,0.1,0.00001);

	if(getRet!=&d){
		get_flag = 0;
		push_info_msg(_("You don't return the right element in the buffer"));
	}
	if(len!=5){
		get_flag = 0;
		push_info_msg(_("You modified the variable len but you mustn't do that"));
	}
	if(first!=1){
		get_flag = 0;
		push_info_msg(_("The value pointed to by first is not equal to one while we called get() only once"));
	}
	if(last!=0){
		get_flag = 0;
		push_info_msg(_("Your get() code modifies the value pointed to by last while it shouldn't"));
	}
	if(in!=4){
		get_flag = 0;
		push_info_msg(_("The value pointed to by in has not been updated or updated incorrectly"));
	}
	if(buffer[4]->longitude!=1 || buffer[4]->latitude!=2 || fabs(buffer[4]->avg_temp - 0.1) >= 0.00001
		|| buffer[3]->longitude!=2 || buffer[3]->latitude!=129 || fabs(buffer[3]->avg_temp - 11.5) >= 0.00001
		|| buffer[2]->longitude!=23 || buffer[2]->latitude!=20 || fabs(buffer[2]->avg_temp - 16.0) >= 0.00001
		|| buffer[1]->longitude!=46 || buffer[1]->latitude!=105 || fabs(buffer[1]->avg_temp - 13.4) >= 0.00001){
		get_flag = 0;
		push_info_msg(_("You modified at least one structure that you should not have modified"));
	}

	ret = put_sol(buffer,len,&first,&last,&in,&i);
	if(ret!=0){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}

	SANDBOX_BEGIN;

	getRet = get(buffer, len, &first, &last, &in);
	getRet = get(buffer, len, &first, &last, &in);
	getRet = get(buffer, len, &first, &last, &in);
	getRet = get(buffer, len, &first, &last, &in);
	getRet = get(buffer, len, &first, &last, &in);

	SANDBOX_END;

	CU_ASSERT_PTR_EQUAL(getRet,&i);

	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,1);
	CU_ASSERT_EQUAL(in,0);

	if(getRet!=&i){
		get_flag = 0;
		push_info_msg(_("The last get we dit should have gotten the element in the first slot but after having filled all the buffer (so overlapping) but it didn't"));
	}
	if(first!=1){
		get_flag = 0;
		if(first > 4){
			push_info_msg(_("The value pointed to by first is out of the buffer. Don't forget that the buffer is limited in size so you have to come back to the beginning sometimes"));
		}
		else{
			push_info_msg(_("The value pointed to by first is not correctly updated"));
		}
	}
	if(last!=1){
		get_flag = 0;
		push_info_msg(_("Your get() code modifies the value pointed to by last while it shouldn't"));
	}
	if(in!=0){
		get_flag = 0;
		push_info_msg(_("The value pointed to by in has not been updated or updated incorrectly"));
	}

	clean_buffer(buffer);
}

void test_put_and_get(){
	set_test_metadata("q2", _("Test the put() and the get() functions"), 5);

	if(!put_flag || !get_flag){
		CU_FAIL();
		push_info_msg(_("Test not started : we will launch this test when you succeed to all other tests"));
		return;
	}

	data_t* getRet1;
	data_t* getRet2;
	data_t* getRet3;
	data_t* getRet4;
	data_t* getRet5;
	data_t* getRet6;

	int ret1;
	int ret2;
	int ret3;
	int ret4;
	int ret5;
	int len = 5;
	int first = 0;
	int last = 0;
	int in = 0;

	data_t** buffer = init_buffer(len);
	if(buffer==NULL){
		CU_FAIL();
		return;
	}

	data_t a = {0,1,0.0};
	data_t b = {1,2,0.1};
	data_t c = {2,3,0.2};
	data_t d = {3,4,0.3};
	data_t e = {4,5,0.4};
	data_t f = {5,6,0.5};
	data_t g = {6,7,0.6};
	data_t h = {7,8,0.7};
	data_t i = {8,9,0.8};
	data_t j = {9,10,0.9};

	SANDBOX_BEGIN;

	ret1 = put(buffer,len,&first,&last,&in,&a);
	ret2 = put(buffer,len,&first,&last,&in,&b);
	ret3 = put(buffer,len,&first,&last,&in,&c);
	ret4 = put(buffer,len,&first,&last,&in,&d);
	ret5 = put(buffer,len,&first,&last,&in,&e);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret1,0);
	CU_ASSERT_EQUAL(ret2,0);
	CU_ASSERT_EQUAL(ret3,0);
	CU_ASSERT_EQUAL(ret4,0);
	CU_ASSERT_EQUAL(ret5,0);

	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,0);
	CU_ASSERT_EQUAL(last,0);
	CU_ASSERT_EQUAL(in,5);

	CU_ASSERT_EQUAL(buffer[0]->longitude,0);
	CU_ASSERT_EQUAL(buffer[0]->latitude,1);
	CU_ASSERT_DOUBLE_EQUAL(buffer[0]->avg_temp,0.0,0.00001);

	CU_ASSERT_EQUAL(buffer[1]->longitude,1);
	CU_ASSERT_EQUAL(buffer[1]->latitude,2);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,0.1,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,2);
	CU_ASSERT_EQUAL(buffer[2]->latitude,3);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,0.2,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,3);
	CU_ASSERT_EQUAL(buffer[3]->latitude,4);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,0.3,0.00001);

	CU_ASSERT_EQUAL(buffer[4]->longitude,4);
	CU_ASSERT_EQUAL(buffer[4]->latitude,5);
	CU_ASSERT_DOUBLE_EQUAL(buffer[4]->avg_temp,0.4,0.00001);

	if(ret1!=0){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}
	if(ret2!=0 && put_flag){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}
	if(ret3!=0 && put_flag){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}
	if(ret4!=0 && put_flag){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}
	if(ret5!=0 && put_flag){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}


	if(len!=5){
		put_flag = 0;
		push_info_msg(_("Put() : You modified the variable len when you put something in the buffer"));
	}
	if(first!=0){
		put_flag = 0;
		push_info_msg(_("Put() : You modified the value pointed to by first while we only called your put() function"));
	}
	if(last!=0){
		put_flag = 0;
		if(last==5){
			push_info_msg(_("Put() : The value pointed to by last is out of the array while it should point to the next available slot in the buffer (the slot may be full if the buffer is full)"));
		}
		else{
			push_info_msg(_("Put() : You don't modify the value pointed to by last correctly"));
		}
	}
	if(in!=5){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't modify the value pointed to by in while you should have because we called your function put()"));
	}

	if(buffer[0]->longitude!=0 || buffer[0]->latitude!=1 || fabs(buffer[0]->avg_temp - 0.0) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the first structure correctly"));
	}
	if(buffer[1]->longitude!=1 || buffer[1]->latitude!=2 || fabs(buffer[1]->avg_temp - 0.1) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the second structure correctly"));
	}
	if(buffer[2]->longitude!=2 || buffer[2]->latitude!=3 || fabs(buffer[2]->avg_temp - 0.2) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the third structure correctly"));
	}
	if(buffer[3]->longitude!=3 || buffer[3]->latitude!=4 || fabs(buffer[3]->avg_temp - 0.3) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the fourth structure correctly"));
	}
	if(buffer[4]->longitude!=4 || buffer[4]->latitude!=5 || fabs(buffer[4]->avg_temp - 0.4) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the fifth structure correctly"));
	}

	SANDBOX_BEGIN;

	getRet1 = get(buffer,len,&first,&last,&in);

	SANDBOX_END;

	CU_ASSERT_PTR_EQUAL(getRet1,&a);
	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,0);
	CU_ASSERT_EQUAL(in,4);

	CU_ASSERT_EQUAL(buffer[1]->longitude,1);
	CU_ASSERT_EQUAL(buffer[1]->latitude,2);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,0.1,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,2);
	CU_ASSERT_EQUAL(buffer[2]->latitude,3);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,0.2,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,3);
	CU_ASSERT_EQUAL(buffer[3]->latitude,4);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,0.3,0.00001);

	CU_ASSERT_EQUAL(buffer[4]->longitude,4);
	CU_ASSERT_EQUAL(buffer[4]->latitude,5);
	CU_ASSERT_DOUBLE_EQUAL(buffer[4]->avg_temp,0.4,0.00001);

	if(getRet1!=&a){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting first element inserted"));
	}
	if(len!=5){
		get_flag = 0;
		push_info_msg(_("Get() : You modified the variable len when we called you get() function"));
	}
	if(first!=1){
		get_flag = 0;
		push_info_msg(_("Get() : You don't modify the value pointed to by first correctly"));
	}
	if(last!=0){
		get_flag = 0;
		push_info_msg(_("Get() : Your get() code modifies the value pointed to by last while it shouldn't"));
	}
	if(in!=4){
		get_flag = 0;
		push_info_msg(_("Get() : The value pointd to by in has not been updated or updated incorrectly"));
	}
	if(buffer[4]->longitude!=4 || buffer[4]->latitude!=5 || fabs(buffer[4]->avg_temp - 0.4) >= 0.00001
		|| buffer[3]->longitude!=3 || buffer[3]->latitude!=4 || fabs(buffer[3]->avg_temp - 0.3) >= 0.00001
		|| buffer[2]->longitude!=2 || buffer[2]->latitude!=3 || fabs(buffer[2]->avg_temp - 0.2) >= 0.00001
		|| buffer[1]->longitude!=1 || buffer[1]->latitude!=2 || fabs(buffer[1]->avg_temp - 0.1) >= 0.00001){
		get_flag = 0;
		push_info_msg(_("Get() : You modified at least one structure that you should not have modified, be sure to respect the FIFO order"));
	}

	SANDBOX_BEGIN;

	ret1 = put(buffer,len,&first,&last,&in,&f);
	ret2 = put(buffer,len,&first,&last,&in,&g);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret1,0);
	CU_ASSERT_EQUAL(ret2,-1);

	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,1);
	CU_ASSERT_EQUAL(in,5);

	CU_ASSERT_EQUAL(buffer[0]->longitude,5);
	CU_ASSERT_EQUAL(buffer[0]->latitude,6);
	CU_ASSERT_DOUBLE_EQUAL(buffer[0]->avg_temp,0.5,0.00001);

	CU_ASSERT_EQUAL(buffer[1]->longitude,1);
	CU_ASSERT_EQUAL(buffer[1]->latitude,2);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,0.1,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,2);
	CU_ASSERT_EQUAL(buffer[2]->latitude,3);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,0.2,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,3);
	CU_ASSERT_EQUAL(buffer[3]->latitude,4);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,0.3,0.00001);

	CU_ASSERT_EQUAL(buffer[4]->longitude,4);
	CU_ASSERT_EQUAL(buffer[4]->latitude,5);
	CU_ASSERT_DOUBLE_EQUAL(buffer[4]->avg_temp,0.4,0.00001);

	if(ret1!=0){
		put_flag = 0;
		push_info_msg(_("Put() : When going back to the first slot in the buffer to insert one element where there was another one that has been deleted from your get() function, you don't return 0"));
	}
	if(ret2!=-1){
		put_flag = 0;
		push_info_msg(_("Put() : When the buffer is full, you don't return -1"));
	}
	if(first!=1){
		put_flag = 0;
		push_info_msg(_("Put() : You mustn't modify the value pointed to by first when putting one new element in the buffer"));
	}
	if(last!=1){
		put_flag = 0;
		push_info_msg(_("¨Put() : You don't modify correctly the value pointed to by last when overlapping the first elements"));
	}
	if(in!=5){
		put_flag = 0;
		push_info_msg(_("Put() : The value pointed to by in has not been updated or updated incorrectly when overlapping the first elements"));
	}

	if(buffer[4]->longitude!=4 || buffer[4]->latitude!=5 || fabs(buffer[4]->avg_temp - 0.4) >= 0.00001
		|| buffer[3]->longitude!=3 || buffer[3]->latitude!=4 || fabs(buffer[3]->avg_temp - 0.3) >= 0.00001
		|| buffer[2]->longitude!=2 || buffer[2]->latitude!=3 || fabs(buffer[2]->avg_temp - 0.2) >= 0.00001
		|| buffer[1]->longitude!=1 || buffer[1]->latitude!=2 || fabs(buffer[1]->avg_temp - 0.1) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : When overlapping the first elements, you modified at least one structure that you should not have modified"));
	}

	if(buffer[0]->longitude!=5 || buffer[0]->latitude!=6 || fabs(buffer[0]->avg_temp - 0.5) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't insert the overlapping structure correctly"));
	}

	SANDBOX_BEGIN;

	getRet1 = get(buffer,len,&first,&last,&in);
	getRet2 = get(buffer,len,&first,&last,&in);
	getRet3 = get(buffer,len,&first,&last,&in);
	getRet4 = get(buffer,len,&first,&last,&in);
	getRet5 = get(buffer,len,&first,&last,&in);
	getRet6 = get(buffer,len,&first,&last,&in);

	SANDBOX_END;

	CU_ASSERT_PTR_EQUAL(getRet1,&b);
	CU_ASSERT_PTR_EQUAL(getRet2,&c);
	CU_ASSERT_PTR_EQUAL(getRet3,&d);
	CU_ASSERT_PTR_EQUAL(getRet4,&e);
	CU_ASSERT_PTR_EQUAL(getRet5,&f);
	CU_ASSERT_PTR_NULL(getRet6);

	CU_ASSERT_EQUAL(first,1);
	CU_ASSERT_EQUAL(last,1);
	CU_ASSERT_EQUAL(in,0);

	if(getRet1!=&b){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting second element inserted"));
	}
	if(getRet2!=&c){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting third element inserted"));
	}
	if(getRet3!=&d){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting fourth element inserted"));
	}
	if(getRet4!=&e){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting fifth element inserted"));
	}
	if(getRet5!=&f){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return the right element in the buffer when getting sixth element inserted"));
	}
	if(getRet6!=NULL){
		get_flag = 0;
		push_info_msg(_("Get() : You don't return NULL when buffer is empty"));
	}

	if(first!=1){
		get_flag = 0;
		if(first==6){
			push_info_msg(_("Get() : The value pointed to by first is out of the array, don't forget that the array has a finite size so you have to come back at 0 sometimes"));
		}
		else{
			push_info_msg(_("Get() : You don't update the value pointed to by first correctly"));
		}
	}
	if(last!=1){
		get_flag = 0;
		push_info_msg(_("Get() : You don't have to update the value pointed to by last when getting elements from the buffer"));
	}
	if(in!=0){
		get_flag = 0;
		push_info_msg(_("Get() : You don't update the value pointed to by in correctly when totally emptying the buffer"));
	}

	SANDBOX_BEGIN;

	ret1 = put(buffer,len,&first,&last,&in,&h);
	ret2 = put(buffer,len,&first,&last,&in,&i);
	ret3 = put(buffer,len,&first,&last,&in,&j);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret1,0);
	CU_ASSERT_EQUAL(ret2,0);
	CU_ASSERT_EQUAL(ret3,0);

	CU_ASSERT_EQUAL(last,4);
	CU_ASSERT_EQUAL(in,3);

	CU_ASSERT_EQUAL(buffer[1]->longitude,7);
	CU_ASSERT_EQUAL(buffer[1]->latitude,8);
	CU_ASSERT_DOUBLE_EQUAL(buffer[1]->avg_temp,0.7,0.00001);

	CU_ASSERT_EQUAL(buffer[2]->longitude,8);
	CU_ASSERT_EQUAL(buffer[2]->latitude,9);
	CU_ASSERT_DOUBLE_EQUAL(buffer[2]->avg_temp,0.8,0.00001);

	CU_ASSERT_EQUAL(buffer[3]->longitude,9);
	CU_ASSERT_EQUAL(buffer[3]->latitude,10);
	CU_ASSERT_DOUBLE_EQUAL(buffer[3]->avg_temp,0.9,0.00001);

	if(ret1!=0 || ret2!=0 || ret3!=0){
		put_flag = 0;
		push_info_msg(_("Put() : You didn't return 0 when everything is fine"));
	}
	if(last!=4){
		put_flag = 0;
		push_info_msg(_("Put() : You don't update the value pointed to by last correctly when overlapping elements"));
	}
	if(in!=3){
		put_flag = 0;
		push_info_msg(_("Put() : You don't update the value pointed to by in correctly when overlapping elements"));
	}
	if(buffer[3]->longitude!=9 || buffer[3]->latitude!=10 || fabs(buffer[3]->avg_temp - 0.9) >= 0.00001
		|| buffer[2]->longitude!=8 || buffer[2]->latitude!=9 || fabs(buffer[2]->avg_temp - 0.8) >= 0.00001
		|| buffer[1]->longitude!=7 || buffer[1]->latitude!=8 || fabs(buffer[1]->avg_temp - 0.7) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("Put() : When overlapping the first elements, you don't insert new elements correctly"));
	}

	clean_buffer(buffer);
}

void test_put_buffer_full(){
	set_test_metadata("q1", _("Test the put() function when the buffer is full"), 1);

	int ret;
	int len = 5;
	int first = 0;
	int last = 0;
	int in = 0;

	data_t** buffer = init_buffer(len);
	if(buffer==NULL){
		CU_FAIL();
		return;
	}

	data_t a = {0,1,0.0};
	data_t b = {1,2,0.1};
	data_t c = {2,3,0.2};
	data_t d = {3,4,0.3};
	data_t e = {4,5,0.4};

	ret = put_sol(buffer,len,&first,&last,&in,&a);
	if(ret){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&b);
	if(ret){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&c);
	if(ret){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&d);
	if(ret){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}
	ret = put_sol(buffer,len,&first,&last,&in,&e);
	if(ret){
		push_info_msg(_("Can't intialise buffer, please contact your tutor or an administrator"));
		CU_FAIL();
		return;
	}

	data_t f = {100,50,23.5};

	SANDBOX_BEGIN;

	ret = put(buffer,len,&first,&last,&in,&f);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret,-1);
	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,0);
	CU_ASSERT_EQUAL(last,0);
	CU_ASSERT_EQUAL(in,5);
	CU_ASSERT_EQUAL(buffer[0]->longitude,0);
	CU_ASSERT_EQUAL(buffer[0]->latitude,1);
	CU_ASSERT_DOUBLE_EQUAL(buffer[0]->avg_temp,0.0,0.00001);

	if(ret!=-1){
		put_flag = 0;
		push_info_msg(_("You didn't return -1 when the buffer was full and you called put()"));
		set_tag("failure_handling");
	}
	if(len!=5){
		put_flag = 0;
		push_info_msg(_("You modified the variable len but you mustn't do that"));
	}
	if(first!=0){
		put_flag = 0;
		push_info_msg(_("You modified the value pointed to by first while you shouldn't"));
	}
	if(last!=0){
		put_flag = 0;
		push_info_msg(_("You modified the value pointed to by last while you shouldn't when the buffer is full"));
		set_tag("failure_handling");
	}
	if(in!=5){
		put_flag = 0;
		push_info_msg(_("You modified the value pointed to by in while you shouldn't when the buffer is full"));
		set_tag("failure_handling");
	}
	if(buffer[0]->longitude!=0){
		put_flag = 0;
		push_info_msg(_("You modified the buffer while you shouldn't when the buffer is full"));
	}
	if(buffer[0]->latitude!=1){
		put_flag = 0;
		push_info_msg(_("You modified the buffer while you shouldn't when the buffer is full"));
	}
	if(fabs(buffer[0]->avg_temp - 0.0) >= 0.00001){
		put_flag = 0;
		push_info_msg(_("You modified the buffer while you shouldn't when the buffer is full"));
	}

	if(put_flag){
		set_tag("q1");
	}

	clean_buffer(buffer);

}

void test_get_buffer_empty(){
	set_test_metadata("q2", _("Test the get() function when the buffer is empty"), 1);

	int len = 5;
	int first = 0;
	int last = 0;
	int in = 0;

	data_t** buffer = init_buffer(len);
	if(buffer==NULL){
		CU_FAIL();
		return;
	}

	data_t* getRet;

	SANDBOX_BEGIN;

	getRet = get(buffer,len,&first,&last,&in);

	SANDBOX_END;

	CU_ASSERT_PTR_NULL(getRet);
	CU_ASSERT_EQUAL(len,5);
	CU_ASSERT_EQUAL(first,0);
	CU_ASSERT_EQUAL(last,0);
	CU_ASSERT_EQUAL(in,0);

	if(getRet!=NULL){
		get_flag = 0;
		push_info_msg(_("You didn't return NULL when the buffer was empty and you called get()"));
		set_tag("failure_handling");
	}
	if(len!=5){
		get_flag = 0;
		push_info_msg(_("You modified the variable len but you mustn't do that"));
	}
	if(first!=0){
		get_flag = 0;
		push_info_msg(_("You modified the value pointed to by first while you shouldn't"));
		set_tag("failure_handling");
	}
	if(last!=0){
		get_flag = 0;
		push_info_msg(_("You modified the value pointed to by last while you shouldn't"));
	}
	if(in!=0){
		get_flag = 0;
		push_info_msg(_("You modified the value pointed to by in while you shouldn't"));
		set_tag("failure_handling");
	}

	if(get_flag){
		set_tag("q2");
	}

	clean_buffer(buffer);

}

int main(int argc,char** argv)
{
	BAN_FUNCS(set_tag, pthread_create, pthread_mutex_init, sem_init);
	RUN(test_put, test_get, test_put_and_get, test_put_buffer_full, test_get_buffer_empty);
}