#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

typedef struct points {
    int NOMA;
    float LEPL1103;
    float LEPL1203;
    float LEPL1108;
    float LEPL1302;
    float LEPL1402;
    float average;
} points_t;

int compar(const void* s1, const void* s2);
int sort(char* filename);