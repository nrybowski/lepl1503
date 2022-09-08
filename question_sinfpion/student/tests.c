#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

char *str_list(node_l* ll){
    if (ll == NULL){
        char *ret = malloc(strlen("NULL") + 1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(200);
    strcpy(ret, "[");
    char *template = "%d";
    while (ll){
        char product[strlen(template)];
        sprintf(product, template,  ll->value);
        strcat(ret, product);
        if (ll->next) strcat(ret, ", ");
        ll = ll->next;
    }
    strcat(ret, "]");
    return ret;
}

void error_index(node_l *ll, int exp, int res){
    char *template = _("Wrong return value. The expected answer with list %s was %d, but you returned %d");
    char msg[strlen(template) + 200];
    char *list_str = str_list(ll);
    sprintf(msg, template, list_str, exp, res);
    push_info_msg(msg);
    free(list_str);
}

char *previous_ll;


void error_remove(node_l *ll, int exp, int res){
    char *template = _("Wrong answer. The expected answer with list %s was %d, but you returned %d and your modified list is %s");
    char msg[strlen(template) + 400];
    char *list_str = str_list(ll);
    sprintf(msg, template, previous_ll, exp, res, list_str);
    push_info_msg(msg);
    free(list_str);
}

void test1(){
    set_test_metadata("find", "Test basique pour findIndexMin", 1);
    //test basique pour findIndexMin
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = 1;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = 2;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = 3;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = 4;
    LinkedList->next->next->next->next = NULL;
    int res;
    SANDBOX_BEGIN;
    res=findMinIndex(LinkedList);
    SANDBOX_END;

    CU_ASSERT_EQUAL(0,res);
    if (res != 0) error_index(LinkedList, 0, res);

    free((void*) LinkedList->next->next->next);
    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);
    
}
    
void test2(){
    set_test_metadata("find", "Test basique pour findMinIndex avec 2 minimums", 1);
    //test basique pour findMinIndex avec 2 minimums
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = 43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = 2;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = 6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = 2;
    LinkedList->next->next->next->next = NULL;
    int res;

    SANDBOX_BEGIN;
    res=findMinIndex(LinkedList);
    SANDBOX_END;

    CU_ASSERT_EQUAL(1,res);
    if (res != 1) error_index(LinkedList, 1, res);

    free((void*) LinkedList->next->next->next);
    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);

    
}
void test3(){
    set_test_metadata("find", "Test basique pour findTheMinIndex avec des nombres négatifs", 1);
    //test basique pour findTheMinIndex avec des nombres négatifs
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = -43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = -2;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = -6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = -32;
    LinkedList->next->next->next->next = NULL;
    int res;

    SANDBOX_BEGIN;
    res=findMinIndex(LinkedList);
    SANDBOX_END;

    CU_ASSERT_EQUAL(0,res);
    if (res != 0) error_index(LinkedList, 0, res);

    free((void*) LinkedList->next->next->next);
    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);


}

void test4(){
    set_test_metadata("remove", "Test basique pour removeTheMinIndex début de liste", 1);

    //test basique pour removeTheMinIndex début de liste
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = -43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = -2;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = -6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = -32;
    LinkedList->next->next->next->next = NULL;

    previous_ll = str_list(LinkedList);

    int res;
    SANDBOX_BEGIN;
    res=removeTheMinIndex(&LinkedList,0);
    SANDBOX_END;

    CU_ASSERT_EQUAL(-43,res);
    if (res != -43) return error_remove(LinkedList, -43, res);

    //creating the just linked list
    node_l * JustLinkedList = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->value = -2;
    JustLinkedList->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->value = -6;
    JustLinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->next->value = -32;
    JustLinkedList->next->next->next =NULL;

    node_l * currentres = LinkedList;
    node_l * currentjust = JustLinkedList;
    while (currentres!=NULL && currentjust!=NULL)
    {
        CU_ASSERT_EQUAL(currentres->value,currentjust->value);
        if (currentres->value != currentjust->value) return error_remove(LinkedList, -43, res);
        currentjust=currentjust->next;
        currentres=currentres->next;
    }
    if (currentres!=NULL || currentjust!=NULL)
    {
        CU_FAIL()
        push_info_msg("You didn't remove the node correctly");
        error_remove(LinkedList, -43, res);
    }



    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);

    free((void*) JustLinkedList->next->next);
    free((void*) JustLinkedList->next);
    free((void*) JustLinkedList);
    free(previous_ll);

}

void test5(){

    set_test_metadata("remove", "Test basique pour removeTheMinIndex fin de liste", 1);

    //test basique pour removeTheMinIndex fin de liste
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = 43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = -2;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = -6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = -32;
    LinkedList->next->next->next->next = NULL;

    previous_ll = str_list(LinkedList);

    int res;
    SANDBOX_BEGIN;
    res=removeTheMinIndex(& LinkedList,3);
    SANDBOX_END;

    CU_ASSERT_EQUAL(-32,res);
    if (res != -32) return error_remove(LinkedList, -32, res);
    //creating the just linked list
    node_l * JustLinkedList = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->value = 43;
    JustLinkedList->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->value = -2;
    JustLinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->next->value = -6;
    JustLinkedList->next->next->next =NULL;

    node_l * currentres = LinkedList;
    node_l * currentjust = JustLinkedList;
    while (currentres!=NULL && currentjust!=NULL)
    {
        CU_ASSERT_EQUAL(currentres->value,currentjust->value);
        if (currentres->value != currentjust->value) return error_remove(LinkedList, -32, res);
        currentjust=currentjust->next;
        currentres=currentres->next;
    }
    if (currentres!=NULL || currentjust!=NULL)
    {
        CU_FAIL()
        push_info_msg("You didn't remove the node correctly");
        error_remove(LinkedList, -32, res);
    }

    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);

    free((void*) JustLinkedList->next->next);
    free((void*) JustLinkedList->next);
    free((void*) JustLinkedList);
    free(previous_ll);
  

}

void test6(){

    set_test_metadata("remove", "Test basique pour removeTheMinIndex ", 1);

    //test basique pour removeTheMinIndex 
    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = 43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = -22;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = 6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = 3;
    LinkedList->next->next->next->next = NULL;

    previous_ll = str_list(LinkedList);

    int res;
    SANDBOX_BEGIN;
    res=removeTheMinIndex(& LinkedList,1);
    SANDBOX_END;

    CU_ASSERT_EQUAL(-22,res);
    if (res != -22) return error_remove(LinkedList, -22, res);
    //creating the just linked list
    node_l * JustLinkedList = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->value = 43;
    JustLinkedList->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->value = 6;
    JustLinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    JustLinkedList->next->next->value = 3;
    JustLinkedList->next->next->next =NULL;

    node_l * currentres = LinkedList;
    node_l * currentjust = JustLinkedList;

    while (currentres!=NULL && currentjust!=NULL)
    {
        CU_ASSERT_EQUAL(currentres->value,currentjust->value);
        if (currentres->value != currentjust->value) return error_remove(LinkedList, -22, res);
        currentjust=currentjust->next;
        currentres=currentres->next;
    }
    if (currentres!=NULL || currentjust!=NULL)
    {
        CU_FAIL()
        push_info_msg("You didn't remove the node correctly");
        error_remove(LinkedList, -22, res);
    }

    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);

    free((void*) JustLinkedList->next->next);
    free((void*) JustLinkedList->next);
    free((void*) JustLinkedList);
    free(previous_ll);

}
void test7(){
    set_test_metadata("remove", "Test pour removeTheMinIndex cas LL vide", 1);
    //test pour removeTheMinIndex cas LL vide
    node_l * LinkedList = NULL;
    int res;
    SANDBOX_BEGIN;
    res=removeTheMinIndex(& LinkedList,0);
    SANDBOX_END;
    CU_ASSERT_EQUAL(-1,res);
    if (res != -1) error_index(LinkedList, -1, res);

  }


void test8(){
    set_test_metadata("remove", "Test index en dehors de la liste", 1);
    //test index en dehors de la liste

    node_l * LinkedList = (node_l *) malloc(sizeof(node_l));
    LinkedList->value = 43;
    LinkedList->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->value = -22;
    LinkedList->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->value = 6;
    LinkedList->next->next->next = (node_l *) malloc(sizeof(node_l));
    LinkedList->next->next->next->value = 3;
    LinkedList->next->next->next->next = NULL;


    int res;
    SANDBOX_BEGIN;
    res=removeTheMinIndex(& LinkedList,4);
    SANDBOX_END;
    CU_ASSERT_EQUAL(-1,res);
    if (res != -1) error_index(LinkedList, -1, res);

    free((void*) LinkedList->next->next->next);
    free((void*) LinkedList->next->next);
    free((void*) LinkedList->next);
    free((void*) LinkedList);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7, test8);
}
