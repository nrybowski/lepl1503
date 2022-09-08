#include<stdio.h>
#include<stdlib.h>
#include "student_code.h"

queue_t* init_queue(){
	queue_t *q = malloc(sizeof(queue_t));
	q->size = 0;
	return q;
}

int priority_enqueue(queue_t* q, letter_t* letter){
	@@priority_enqueue@@
}

letter_t *dequeue(queue_t* q){
	@@dequeue@@
}

int process_letters(queue_t* post_office_queue ,queue_t** continents_queue){
	@@process_letters@@
}