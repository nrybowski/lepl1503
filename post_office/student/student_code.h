#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
* Continent: 0 if Europe
*            1 if America
*            2 if Asia
*            3 if Oceania
*            4 if Africa
*
* Priority: 0 if no priority stamp
*           1 if priority stamp
*/
typedef struct letter {
	int continent;
	int priority;
	char name;
	struct letter* next; //from front of the queue to the back of the queue 
} letter_t;

typedef struct queue {
	letter_t* front;
	letter_t* rear;
	int size;
} queue_t;


/*
* Add @letter to @q by respecting the priority order 
* -> letters with a priority stamp are always in front of letters without it
* -> the FIFO order is respected amongst the letters with priority and amongst the letters without it
*
* @letter  : the letter to enqueue
* @q      : the queue
*
* @return 0 if no error, -1 otherwise
*
* pre : the queue q will always be valid, you don't have to handle the NULL case
*/
int priority_enqueue(queue_t* q, letter_t* letter);




/*
* Dequeue a letter from the front of @q 
* 
* @q : the queue
*
* @return the letter dequeued from @q if the queue isn't empty, NULL otherwise
*
* pre : the queue q will always be valid, you don't have to handle the NULL case
*/
letter_t *dequeue(queue_t* q);




/*
* Dequeue letters from @post_office_queue and enqueue them in the correct queue of the @continents_queue array
* 
* @post_office_queue : the queue from which you have to dequeue
* @continents_queue  : the array of continents queues
*
* @return 0 if no error, -1 otherwise
*
* pre : the queues will always be valid, you don't have to handle the NULL case
*/
int process_letters(queue_t* post_office_queue ,queue_t** continents_queue);

queue_t* init_queue();


//------------------------------------------------------------------------------


/*
* Helper function
*/

