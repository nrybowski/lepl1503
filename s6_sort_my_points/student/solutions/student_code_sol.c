#include "student_code_sol.h"

int compar_sol(const void* s1, const void* s2){
	points_t* first = (points_t*) s1;
	points_t* second = (points_t*) s2;

	if(first->average < second->average){
		return -1;
	}
	else if(first->average == second->average){
		return 0;
	}
	else{
		return 1;
	}
}

int sort_sol(char* filename){
	int fd = open(filename, O_RDWR);
	if(fd==-1){
		return -1;
	}

	struct stat buf;
	int ret = fstat(fd,&buf);
	if(ret==-1){
		close(fd);
		return -5;
	}

	void* addr = mmap(NULL, buf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr==MAP_FAILED){
		close(fd);
		return -2;
	}
	points_t* array = (points_t*) addr;

	int nb = buf.st_size/sizeof(points_t);
	for(int i = 0; i < nb; i++){
		array[i].average = (array[i].LEPL1103 + array[i].LEPL1203 + array[i].LEPL1108 + array[i].LEPL1302 + array[i].LEPL1402)/5.0;
	}
	qsort(addr,nb,sizeof(points_t),&compar_sol);

	ret = msync(addr, buf.st_size, MS_SYNC);
	if(ret==-1){
		close(fd);
		munmap(addr, buf.st_size);
		return -4;
	}

	ret = munmap(addr, buf.st_size);
	if(ret==-1){
		close(fd);
		return -3;
	}

	ret = close(fd);
	if(ret==-1){
		return -6;
	}

	return 0;
}