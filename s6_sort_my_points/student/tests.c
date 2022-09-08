#include <stdlib.h>
#include "solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

int flag_sort = 1;

float get_point_over_20() {
    return (rand() % 41)/2.0;
}

void gen_files(int n){

	points_t* array = (points_t*) malloc(sizeof(points_t)*n);
	points_t* good_array = (points_t*) malloc(sizeof(points_t)*n);

    for (int i = 0; i < n; i++){
    	//float randf = (rand() % 41)/2.0;
    	//float r = (randf/RAND_MAX)*20;
    	//points_t p =      {40000000-i, r, r/1.5, r/1.1, r/1.8, r/1.3, 0.0};
    	//points_t good_p = {40000000-i, r, r/1.5, r/1.1, r/1.8, r/1.3, 0.0};
    	points_t p = {40000000-i, get_point_over_20(), get_point_over_20(), get_point_over_20(), get_point_over_20(), get_point_over_20(), 0.0};
    	points_t good_p;
        memcpy(&good_p, &p, sizeof(p));
    	good_p.average = (p.LEPL1103 + p.LEPL1203 + p.LEPL1108 + p.LEPL1302 + p.LEPL1402)/5.0;
        array[i] = p;
        good_array[i] = good_p;
    }
    qsort(good_array,n,sizeof(points_t),&compar_sol);

    int fd = open("file.txt",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd == -1) {
    	free(array);
    	free(good_array);
        push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }
    int fd2 = open("good_file.txt",O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd2 == -1) {
    	free(array);
    	free(good_array);
        push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }


    if(write(fd, array, sizeof(points_t)*n)==-1){
    	free(array);
    	free(good_array);
    	push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }
    if(write(fd2, good_array, sizeof(points_t)*n)==-1){
    	free(array);
    	free(good_array);
    	push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }

    free(array);
    free(good_array);


    if (close(fd) == -1) {
        push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }
    if (close(fd2) == -1) {
        push_info_msg(_("There was an error initialising the test, please contact your tutor or an administrator"));
        return;
    }
}

void test_compare(){
	set_test_metadata("q1", _("Test for compare function"), 1);

	int flag = 1;

	points_t a = {400, 0.0, 0.0, 0.0, 0.0, 0.0, 16.3};
	points_t b = {401, 1.0, 1.0, 1.0, 1.0, 1.0, 14.2};
	points_t c = {402, 2.0, 2.0, 2.0, 2.0, 2.0, 12.6};
	points_t d = {403, 3.0, 3.0, 3.0, 3.0, 3.0, 16.6};

	int ret1=-7;
	int ret2=-7;
	int ret3=-7;
	int ret4=-7;

	SANDBOX_BEGIN;

	ret1 = compar((const void*) &a, (const void*) &b);
	ret2 = compar((const void*) &c, (const void*) &a);
	ret3 = compar((const void*) &b, (const void*) &b);
	ret4 = compar((const void*) &d, (const void*) &a);

	SANDBOX_END;

	CU_ASSERT(ret1 > 0);
	CU_ASSERT(ret2 < 0);
	CU_ASSERT(ret3 == 0);
	CU_ASSERT(ret4 > 0);

	if(ret1 <= 0){
		flag = 0;
		push_info_msg(_("Your function is incorrect if the average of s1 is greater than the average of s2"));
	}
	if(ret2 >= 0){
		flag = 0;
		push_info_msg(_("Your function is incorrect if the average of s1 is less than the average of s2"));
	}
	if(ret3 != 0){
		flag = 0;
		push_info_msg(_("Your function is incorrect if the average of s1 is equal to the average of s2"));
	}
	// Only give this hint if it is the last error
	if(flag && ret4 <= 0){
		flag = 0;
		push_info_msg(_("Your compare function must return an int; do you correctly handle small differences?"));
	}

	if(flag){
		set_tag("q1");
	}
}

void simple_test(){
	set_test_metadata("q2", _("Basic test for sort"), 2);

	int nb_struct = 10;

	gen_files(nb_struct);

    int ret = 0;
    int err = 0;

    monitored.mmap = true; 
    monitored.open = true; 
    monitored.close = true;
    monitored.munmap = true; 
    monitored.fstat = true;
    monitored.msync = true;
    
    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.mmap = false; 
    monitored.open = false; 
    monitored.close = false;
    monitored.munmap = false; 
    monitored.fstat = false;
    monitored.msync = false;

    int fd = open("file.txt",O_RDWR);
    if(fd==-1){
    	CU_FAIL();
    	push_info_msg(_("Internal error when opening the file, please contact your tutor or an administrator"));
    	return;
    }

    struct stat buf;
	err = fstat(fd,&buf);
	if(err==-1){
		close(fd);
		CU_FAIL();
    	push_info_msg(_("Internal error when getting stats from the file, please contact your tutor or an administrator"));
		return;
	}

	err = close(fd);
	if(err==-1){
		CU_FAIL();
    	push_info_msg(_("Internal error when closing the file, please contact your tutor or an administrator"));
		return;
	}

    CU_ASSERT_EQUAL(ret,0);

    CU_ASSERT_EQUAL(stats.open.called, 1);
    CU_ASSERT_EQUAL(stats.close.called, 1);
    CU_ASSERT_EQUAL(stats.fstat.called, 1);
    CU_ASSERT_EQUAL(stats.mmap.called, 1);
    CU_ASSERT_EQUAL(stats.munmap.called, 1);
    CU_ASSERT_EQUAL(stats.msync.called, 1);

    CU_ASSERT_EQUAL(stats.open.last_return, stats.fstat.last_params.fd);
    CU_ASSERT_PTR_NULL(stats.mmap.last_params.addr);
    CU_ASSERT_EQUAL(stats.mmap.last_params.length,sizeof(points_t)*nb_struct);
    CU_ASSERT_EQUAL(stats.mmap.last_params.prot,PROT_READ|PROT_WRITE);
    CU_ASSERT_EQUAL(stats.mmap.last_params.flags,MAP_SHARED);
    CU_ASSERT_EQUAL(stats.mmap.last_params.fd,stats.open.last_return);
    CU_ASSERT_EQUAL(stats.mmap.last_params.offset,0);
    CU_ASSERT_EQUAL(stats.msync.last_params.addr,stats.mmap.last_return);
    CU_ASSERT_EQUAL(stats.msync.last_params.length,sizeof(points_t)*nb_struct);
    CU_ASSERT_EQUAL(stats.msync.last_params.flags,MS_SYNC);
    CU_ASSERT_EQUAL(stats.munmap.last_params.addr,stats.mmap.last_return);
    CU_ASSERT_EQUAL(stats.munmap.last_params.length,sizeof(points_t)*nb_struct);
    CU_ASSERT_EQUAL(stats.close.last_params.fd,stats.open.last_return);

    CU_ASSERT_EQUAL(buf.st_size,sizeof(points_t)*nb_struct);
    
    if(ret != 0){
    	flag_sort = 0;
        push_info_msg(_("You do not return the correct value when everything is fine"));
    }   
    if(stats.open.called != 1) {
    	flag_sort = 0;
        push_info_msg(_("You should call open exactly once"));
    }
    if(stats.close.called != 1) {
    	flag_sort = 0;
        push_info_msg(_("You should call close exactly once"));
    }
    if(stats.fstat.called != 1) {
    	flag_sort = 0;
        push_info_msg(_("You should call fstat exactly once"));
    }
    if(stats.mmap.called != 1){
		flag_sort = 0;
        push_info_msg(_("You should call mmap exactly once"));
    }
    if(stats.munmap.called != 1){
		flag_sort = 0;
        push_info_msg(_("You should call munmap exactly once"));
    }
    if(stats.msync.called != 1){
		flag_sort = 0;
        push_info_msg(_("You should call msync exactly once"));
    }
    if(buf.st_size != sizeof(points_t)*nb_struct){
    	flag_sort = 0;
    	push_info_msg(_("There is not enough structures in the file, you didn't write them correctly"));
    }    
    if(system("diff file.txt good_file.txt") != 0){
		flag_sort = 0;
        push_info_msg(_("You didn't sort the structures correctly"));
        CU_FAIL();
    }
    if(stats.open.last_return!=stats.fstat.last_params.fd){
    	flag_sort = 0;
        push_info_msg(_("You don't call fstat on the same file descriptor as the one returned by open()"));
    }
    if(stats.mmap.last_params.addr != NULL){
		flag_sort = 0;
        push_info_msg(_("You don't have to specify an address for mmap, just use NULL"));    	
    }
    if(stats.mmap.last_params.length!=sizeof(points_t)*nb_struct){
    	flag_sort = 0;
        push_info_msg(_("You don't call mmap with the right length"));
    }
    if(stats.mmap.last_params.prot!=(PROT_READ|PROT_WRITE)){
    	flag_sort = 0;
        push_info_msg(_("You don't call mmap with the right protections"));
    }
    if(stats.mmap.last_params.flags!=MAP_SHARED){
    	flag_sort = 0;
        push_info_msg(_("You don't call mmap with the right flags"));
    }
    if(stats.mmap.last_params.fd!=stats.open.last_return){
    	flag_sort = 0;
        push_info_msg(_("You don't call mmap with the right file descriptor"));
    }
    if(stats.mmap.last_params.offset!=0){
    	flag_sort = 0;
        push_info_msg(_("You don't need to specify an offset when calling mmap, just use 0"));
    }
    if(stats.msync.last_params.addr!=stats.mmap.last_return){
    	flag_sort = 0;
        push_info_msg(_("You don't call msync on the address returned by mmap()"));
    }
    if(stats.msync.last_params.length!=sizeof(points_t)*nb_struct){
    	flag_sort = 0;
        push_info_msg(_("You don't call msync with the right length"));
    }
    if(stats.msync.last_params.flags!=MS_SYNC){
    	flag_sort = 0;
        push_info_msg(_("You don't call msync with the right flags, you have to ensure that the file is updated BEFORE calling munmap"));
    }
    if(stats.munmap.last_params.addr!=stats.mmap.last_return){
    	flag_sort = 0;
        push_info_msg(_("You don't call munmap on the address returned by mmap()"));
    }
    if(stats.munmap.last_params.length!=sizeof(points_t)*nb_struct){
    	flag_sort = 0;
        push_info_msg(_("You don't call munmap with the right length"));
    }
    if(stats.close.last_params.fd!=stats.open.last_return){
    	flag_sort = 0;
        push_info_msg(_("You don't call close on the file descriptor returned by open()"));
    }
}

void cpu_test(){
	set_test_metadata("q2", _("Hard test for sort"), 10);

	int nb_struct = 1000000;

	gen_files(nb_struct);

	int ret;

	struct timespec before;
	struct timespec after;

	time_t sec = 0;
	long nano = 0;
    int clockerr;
    int clockerr2;

	SANDBOX_BEGIN;

	clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &before);
	ret = sort("file.txt");
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &after);

	SANDBOX_END;

	CU_ASSERT_EQUAL(ret,0);

	if(ret!=0){
		flag_sort = 0;
        push_info_msg(_("You do not return the correct value when everything is fine"));
	}
	if(system("diff file.txt good_file.txt") != 0){
		flag_sort = 0;
        push_info_msg(_("You didn't sort the structures correctly"));
        CU_FAIL();
        return;
    }

    if (clockerr == 0 && clockerr2 == 0){
		sec = after.tv_sec - before.tv_sec;
		nano = after.tv_nsec - before.tv_nsec;
	}
    else{
        CU_FAIL("Can't get time used for the CPU_test");
        push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        return;
    }    
    float studtime = ((float) nano)/1000000000 + (float) sec;

    gen_files(nb_struct);

    clockerr = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &before);
	ret = sort_sol("file.txt");
	clockerr2 = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &after);

	if (clockerr == 0 && clockerr2 == 0){
		sec = after.tv_sec - before.tv_sec;
		nano = after.tv_nsec - before.tv_nsec;
	}
    else{
        CU_FAIL("Can't get time used for the CPU_test");
        push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        return;
    }
    
    float soltime = ((float) nano)/1000000000 + (float) sec;

    FILE* file = fopen("cpu.txt", "w+");
    if(file==NULL){
        CU_FAIL("Can't open cpu.txt");
    	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        return;
    }
    int check = fprintf(file,"%2.6f\n",studtime);
    if(check <= 0){
        CU_FAIL("Can't write to cpu.txt");
    	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        fclose(file);
        return;
    }
    check = fclose(file);
    if(check==EOF){
        CU_FAIL("Can't close cpu.txt");
    	push_info_msg(_("The test encountered an error, please contact your tutor or an administrator."));
        return;
    }
    
    if(studtime > 2.0*soltime){
        CU_FAIL();
        flag_sort = 0;
        char* str = _("Your solution seems to take a lot of time compared to our solution. Maybe you should think about a better way to solve the problem because it is really important to save as much CPU time as you can when you write programs. Your solution took %2.6f sec while our solution took %2.6f sec.");
        char strmsg[strlen(str)+30];
        sprintf(strmsg,str,studtime,soltime);
        push_info_msg(strmsg);
    }
}

void test_open_fail(){
    set_test_metadata("q2", _("Test open fails"), 1);

    int ret;

    monitored.open = true;
    failures.open=FAIL_FIRST;
    failures.open_ret = -1;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.open = false;

    CU_ASSERT_EQUAL(ret,-1);

    if(ret!=-1){
    	push_info_msg(_("You don't return -1 when open fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }
}

void test_mmap_fail(){
    set_test_metadata("q2", _("Test mmap fails"), 1);

    int ret;

    monitored.mmap = true;
    monitored.close = true;
    failures.mmap=FAIL_FIRST;
    failures.mmap_ret = MAP_FAILED;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.mmap = false;
    monitored.close = false;

    CU_ASSERT_EQUAL(ret,-2);
    CU_ASSERT_EQUAL(stats.close.called,1)

    if(ret!=-2){
    	push_info_msg(_("You don't return -2 when mmap fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }
    if(stats.close.called!=1){
    	set_tag("failure_handling");
    	flag_sort = 0;
    	push_info_msg(_("You don't close the file descriptor when mmap fails"));
    }
}

void test_munmap_fail(){
    set_test_metadata("q2", _("Test munmap fails"), 1);

    int ret;

    monitored.munmap = true;
    failures.munmap=FAIL_FIRST;
    failures.munmap_ret = -1;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.munmap = false;

    CU_ASSERT_EQUAL(ret,-3);

    if(ret!=-3){
    	push_info_msg(_("You don't return -3 when munmap fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }
}

void test_msync_fail(){
    set_test_metadata("q2", _("Test msync fails"), 1);

    int ret;

    monitored.msync = true;
    monitored.munmap = true;
    failures.msync=FAIL_FIRST;
    failures.msync_ret = -1;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.msync = false;
    monitored.munmap = false;

    CU_ASSERT_EQUAL(ret,-4);
    CU_ASSERT_EQUAL(stats.munmap.called,1);

    if(ret!=-4){
    	push_info_msg(_("You don't return -4 when msync fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }
    if(stats.munmap.called!=1){
    	set_tag("failure_handling");
    	flag_sort = 0;
    	push_info_msg(_("You don't call munmap when the call to msync fails"));
    }
}

void test_fstat_fail(){
    set_test_metadata("q2", _("Test fstat fails"), 1);

    int ret;

    monitored.fstat = true;
    monitored.close = true;
    failures.fstat=FAIL_FIRST;
    failures.fstat_ret = -1;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.fstat = false;
    monitored.close = false;

    CU_ASSERT_EQUAL(ret,-5);
    CU_ASSERT_EQUAL(stats.close.called,1);

    if(ret!=-5){
    	push_info_msg(_("You don't return -5 when fstat fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }
    if(stats.close.called!=1){
    	set_tag("failure_handling");
    	flag_sort = 0;
    	push_info_msg(_("You don't close the file descriptor when fstat fails"));
    }
}

void test_close_fail(){
    set_test_metadata("q2", _("Test close fails"), 1);

    int ret;

    monitored.close = true;
    failures.close=FAIL_FIRST;
    failures.close_ret = -1;

    gen_files(1);

    SANDBOX_BEGIN;

    ret = sort("file.txt");

    SANDBOX_END;

    monitored.close = false;

    CU_ASSERT_EQUAL(ret,-6);

    if(ret!=-6){
    	push_info_msg(_("You don't return -6 when close fails"));
    	set_tag("failure_handling");
    	flag_sort = 0;
    }

    if(flag_sort){
        set_tag("q2");
    }
}

int main(int argc,char** argv)
{
	BAN_FUNCS(set_tag, read, write, fread, fwrite, fopen, fclose);
	RUN(test_compare, simple_test, cpu_test, test_open_fail, test_fstat_fail, test_mmap_fail, test_munmap_fail, test_msync_fail, test_close_fail);
}