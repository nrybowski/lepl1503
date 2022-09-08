#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "student_code.h"

@@auxiliary@@


int AddStuff(consumer_t* client, char* name, unsigned int price){
	@@addstuff@@
}

 consumer_t * NewConsumer(char* name, unsigned int bagSize, unsigned int budget, char * lst[], unsigned int size){
    consumer_t * consumer = (consumer_t *) malloc(sizeof(consumer_t));
    if(consumer == NULL){
        return NULL;
    }
    consumer->bag = NULL;
    consumer->name = name;
    consumer->total = 0;
    consumer->bagSize = bagSize;
    consumer->dontLike = lst;
    consumer->size = size;
    consumer->budget = budget;
    return consumer;
}


