#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

void insertFirst(list_t* liste , int data) {
   node_t *link = (node_t*) malloc(sizeof(struct node));
   link->data = data;

   if (liste->size==0) {
      liste->head = link;
      liste->head->next = liste->head;
      liste->last = liste->head;
   } 
   else {
      link->next = liste->head; 
      liste->head = link;
      liste->last->next=liste->head;
   }
   liste->size++;
}

char *str_list(list_t *list){
    if (list==NULL){
        char *temp = "NULL";
        char *ret = malloc(strlen(temp)+1);
        strcpy(ret, temp);
        return ret;
    }
    char *ret = malloc(list->size*4);
    node_t *curr = list->head;
    strcpy(ret, "[");
    for (int i = 0; i<list->size; i++){
        char *value= i == list->size - 1 ? "%d" : "%d, ";
        char temp[strlen(value)];
        sprintf(temp, value, curr->data);
        strcat(ret, temp);
        curr = curr->next;
    }
    strcat(ret, "]");
    return ret;

}

char *list_str;

void error(list_t *ret, int value){
	char *err = _("You didn't apply the modifications correctly. With the list %s and value %d, you returned %s");
	char *ret_str = str_list(ret);
	char msg[strlen(err) + strlen(ret_str) + strlen(list_str)];
	sprintf(msg, err, list_str, value, ret_str);
	push_info_msg(msg);
	free(ret_str);
}

void error_size(int ret, int exp){
    char *template = "Your list has a wrong size. Expected size was %d, but yours is %d";
    char msg[strlen(template)];
    sprintf(msg, template, exp, ret);
    push_info_msg(msg);
}
 
 
int flag = 1;

int value;

typedef struct size{
    int size1;
    int size2;
} size_pair;

typedef union switcher{
    list_t *first;
    size_pair s;
}sw_t;

sw_t switcher;

bool compare(list_t* liste1,list_t* liste2){

    if (liste1->size!=liste2->size){
        switcher.s = (size_pair) {liste1->size, liste2->size};
        flag = -1;
        return false;
    }

    if (liste1->size==0 && liste1->head == NULL && liste2->head==NULL) return true;

    node_t *curr1 = liste1->head;
    node_t *curr2 = liste2->head;

    for (int j = 0; j < liste2->size; j++){     // change the offset where we are starting in the circular list
        node_t *temp1 = curr1;
        node_t *temp2 = curr2;
        int equals = 1;
        for (int i = 0; i < liste2->size; i++)
        {
            if (curr1->data!=curr2->data){
                equals = 0;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        if (equals){
            return true;

        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    switcher.first = liste1;
    flag = -2;
    return false;
}

void check_error(){
    switch (flag){
        case 1:
            return;
        case -1:
            error_size(switcher.s.size1, switcher.s.size2);
            break;
        case -2:
            error(switcher.first, value);
            break;
    }
    flag = 1;
    free(list_str);
}



void test_delete_value_1(){
    set_test_metadata("delete", "Test delete premier élément", 1);
    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,1);
    insertFirst(&liste1,10);
    insertFirst(&liste1,20);
    insertFirst(&liste1,30);
    insertFirst(&liste1,40);
    insertFirst(&liste1,56);

    list_str = str_list(&liste1);
    value = 1;

    list_t liste;
    liste.size=0;

    liste.head=NULL;
    insertFirst(&liste,10);
    insertFirst(&liste,20);
    insertFirst(&liste,30);
    insertFirst(&liste,40);
    insertFirst(&liste,56);
    
    int b;
    SANDBOX_BEGIN;
    b  = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 1;
    CU_ASSERT_EQUAL(a,b);
    if (a!=b) push_info_msg("You didn't delete the right number of elements");
    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

void test_delete_value_2(){
    set_test_metadata("delete", "Test delete deux éléments de suite", 1);
    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,1);
    insertFirst(&liste1,10);
    insertFirst(&liste1,20);
    insertFirst(&liste1,30);
    insertFirst(&liste1,1);
    insertFirst(&liste1,1);
    insertFirst(&liste1,40);
    insertFirst(&liste1,56);

    list_str = str_list(&liste1);
    value = 1;

    list_t liste;
    liste.size=0;

    liste.head=NULL;
    insertFirst(&liste,10);
    insertFirst(&liste,20);
    insertFirst(&liste,30);
    insertFirst(&liste,40);
    insertFirst(&liste,56);

    int b;
    SANDBOX_BEGIN;
    b  = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 3;

    CU_ASSERT_EQUAL(a,b);
        if (a!=b) push_info_msg("You didn't delete the right number of elements");
    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

void test_delete_value_3(){

    set_test_metadata("delete", "Test delete dernier élément", 1);

    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,1);
    insertFirst(&liste1,5);
    insertFirst(&liste1,2);
    insertFirst(&liste1,3);
    insertFirst(&liste1,1);
    insertFirst(&liste1,1);
    insertFirst(&liste1,4);
    insertFirst(&liste1,6);
    insertFirst(&liste1,1);

    list_str = str_list(&liste1);
    value = 1;

    list_t liste;
    liste.size=0;
    liste.head=NULL;
    insertFirst(&liste,5);
    insertFirst(&liste,2);
    insertFirst(&liste,3);
    insertFirst(&liste,4);
    insertFirst(&liste,6);


    int b;
    SANDBOX_BEGIN;
    b = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 4;

    CU_ASSERT_EQUAL(a,b);
        if (a!=b) push_info_msg("You didn't delete the right number of elements");

    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

void test_delete_value_4(){

    set_test_metadata("delete", "Test delete liste contenant que l'élément", 1);

    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,1);

    list_str = str_list(&liste1);
    value = 1;
    

    list_t liste;
    liste.size=0;
    liste.head=NULL;
   

    int b;
    SANDBOX_BEGIN;
    b = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 1;

    CU_ASSERT_EQUAL(a,b);
        if (a!=b) push_info_msg("You didn't delete the right number of elements");

    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

void test_delete_value_5(){

    set_test_metadata("delete", "Test delete liste contenants plusieurs fois l'élément", 1);

    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,1);
    insertFirst(&liste1,1);

    list_str = str_list(&liste1);
    value = 1;
    

    list_t liste;
    liste.size=0;
    liste.head=NULL;
    


    int b;
    SANDBOX_BEGIN;
    b  = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 2;

    CU_ASSERT_EQUAL(a,b);
        if (a!=b) push_info_msg("You didn't delete the right number of elements");

    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

void test_delete_value_6(){

    set_test_metadata("delete", "Test delete liste ne contenant pas l'élément", 1);

    list_t liste1;
    liste1.size=0;

    liste1.head=NULL;
    insertFirst(&liste1,5);

    list_str = str_list(&liste1);
    value = 1;
    

    list_t liste;
    liste.size=0;
    liste.head=NULL;
    
    insertFirst(&liste,5);


    int b;
    SANDBOX_BEGIN;
    b  = deletevalue(&liste1,1);
    SANDBOX_END;
    int a  = 0;

    CU_ASSERT_EQUAL(a,b);
        if (a!=b) push_info_msg("You didn't delete the right number of elements");

    CU_ASSERT_TRUE(compare(&liste1,&liste));

    check_error();
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_delete_value_1, test_delete_value_2, test_delete_value_3, test_delete_value_4, test_delete_value_5, test_delete_value_6);
}
