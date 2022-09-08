#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int priority_enqueue_sol(queue_t* q, letter_t* letter){
	if(letter == NULL) {
		return -1;
	}

	if(q->size == 0){
		q->front = letter; 
		q->rear = q->front; 
		q->size++;
		return 0;
	}
	if((q->size == 1) && (q->front->priority == 1)){
		q->front->next = letter;
		q->rear = q->front->next;
		q->size++;
		return 0;
	}
	if((q->size == 1) && (q->front->priority == 0)){
		if(letter->priority == 1) {
			letter->next = q->front;
			q->rear = q->front;
			q->front = letter;
			q->size++;
			return 0;
		}
		q->front->next = letter;
		q->rear = letter;
		q->size++;
		return 0;

	}
	if(letter->priority == 0){ //no priority
		q->rear->next = letter;
		q->rear = q->rear->next;
		q->size++;
		return 0;
	}
	//priority
	if(q->front->priority == 0) {
		letter->next = q->front;
		q->front = letter; 
		q->size++;
		return 0;
	}
	if((q->front->priority == 1) && (q->front->next->priority == 0)){
		letter->next = q->front->next;
		q->front->next = letter;
		q->size++;
		return 0;
	}
	letter_t *priority_rear = q->front->next;
	while(priority_rear->next->priority != 0) {
		priority_rear = priority_rear->next;
	}
	priority_rear->next = letter;
	letter->next = priority_rear->next->next;
	q->size++;
	return 0;
}

letter_t *dequeue_sol(queue_t* q){
	if(q->size == 0){
		return NULL;
	}

	letter_t *temp;
	if(q->size == 1){
		temp = q->front;
		q->front = NULL;
		q->rear = NULL;
		q->size = 0;
		return temp;
	}
	temp = q->front;
	q->front = q->front->next;
	q->size--;
	return temp;
}

int process_letters_sol(queue_t* post_office_queue ,queue_t** continents_queue){
	if(post_office_queue->size == 0){
		return -1; 
	}
	while(post_office_queue->size != 0) {
		letter_t *toSend = dequeue(post_office_queue);
		priority_enqueue(continents_queue[toSend->continent],toSend);
	}
	return 0;
}
