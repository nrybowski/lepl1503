#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int longitude;
    int latitude;
    float avg_temp;
} data_t;

int put(data_t** buf, int len, int* first, int* last, int* in, data_t* d);
data_t* get(data_t** buf, int len, int* first, int* last, int* in);