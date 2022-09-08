#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"


int doubleEqualsEpsilon(double x, double y, double epsilon){
    return fabs(x - y) < epsilon;
}

int doubleEquals(double x, double y){
    return doubleEqualsEpsilon(x,y,10e-6);
}

node_t* head0;
node_t* head1;

// Linked list methods

node_t* add_product(node_t* head, product_t product){
    node_t* node = malloc(sizeof(node_t));
    if (!node) return NULL;
    node->product = product;
    node->next = NULL;

    if (head == NULL){ // Empty list case
        return node;
    }

    node_t* n = head;
    while (n->next){
        n = n->next;
    }
    n->next = node;
    return head;
}

char *print_lkdlist(node_t* head){
    char *ret = malloc(2000);
    strcpy(ret, "[");
    node_t* n = head;
    char *template = "(Product name = %s, Price = %f)";
    while (n){
        char product[strlen(template) + 50];
        sprintf(product, template,  n->product.name, n->product.price);
        strcat(ret, product);
        n = n->next;
    }
    strcat(ret, "]");
    return ret;
}


void free_lkdlist(node_t* head){
    if (head){
        node_t* next = head->next;
        free(head);
        free_lkdlist(next);
    }
}

// Mapping functions

int increase_cost(product_t* product){
    product->price += 1.0;
    return 0;
}

int rename_product(product_t* product){
    product->name = "Just another product";
    return 0;
}

int identity(product_t* product){
    return 0;
}

int fail_fct(product_t* product){
    if (strcasecmp("Carpette", product->name) == 0) return 1;
    return 0;
}

int init(void) {
    product_t table;
    table.name = "Table";
    table.price = 150.01;

    product_t carpette;
    carpette.name = "Carpette";
    carpette.price = 14.99;

    product_t books;
    books.name = "Integrale des aventures de Tintin";
    books.price = 234.56;

    product_t key;
    key.name = "Cle du bonheur";
    key.price = 0.0; 

    product_t piano;
    piano.name = "Piano";
    piano.price = 2399.50;

    head1 = add_product(NULL, table);
    if (!head1) return -1;

    if (!add_product(head1, carpette)){
        free_lkdlist(head1);
        return -1;
    }

    if (!add_product(head1, books)){
        free_lkdlist(head1);
        return -1;
    }

    if (!add_product(head1, key)){
        free_lkdlist(head1);
        return -1;
    }

    if (!add_product(head1, piano)){
        free_lkdlist(head1);
        return -1;
    }

    if (!add_product(head1, carpette)){
        free_lkdlist(head1);
        return -1;
    }

    head0 = add_product(NULL, carpette);
    if (!head0){
        free_lkdlist(head1);
        return -1;
    }

    return 0; 
}

int clean(void) {
    free_lkdlist(head0);
    free_lkdlist(head1);
    return 0;
}

typedef enum map{IP, RP, ID, FAIL} map_t;

char *function_str[] = {"(product) -> product.price++", "(product) -> product.name = \"Just another product\"",
                        "(product) -> return", "(product) -> return 1"};

void error(node_t *ret, char *init, map_t function){
	char *err = _("You didn't apply the modifications correctly. With the list %s and function %s, you returned %s");
	char *ret_str = print_lkdlist(ret);
	char *f = function_str[function];
	char msg[strlen(err) + strlen(ret_str) + strlen(f) + strlen(init)];
	sprintf(msg, err, init, f, ret_str);
	push_info_msg(msg);
	free(ret_str);

}

int flag = 1;

// Tests methods

void test1(){
    init();
    set_test_metadata("map", "Test un seul element, f = identity", 1);
    int res;

    char *list_str = print_lkdlist(head0);
    SANDBOX_BEGIN;
    res = map(&identity, head0);
    SANDBOX_END;

    flag = 1;
    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");

    CU_ASSERT_STRING_EQUAL(head0->product.name, "Carpette");
    if (strcmp(head0->product.name, "Carpette") != 0) flag = 0;

    CU_ASSERT_DOUBLE_EQUAL(head0->product.price, 14.99, 10e-6);
    if (!doubleEquals(head0->product.price , 14.99)) flag = 0;

    if (!flag) error(head0, list_str, ID);

    CU_ASSERT_PTR_NULL(head0->next);

    free(list_str);
    clean();
}

void test2(){
    init();
    set_test_metadata("map", "Test un seul element, f = fail_fct", 1);
    //
    int res;
    char *list_str = print_lkdlist(head0);
    SANDBOX_BEGIN;
    res = map(&fail_fct, head0);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 1);
    if (res != 1) push_info_msg("You returned the wrong value");
    CU_ASSERT_STRING_EQUAL(head0->product.name, "Carpette"); //La liste ne devrait pas avoir été modifiée
    if (strcmp(head0->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(head0->product.price, 14.99, 10e-6);
    if (!doubleEquals(head0->product.price , 14.99)) flag = 0;
    CU_ASSERT_PTR_NULL(head0->next);

    if (!flag) error(head0, list_str, FAIL);

    free(list_str);
    clean();
}

void test3(){
    init();
    set_test_metadata("map", "Test un seul element, f = increase_price", 1);

    int res;
    char *list_str = print_lkdlist(head0);
    SANDBOX_BEGIN;
    res = map(&increase_cost, head0);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_STRING_EQUAL(head0->product.name, "Carpette");
    if (strcmp(head0->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(head0->product.price, 15.99, 10e-6);
    if (!doubleEquals(head0->product.price , 15.99)) flag = 0;
    CU_ASSERT_PTR_NULL(head0->next);

    if (!flag) error(head0, list_str, IP);
    free(list_str);
    clean();
}

void test4(){
    init();
    set_test_metadata("map", "Test un seul element, f = rename_product", 1);

    int res;
    char *list_str = print_lkdlist(head0);
    SANDBOX_BEGIN;
    res = map(&rename_product, head0);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_STRING_EQUAL(head0->product.name, "Just another product");
    if (strcmp(head0->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(head0->product.price, 14.99, 10e-6);
    if (!doubleEquals(head0->product.price , 14.99)) flag = 0;
    CU_ASSERT_PTR_NULL(head0->next);

    if (!flag) error(head0, list_str, IP);
    free(list_str);
    clean();
}

void test5(){
    init();
    set_test_metadata("map", "Test liste vide, f = identity", 1);

    node_t* head = NULL;
    int res;

    SANDBOX_BEGIN;
    res = map(&identity, head);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_PTR_NULL(head);
    if (head != NULL) push_info_msg("The list should remain NULL");
    clean();
}

void test6(){
    init();
    set_test_metadata("map", "Test liste vide, f = fail_fct", 1);

    node_t* head = NULL;
    int res;
    SANDBOX_BEGIN;
    res = map(&fail_fct, head);
    SANDBOX_END;
    
    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_PTR_NULL(head);
    if (head != NULL) push_info_msg("The list should remain NULL");
    clean();
}

void test7(){
    init();
    set_test_metadata("map", "Test liste vide, f = rename_product", 1);
    //test d'une liste vide
    node_t* head = NULL;
    int res;
    SANDBOX_BEGIN;
    res = map(&increase_cost, head);
    SANDBOX_END;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_PTR_NULL(head);
    if (head != NULL) push_info_msg("The list should remain NULL");
    clean();
}

void test8(){
    init();
    set_test_metadata("map", "Test liste vide, f = increase_price", 1);

    //test d'une liste vide
    node_t* head = NULL;
    int res;
    SANDBOX_BEGIN;
    res = map(&rename_product, head);
    SANDBOX_END;
    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    CU_ASSERT_PTR_NULL(head);
    if (head != NULL) push_info_msg("The list should remain NULL");
    clean();
}

void test9(){
    init();
    set_test_metadata("map", "Test 6 elements, f = identity", 1);

    //test d'une liste contenant plus d'un élément (ici 6)
    int res;
    char *list_str = print_lkdlist(head1);
    SANDBOX_BEGIN;
    res = map(&identity, head1);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    node_t* n = head1;
    CU_ASSERT_STRING_EQUAL(n->product.name, "Table");
    if (strcmp(n->product.name, "Table") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 150.01, 10e-6); 
    if (!doubleEquals(n->product.price, 150.01)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Integrale des aventures de Tintin");
    if (strcmp(n->product.name, "Integrale des aventures de Tintin") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 234.56, 10e-6); 
    if (!doubleEquals(n->product.price, 234.56)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Cle du bonheur");
    if (strcmp(n->product.name, "Cle du bonheur") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 0.00, 10e-6); 
    if (!doubleEquals(n->product.price, 0.00)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Piano");
    if (strcmp(n->product.name, "Piano") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 2399.50, 10e-6); 
    if (!doubleEquals(n->product.price, 2399.50)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;


    CU_ASSERT_PTR_NULL(n);

    if (!flag) error(head1, list_str, ID);

    free(list_str);

    clean();
}

void test10(){
    init();

    set_test_metadata("map", "Test 6 elements, f = fail_fct", 1);

    //test d'une liste contenant plus d'un élément (ici 6) avec une fonction qui fail
    int res;
    char *list_str = print_lkdlist(head1);

    SANDBOX_BEGIN;
    res = map(&fail_fct, head1);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 1);
    if (res != 1) push_info_msg("You returned the wrong value");
    node_t* n = head1;
    CU_ASSERT_STRING_EQUAL(n->product.name, "Table");
    if (strcmp(n->product.name, "Table") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 150.01, 10e-6); 
    if (!doubleEquals(n->product.price, 150.01)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Integrale des aventures de Tintin");
    if (strcmp(n->product.name, "Integrale des aventures de Tintin") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 234.56, 10e-6); 
    if (!doubleEquals(n->product.price, 234.56)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Cle du bonheur");
    if (strcmp(n->product.name, "Cle du bonheur") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 0.00, 10e-6); 
    if (!doubleEquals(n->product.price, 0.00)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Piano");
    if (strcmp(n->product.name, "Piano") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 2399.50, 10e-6); 
    if (!doubleEquals(n->product.price, 2399.50)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;
    CU_ASSERT_PTR_NULL(n);

    if(!flag) error(head1, list_str, FAIL);

    free(list_str);
    clean();
}

void test11(){

    init();
    set_test_metadata("map", "Test 6 elements, f = increase_price", 1);

    //test d'une liste contenant plus d'un élément (ici 6)
    int res;
    char *list_str = print_lkdlist(head1);

    SANDBOX_BEGIN;
    res = map(&increase_cost, head1);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");
    node_t* n = head1;
    CU_ASSERT_STRING_EQUAL(n->product.name, "Table");
    if (strcmp(n->product.name, "Table") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 151.01, 10e-6); 
    if (!doubleEquals(n->product.price, 151.01)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 15.99, 10e-6); 
    if (!doubleEquals(n->product.price, 15.99)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Integrale des aventures de Tintin");
    if (strcmp(n->product.name, "Integrale des aventures de Tintin") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 235.56, 10e-6); 
    if (!doubleEquals(n->product.price, 235.56)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Cle du bonheur");
    if (strcmp(n->product.name, "Cle du bonheur") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 1.00, 10e-6); 
    if (!doubleEquals(n->product.price, 1.00)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Piano");
    if (strcmp(n->product.name, "Piano") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 2400.50, 10e-6); 
    if (!doubleEquals(n->product.price, 2400.50)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Carpette");
    if (strcmp(n->product.name, "Carpette") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 15.99, 10e-6); 
    if (!doubleEquals(n->product.price, 15.99)) flag = 0;
    n = n->next;
    CU_ASSERT_PTR_NULL(n);

    if (!flag) error(head1, list_str, IP);

    free(list_str);

    clean();
}

void test12(){

    init();

    set_test_metadata("map", "Test 6 elements, f = rename_product", 1);

    //test d'une liste contenant plus d'un élément (ici 6)
    int res;
    char *list_str = print_lkdlist(head1);
    SANDBOX_BEGIN;
    res = map(&rename_product, head1);
    SANDBOX_END;

    flag = 1;

    CU_ASSERT_EQUAL(res, 0);
    if (res != 0) push_info_msg("You returned the wrong value");


    node_t* n = head1;
    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 150.01, 10e-6); 
    if (!doubleEquals(n->product.price, 150.01)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 234.56, 10e-6); 
    if (!doubleEquals(n->product.price, 234.56)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 0.00, 10e-6); 
    if (!doubleEquals(n->product.price, 0.00)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 2399.50, 10e-6); 
    if (!doubleEquals(n->product.price, 2399.50)) flag = 0;
    n = n->next;


    CU_ASSERT_STRING_EQUAL(n->product.name, "Just another product");
    if (strcmp(n->product.name, "Just another product") != 0) flag = 0;
    CU_ASSERT_DOUBLE_EQUAL(n->product.price, 14.99, 10e-6); 
    if (!doubleEquals(n->product.price, 14.99)) flag = 0;
    n = n->next;
    CU_ASSERT_PTR_NULL(n);

    if (!flag) error(head1, list_str, IP);

    free(list_str);

    clean();
}



int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1,test2, test3, test4, test5, test6, test7, test8, test9, test10, test11, test12);
}
