#include <stdlib.h>
#include <string.h>
#include "student_code.h"
#include "linked_list.h"
#include "../../course/common/student/CTester/CTester.h"

int filter_function(int a){
	if(a%2 != 0){
		return 0;
	}
	return 1;
}

char *str_list(list_t *list){
    if (list==NULL){
        char *temp = "NULL";
        char *ret = malloc(strlen(temp)+1);
        strcpy(ret, temp);
        return ret;
    }
    char *ret = malloc(list->size*4);
    node_t *curr = list->first;
    strcpy(ret, "[");
    for (int i = 0; i<list->size; i++){
        char *value= i == list->size - 1 ? "%d" : "%d, ";
        char temp[strlen(value)];
        sprintf(temp, value, curr->value);
        strcat(ret, temp);
        curr = curr->next;
    }
    strcat(ret, "]");
    return ret;

}

typedef enum function{PRED, MODIF} function_t;

void error(list_t *ret, char *init, function_t function){
	char *err = _("You didn't apply the modifications correctly. With the list %s and function %s, you returned %s");
	char *ret_str = str_list(ret);
	char *f;
	switch(function){
		case PRED:
			f = "(elem) -> return elem\%2==0";
			break;
		case MODIF:
			f = "(elem) -> return elem+3";
	}
	char msg[strlen(err) + strlen(ret_str) + strlen(f) + strlen(init)];
	sprintf(msg, err, init, f, ret_str);
	push_info_msg(msg);
	free(ret_str);

}

void free_list(list_t *list){
	node_t *curr = list->first;
	for (size_t i = 0; i < list->size; i++)
	{
		node_t *temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(list);
	
}


void test_filter1(){
    set_test_metadata("filter", "Test filter with list==NULL", 1);
	list_t* list1 = NULL;
    SANDBOX_BEGIN;
	filter(list1, filter_function);
    SANDBOX_END;
	CU_ASSERT_EQUAL(list1, NULL);
	if (list1 != NULL) error(list1, "NULL", PRED);
}

void test_filter2(){
	set_test_metadata("filter", "Test filter with list->first==NULL", 1);
	list_t* list2 = malloc(sizeof(list_t));
	list2->first = NULL;
	SANDBOX_BEGIN;
	filter(list2, filter_function);
	SANDBOX_END;
	CU_ASSERT_EQUAL(list2->first, NULL);
	if (list2->first != NULL) error(list2, "[]", PRED);
	free(list2);
}

void test_filter3(){
    set_test_metadata("filter", "Test filter with undesired elements only", 1);
	list_t* list3 = malloc(sizeof(list_t));
	list3->size = 0;
	add_node(list3, 1);
	add_node(list3, 3);
	add_node(list3, 5);
	add_node(list3, 87);
	char *list_str = str_list(list3);
	SANDBOX_BEGIN;
	filter(list3, filter_function);
    SANDBOX_END;
	CU_ASSERT_EQUAL(list3->first, NULL);
	CU_ASSERT_EQUAL(list3->size, 0);
	if (list3->first != NULL) error(list3, list_str, PRED);
	if (list3->size != 0) push_info_msg("Don't forget to update the size of the list");
	free(list3);
	free(list_str);
}

void test_filter4(){
	set_test_metadata("filter", "Test filter with wanted elements only", 1);
	list_t* list4 = malloc(sizeof(list_t));
	add_node(list4, 18);
	add_node(list4, 4);
	add_node(list4, 16);
	add_node(list4, 2);

	char *list_str = str_list(list4);

	SANDBOX_BEGIN;
	filter(list4, filter_function);
	SANDBOX_END;

	int flag = 1;

	node_t* current = list4->first;
	CU_ASSERT_EQUAL(current->value, 2);
	if (current->value != 2) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 16);
	if (current->value != 16) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 4);
	if (current->value != 4) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 18);
	if (current->value != 18) flag = 0;

	CU_ASSERT_EQUAL(current->next, NULL);
	if (current->next != NULL) flag = 0;

	if (!flag) error(list4, list_str, PRED);

	CU_ASSERT_EQUAL(list4->size, 4);
	if (list4->size != 4 ) push_info_msg("You have to update the size of the list");

	free_list(list4);
	free(list_str);
}

void test_filter5(){
	set_test_metadata("filter","Test filter with random elements", 1);
	list_t* list5 = malloc(sizeof(list_t));
	add_node(list5, 18);
	add_node(list5, 17);
	add_node(list5, 5);
	add_node(list5, 4);
	add_node(list5, 120);
	add_node(list5, 61);
	add_node(list5, 10);

	char *list_str = str_list(list5);

	SANDBOX_BEGIN;
	filter(list5, filter_function);
	SANDBOX_END;

	int flag = 1;

	node_t* current = list5->first;

	CU_ASSERT_EQUAL(current->value, 10);
	if (current->value != 10) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 120);
	if (current->value != 120) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 4);
	if (current->value != 4) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 18);
	if (current->value != 18) flag = 0;

	CU_ASSERT_EQUAL(current->next, NULL);
	if (current->next != NULL) flag = 0;

	CU_ASSERT_EQUAL(list5->size, 4);
	if (list5->size != 4 ) push_info_msg("You have to update the size of the list");

	if (!flag) error(list5, list_str, PRED);

	free_list(list5);
	free(list_str);
}

void test_filter6(){
	set_test_metadata("filter", "Test filter with the last element undesired", 1);

	list_t *list6 = malloc(sizeof(list_t));
	add_node(list6, 9);
	add_node(list6, 2);
	add_node(list6, 25);
	add_node(list6, 4);

	char *list_str = str_list(list6);

	SANDBOX_BEGIN;
	filter(list6, filter_function);
	SANDBOX_END;

	int flag = 1;

	CU_ASSERT_EQUAL(list6->size, 2);
	if (list6->size != 2 ) push_info_msg("You have to update the size of the list");

	CU_ASSERT_EQUAL(list6->first->value, 4);
	if (list6->first->value != 4) flag = 0;

	CU_ASSERT_EQUAL(list6->first->next->value, 2);
	if (list6->first->next->value != 2) flag = 0;

	CU_ASSERT_EQUAL(list6->first->next->next, NULL);
	if (list6->first->next->next != NULL) flag = 0;

	if (!flag) error(list6, list_str, PRED);

	free_list(list6);
	free(list_str);
}

/**
 * Fonction map :
 * -linked list = null
 * -first = null
 * -cas avec un élément
 * -cas avec plusieurs éléments
 **/

int map_function(int a){
	return a+3;
}

void test_map1(){
	set_test_metadata("map", "Test map sur list=NULL", 1);
	list_t* list1 = NULL;
	SANDBOX_BEGIN;
	map(list1, map_function);
	SANDBOX_END;
	CU_ASSERT_EQUAL(list1, NULL);
	if (list1 != NULL) error(list1, "NULL", MODIF);
}

void test_map2(){
	set_test_metadata("map", "Test map with list->first=NULL", 1);
	list_t* list2 = malloc(sizeof(list_t));

	list2->first = NULL;

	SANDBOX_BEGIN;
	map(list2, map_function);
	SANDBOX_END;

	CU_ASSERT_EQUAL(list2->first, NULL);
	if (list2->first != NULL) error(list2, "[]", MODIF);

	free(list2);
}

void test_map3(){
	set_test_metadata("map", "Test map with 4 element", 1);
	list_t* list3 = malloc(sizeof(list_t));
	list3->size = 0;
	add_node(list3, 1);
	add_node(list3, 4);
	add_node(list3, 2);
	add_node(list3, 3);

	char *list_str = str_list(list3);

	SANDBOX_BEGIN;
	map(list3, map_function);
	SANDBOX_END;

	int flag = 1;

	node_t* current = list3->first;
	CU_ASSERT_EQUAL(current->value, 6);
	if (current->value != 6) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 5);
	if (current->value != 5) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 7);
	if (current->value != 7) flag = 0;
	current = current->next;

	CU_ASSERT_EQUAL(current->value, 4);
	if (current->value != 4) flag = 0;

	if(!flag) error(list3, list_str, MODIF);

	CU_ASSERT_EQUAL(list3->size, 4);
	if (list3->size != 4 ) push_info_msg("You don't have to update the size of the list");

	free_list(list3);
	free(list_str);
}

void test_map4(){
	set_test_metadata("map", "Test map with 1 elements", 1);

	list_t* list4 = malloc(sizeof(list_t));
	list4->size = 0;
	add_node(list4, 85);

	char *list_str = str_list(list4);

	map(list4, map_function);
	CU_ASSERT_EQUAL(list4->first->value, 88);
	if (list4->first->value != 88) error(list4, list_str, MODIF);
	CU_ASSERT_EQUAL(list4->size, 1);
	if (list4->size != 1 ) push_info_msg("You don't have to update the size of the list");

	free_list(list4);
	free(list_str);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_filter1, test_filter2, test_filter3, test_filter4, test_filter5, test_filter6, test_map1,test_map2, test_map3, test_map4);
}
