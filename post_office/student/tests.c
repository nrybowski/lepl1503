#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

char *str_letter(letter_t *letter){
    if (letter == NULL){
        char *temp = malloc(9);
        sprintf(temp, "Letter()");
        return temp;
    }
    char *letter_msg = "Letter(continent : %d, priority : %d, name : %c)";
    char *ret = malloc(strlen(letter_msg) + 10);
    sprintf(ret, letter_msg, letter->continent, letter->priority, letter->name);
    return ret;
}

char *str_queue(queue_t *queue){
    char *res = malloc(2000);
    sprintf(res, "Queue (size = %d) ", queue->size);
    strcat(res, "[");
    letter_t *curr = queue->front;
    for (int i = 0; i< queue->size; i++){
        char *temp = str_letter(curr);
        strcat(res, temp);
        if (i < queue->size - 1) strcat(res, ", ");
        free(temp);
        curr = curr->next;
    }
    strcat(res, "]");
    return res;
}

void error_queue(char *exp, queue_t *res, letter_t *new){
    char *error = "Wrong queue : initial %s when pushing %s, but you returned %s";
    char msg[strlen(error) + 2000];
    char *ret_str = str_queue(res);
    char *letter = str_letter(new);
    sprintf(msg, error, exp, letter, ret_str);
    free(ret_str);
    free(letter);
    push_info_msg(msg);
}

//test dequeue of empty queue case
void test_dequeue_1(){
    set_test_metadata("dequeue", _("Dequeue in an empty queue"), 1);
	//letter_t *empty = NULL;
	queue_t *q = init_queue();
	letter_t *res;
    SANDBOX_BEGIN;
    res = dequeue(q);
    SANDBOX_END;
	//CU_ASSERT_EQUAL(empty,res);
	CU_ASSERT_PTR_NULL(res);
	free(q);
}

//test dequeue for queue with one element -> correct redefinition of front and rear
void test_dequeue_2(){
    set_test_metadata("dequeue", _("Redefinition of front and rear when dequeuing a queue with 1 letters"), 1);
	queue_t *q = init_queue();
	letter_t *elem = malloc(sizeof(letter_t));
	elem->continent = 0;
	elem->priority = 1;
	elem->name = 'A';
	elem->next = NULL;
	q->front = elem;
	q->rear = elem;
	q->size = 1;
    SANDBOX_BEGIN;
    dequeue(q);
    SANDBOX_END;
	CU_ASSERT_PTR_NULL(q->front);
	CU_ASSERT_PTR_NULL(q->rear);
    if (q->front != NULL || q->rear != NULL) push_info_msg("You forgot to set rear and front to NULL when removing last element");
	free(q);
	free(elem);
}

//test size managment of one element queue
void test_dequeue_3(){
    set_test_metadata("dequeue", _("Update of queue size when dequeuing a queue with 1 letters"), 1);
	queue_t *q = init_queue();
	letter_t *elem = malloc(sizeof(letter_t));
	elem->continent = 0;
	elem->priority = 1;
	elem->name = 'A';
	elem->next = NULL;
	q->front = elem;
	q->rear = elem;
	q->size = 1;
    SANDBOX_BEGIN;
    dequeue(q);
    SANDBOX_END;
	int expected_size = 0;
	CU_ASSERT_EQUAL(expected_size,q->size);
    if (expected_size != q->size) push_info_msg("Dont forget to decrement size when removing an element");
	free(q);
	free(elem);
}

//test dequeue for queue with two element -> correct redefinition of front and rear
void test_dequeue_4(){
    set_test_metadata("dequeue", _("Redefinition of front and rear when dequeuing a queue with 2 letters"), 1);
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	front->continent = 0;
	front->priority = 1;
	front->name = 'A';
	letter_t *rear = malloc(sizeof(letter_t));
	rear->continent = 3;
	rear->priority = 0;
	rear->name = 'B';
	front->next = rear;
	rear->next = NULL;
	q->front = front;
	q->rear = rear;
	q->size = 2;
    SANDBOX_BEGIN;
    dequeue(q);
    SANDBOX_END;
	char expected_front = 'B';
	char expected_rear = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name )push_info_msg("Don't forget to update front and rear");
	free(q);
	free(front); free(rear);
}


//test size managment of regular queue (q->size-- after dequeuing)
void test_dequeue_5(){
    set_test_metadata("dequeue", _("Update of queue size when dequeuing a queue with 3 letters"), 1);
	int expected_res = 2;
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	letter_t *middle = malloc(sizeof(letter_t));
	letter_t *rear = malloc(sizeof(letter_t));
	front->continent = 0;
	front->priority = 1;
	front->name = 'A';
	front->next = middle;
	middle->continent = 2;
	middle->priority = 1;
	middle->name = 'B';
	middle->next = rear;
	rear->continent = 1;
	rear->priority = 0;
	rear->name = 'C';
	rear->next = NULL;
	q->front = front;
	q->rear = rear;
	q->size = 3;
    SANDBOX_BEGIN;
    dequeue(q);
    SANDBOX_END;
	CU_ASSERT_EQUAL(expected_res,q->size);
    if (expected_res != q->size) push_info_msg("Dont forget to decrement size when removing an element");
	free(q);
	free(front); free(middle); free(rear);
}

//test dequeued element (correct position -> FIFO) for regular queue
void test_dequeue_6(){
    set_test_metadata("dequeue", _("Dequeuing correct element from a queue with 3 letters (FIFO)"), 1);
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	letter_t *middle = malloc(sizeof(letter_t));
	letter_t *rear = malloc(sizeof(letter_t));
	front->continent = 0;
	front->priority = 1;
	front->name = 'A';
	front->next = middle;
	middle->continent = 2;
	middle->priority = 1;
	middle->name = 'B';
	middle->next = rear;
	rear->continent = 1;
	rear->priority = 0;
	rear->name = 'C';
	rear->next = NULL;
	q->front = front;
	q->rear = rear;
	q->size = 3;
    letter_t temp;
	letter_t *dequeued = &temp;
    SANDBOX_BEGIN;
    dequeued = dequeue(q);
    SANDBOX_END;
	char expected_name = 'A';
	CU_ASSERT_EQUAL(expected_name,dequeued->name);
    if (expected_name != dequeued->name) push_info_msg("You didn't dequeue the correct letter");
	free(q);
	free(front); free(middle); free(rear);
}


//test if front is correctly redefined for regular queue
void test_dequeue_7(){
    set_test_metadata("dequeue", _("Redefinition of front when dequeuing a queue with 3 letters"), 1);
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	letter_t *middle = malloc(sizeof(letter_t));
	letter_t *rear = malloc(sizeof(letter_t));
	front->continent = 0;
	front->priority = 1;
	front->name = 'A';
	front->next = middle;
	middle->continent = 2;
	middle->priority = 1;
	middle->name = 'B';
	middle->next = rear;
	rear->continent = 1;
	rear->priority = 0;
	rear->name = 'C';
	rear->next = NULL;
	q->front = front;
	q->rear = rear;
	q->size = 3;
    SANDBOX_BEGIN;
    dequeue(q);
    SANDBOX_END;
	char expected_front = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
    if (expected_front != q->front->name) push_info_msg("You didn't update front correctly");
	free(q);
	free(front); free(middle); free(rear);
}

//test to verify size after enqueuing a letter to an empty queue
void test_enqueue_1(){
    set_test_metadata("priority_enqueue", _("Update of queue size when enqueuing to an empty queue"), 1);
	queue_t *q = init_queue();
	letter_t *elem = malloc(sizeof(letter_t));
	elem->continent = 0;
	elem->name = 'A';
	elem->next = NULL;
	elem->priority = 0;
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	int expected_size = 1;
	CU_ASSERT_EQUAL(expected_size,q->size);
    if (expected_size != q->size) push_info_msg("You have to increment the size when enqueing");
	free(q);
	free(elem);
}

//test to verify the definition of the front and rear after enqueuing a letter to an empty list
void test_enqueue_2(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear after enqueuing a letter to an empty queue"), 1);
	queue_t *q = init_queue();
	letter_t *elem = malloc(sizeof(letter_t));
	elem->continent = 0;
	elem->name = 'A';
	elem->next = NULL;
	elem->priority = 0;
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_res = 'A';
	CU_ASSERT_EQUAL(expected_res,q->front->name);
	CU_ASSERT_EQUAL(expected_res,q->rear->name);
    if (expected_res != q->front->name || expected_res != q->rear->name) push_info_msg("You don't update front and rear correctly");
	free(q);
	free(elem);
}

//test to verify size after enqueuing a letter to a queue with one elment already in it 
void test_enqueue_3(){
    set_test_metadata("priority_enqueue", _("Update of queue size when enqueuing to a queue with 1 element"), 1);
	queue_t *q = init_queue();
	letter_t *in_queue = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	in_queue->continent = 0;
	in_queue->name = 'A';
	in_queue->priority = 0;
	elem->continent = 0;
	elem->name = 'B';
	elem->priority = 0;
	q->front = in_queue;
	q->rear = in_queue;
	q->size = 1;

    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	int expected_size = 2;
	CU_ASSERT_EQUAL(expected_size,q->size);
    if (expected_size != q->size) error_queue(queue_str, q, elem);
	free(q);
	free(elem); free(in_queue);
    free(queue_str);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITHOUT priority in a queue 
*that already has an element WITHOUT priority in it 
*/
void test_enqueue_4(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter without priority in a queue that has a letter without priority"), 1);
	queue_t *q = init_queue();
	letter_t *in_queue = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	in_queue->continent = 0;
	in_queue->name = 'A';
	in_queue->priority = 0;
	elem->continent = 0;
	elem->name = 'B';
	elem->priority = 0;
	q->front = in_queue;
	q->rear = in_queue;
	q->size = 1;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'A';
	char expected_rear = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name) error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(in_queue);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITH priority in a queue 
*that already has an element WITHOUT priority in it 
*/
void test_enqueue_5(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter with priority in a queue that has a letter without priority"), 1);
	queue_t *q = init_queue();
	letter_t *in_queue = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	in_queue->continent = 0;
	in_queue->name = 'A';
	in_queue->priority = 0;
	elem->continent = 0;
	elem->name = 'B';
	elem->priority = 1;
	q->front = in_queue;
	q->rear = in_queue;
	q->size = 1;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'B';
	char expected_rear = 'A';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name ) error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(in_queue);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITHOUT priority in a queue 
*that already has an element WITH priority in it 
*/
void test_enqueue_6(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter without priority in a queue that has a letter with priority"), 1);
	queue_t *q = init_queue();
	letter_t *in_queue = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	in_queue->continent = 0;
	in_queue->name = 'A';
	in_queue->priority = 1;
	elem->continent = 0;
	elem->name = 'B';
	elem->priority = 0;
	q->front = in_queue;
	q->rear = in_queue;
	q->size = 1;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'A';
	char expected_rear = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if(expected_front != q->front->name || expected_rear != q->rear->name) error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(in_queue);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITH priority in a queue 
*that already has an element WITH priority in it 
*/
void test_enqueue_7(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter with priority in a queue that has a letter with priority"), 1);
	queue_t *q = init_queue();
	letter_t *in_queue = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	in_queue->continent = 0;
	in_queue->name = 'A';
	in_queue->priority = 1;
	elem->continent = 0;
	elem->name = 'B';
	elem->priority = 1;
	q->front = in_queue;
	q->rear = in_queue;
	q->size = 1;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'A';
	char expected_rear = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name)error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(in_queue);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITHOUT priority in a queue 
*that already has 2 elements. The first element in the queue has priority, the second doesn't 
*/
void test_enqueue_8(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter withouth priority in a queue with 2 letters. The first has priority, the second doesn't"), 1);
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	letter_t *rear = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	front->continent = 0;
	front->name = 'A';
	front->priority = 1;
	rear->continent = 0;
	rear->name = 'B';
	rear->priority = 0;
	elem->continent = 0;
	elem->name = 'C';
	elem->priority = 0;
	front->next = rear;
	q->front = front;
	q->rear = rear;
	q->size = 2;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'A';
	char expected_rear = 'C';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name)error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(front); free(rear);
}

/*
*test to verify the correct redefinition of front and rear when enqueuing an element WITH priority in a queue 
*that already has 2 elements. The first element in the queue has priority, the second doesn't 
*/
void test_enqueue_9(){
    set_test_metadata("priority_enqueue", _("Redefinition of front and rear when enqueuing a letter with priority in a queue with 2 letters. The first has priority, the second doesn't"), 1);
	queue_t *q = init_queue();
	letter_t *front = malloc(sizeof(letter_t));
	letter_t *rear = malloc(sizeof(letter_t));
	letter_t *elem = malloc(sizeof(letter_t));
	front->continent = 0;
	front->name = 'A';
	front->priority = 1;
	rear->continent = 0;
	rear->name = 'B';
	rear->priority = 0;
	elem->continent = 0;
	elem->name = 'C';
	elem->priority = 1;
	front->next = rear;
	q->front = front;
	q->rear = rear;
	q->size = 2;
    char *queue_str = str_queue(q);
    SANDBOX_BEGIN;
	priority_enqueue(q,elem);
    SANDBOX_END;
	char expected_front = 'A';
	char expected_rear = 'B';
	CU_ASSERT_EQUAL(expected_front,q->front->name);
	CU_ASSERT_EQUAL(expected_rear,q->rear->name);
    if (expected_front != q->front->name || expected_rear != q->rear->name)error_queue(queue_str, q, elem);
	free(q); free(queue_str);
	free(elem); free(front); free(rear);
}

//test to verify if function returns -1 when the letter is NULL
void test_enqueue_10(){
    set_test_metadata("priority_enqueue", _("Return -1 when @letter is NULL"), 1);
	queue_t *q = init_queue();
	letter_t *toEnqueue = NULL;
	int res;
    SANDBOX_BEGIN;
    res = priority_enqueue(q,toEnqueue);
    SANDBOX_END;
	int expected_res = -1;
	CU_ASSERT_EQUAL(expected_res,res);
    if (expected_res != res) push_info_msg("You have to return -1 when letter is NULL");
	free(q);
}


//test to verify if the letter dequeued from the post office queue is enqueued in the correct "continent queue"
void test_process_letters_1(){
    set_test_metadata("process_letters", _("Dequeued letter from the post office queue is enqueued in the correct continent queue"), 1);
	queue_t *post_office_q = init_queue();
	queue_t **continent_queues = malloc(sizeof(queue_t*)*5);
	for(int i = 0; i < 5; i++) {
		continent_queues[i] = init_queue();
	}
	letter_t *elem = malloc(sizeof(letter_t));
	elem->continent = 2;
	elem->name = 'A';
	elem->priority = 0;
	post_office_q->front = elem;
	post_office_q->rear = elem;
	post_office_q->size = 1;
	char expected_name = 'A';
    SANDBOX_BEGIN;
	process_letters(post_office_q,continent_queues);
    SANDBOX_END;
	CU_ASSERT_EQUAL(expected_name,continent_queues[2]->front->name);
    if (expected_name != continent_queues[2]->front->name) push_info_msg("Erreur dans la fonction");
	free(elem);
	free(post_office_q);
	for(int i = 0; i < 5; i++) {
		free(continent_queues[i]);
	}
	free(continent_queues);
}

//test to verify if function returns -1 when the post queue is empty
void test_process_letters_2(){
    set_test_metadata("process_letters", _("Function returns -1 when the post office queue is empty"), 1);
	queue_t *post_office_q = init_queue();
	queue_t **continent_queues = malloc(sizeof(queue_t*)*5);
	for(int i = 0; i < 5; i++) {
		continent_queues[i] = init_queue();
	}
	int res;
    SANDBOX_BEGIN;
    res = process_letters(post_office_q,continent_queues);
    SANDBOX_END;
	int expected_res = -1;
	CU_ASSERT_EQUAL(expected_res,res);
    if (expected_res != res) push_info_msg("You should return -1 when the post office queue is empty");
	free(post_office_q);
	for(int i = 0; i < 5; i++) {
		free(continent_queues[i]);
	}
	free(continent_queues);
}

//test to verify if the function works properly on a "general" case
void test_process_letters_3(){
    set_test_metadata("process_letters", _("General case"), 1);
	char names[14] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};
	int continents_list[14] = {4,4,0,0,0,0,2,2,3,3,3,4,4,1};
	int priority_list[14] = {0,1,0,0,0,1,1,0,0,1,1,0,1,0};

	letter_t *letters_list = malloc(sizeof(letter_t)*14);
	for(int i = 0; i < 14; i++){
		//letters_list[i] = malloc
		(letters_list[i]).continent = continents_list[i];
		(letters_list[i]).priority = priority_list[i];
		(letters_list[i]).name = names[i];
	} 

	queue_t *post_queue = malloc(sizeof(queue_t));
	queue_t **continent_queues = malloc(sizeof(queue_t*)*5);
	for(int i = 0; i < 5; i++) {
		continent_queues[i] = malloc(sizeof(queue_t));
		continent_queues[i]->size = 0;
	}

	post_queue->front = &letters_list[0];
	post_queue->rear = &letters_list[0];
	post_queue->size = 1;

	for(int i = 1; i < 14; i++){
		post_queue->rear->next = &letters_list[i];
		post_queue->rear = post_queue->rear->next;
		post_queue->size++;
	}

    int flag = 1;

    char *queue_str = str_queue(post_queue);

    SANDBOX_BEGIN;
	process_letters(post_queue,continent_queues);
    SANDBOX_END;

	char expected_res_Africa[4] = {'B','M','A','L'};
	char expected_res_Europe[4] = {'F','C','D','E'};
	char expected_res_Asia[2] = {'G','H'};
	char expected_res_Oceania[3] = {'J','K','I'};
	char expected_res_America[1] = {'N'};

	char *res_Africa = malloc(sizeof(char)*10);
	char *res_Europe = malloc(sizeof(char)*10);
	char *res_Asia = malloc(sizeof(char)*10);
	char *res_Oceania = malloc(sizeof(char)*10);
	char *res_America = malloc(sizeof(char));
	char **res = malloc(sizeof(char*)*5);
	res[0] = res_Europe; res[1] = res_America; res[2] = res_Asia; res[3] = res_Oceania; res[4] = res_Africa;

	for(int i = 0; i < 5; i++) {
		int k = 0;
		while((continent_queues[i]->size > 0) && (k<5)){
            SANDBOX_BEGIN;
			res[i][k] = dequeue(continent_queues[i])->name;
            SANDBOX_END;
			k++;
		}
	}

	for(int i = 0; i < 4; i++){
		CU_ASSERT_EQUAL(expected_res_Europe[i],res_Europe[i]);
        if (expected_res_Europe[i] != res_Europe[i]) flag = 0;
	}
	CU_ASSERT_EQUAL(expected_res_America[0],res_America[0]);
	for(int i = 0; i < 2; i++){
		CU_ASSERT_EQUAL(expected_res_Asia[i],res_Asia[i]);
        if (expected_res_Asia[i] != res_Asia[i]) flag = 0;
	}
	for(int i = 0; i < 3; i++){
		CU_ASSERT_EQUAL(expected_res_Oceania[i],res_Oceania[i]);
        if (expected_res_Oceania[i] != res_Oceania[i]) flag = 0;
	}
	for(int i = 0; i < 4; i++){
		CU_ASSERT_EQUAL(expected_res_Africa[i],res_Africa[i]);
        if (expected_res_Africa[i] != res_Africa[i]) flag = 0;
	}

    if (!flag){
        push_info_msg("You did some errors in the queue");
    }

	free(res_Africa); free(res_Oceania); free(res_Asia), free(res_America); free(res_Europe);
	free(post_queue);
    free(queue_str);
	for(int i = 0; i < 5; i++){
		free(continent_queues[i]);
	}
	free(continent_queues);
	free(res);
	free(letters_list);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_dequeue_1, test_dequeue_2, test_dequeue_3, test_dequeue_4, test_dequeue_5, test_dequeue_6, test_dequeue_7, test_enqueue_1, test_enqueue_2, test_enqueue_3
    , test_enqueue_4, test_enqueue_5, test_enqueue_6, test_enqueue_7, test_enqueue_8, test_enqueue_9, test_enqueue_10 ,test_process_letters_1, test_process_letters_2, test_process_letters_3);
}
