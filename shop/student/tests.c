#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

struct product *initial_product1;
struct product *initial_product2;
struct product *initial_product3;
struct product *initial_product4;
struct product *initial_product5;

int doubleEquals(double x, double y){
    return fabs(x-y) < 0.01;
}

char *str_prod(struct product *prod){
    char *msg = malloc(800);
    char *template = "Product(Name : %s, price : %f, quantity : %d) ";
    strcpy(msg, ""); //initialize
    while (prod){
        char temp[strlen(template)+50];
        sprintf(temp, prod->name, prod->unit_price, prod->quantity);
        strcat(msg, temp);
        prod = prod->next;
    };
    return msg;
}

char *str_shop(struct shop *shop){
    char *temp = "Shop( Number products : %d, Income %f, stock value %f) with products [%s]";
    char *msg = malloc(1000);
    char *prod_str = str_prod(shop->first_product);
    sprintf(msg, temp, shop->count_products, shop->income, shop->stock_value, prod_str);
    free(prod_str);
    return msg;
}

void error(struct shop *correct_shop, struct shop *student_shop){
    char msg[2000];
    char *template = "Wrong answer. Expected shop was %s, but you returned %s";
    char *cor = str_shop(correct_shop);
    char *stu = str_shop(student_shop);
    sprintf(msg, template, cor, stu);
    free(cor);
    free(stu);
    push_info_msg(msg);
}

void error_ret(int exp, int ret){
    return;
    char *template = "Wrong return value. Expected value was %d, but you returned %d";
    char msg[strlen(template)];
    sprintf(msg, template, exp, ret);
    push_info_msg(msg);
}

void test_shops(struct shop *correct_shop, struct shop *student_shop) {
  CU_ASSERT_EQUAL(correct_shop->count_products, student_shop->count_products);
  CU_ASSERT_EQUAL(correct_shop->income, student_shop->income);
  CU_ASSERT_EQUAL(correct_shop->stock_value, student_shop->stock_value);
  /**if (correct_shop->count_products != student_shop->count_products 
    || correct_shop->income != student_shop->income 
    || correct_shop->stock_value != student_shop->stock_value) return error(correct_shop, student_shop);*/

  struct product *correct_prod = correct_shop->first_product ;
  struct product *actual_prod = student_shop->first_product ;

  while ( (correct_prod != NULL) && (actual_prod != NULL) ) {
    CU_ASSERT_STRING_EQUAL(correct_prod->name, actual_prod->name);
    CU_ASSERT_DOUBLE_EQUAL(correct_prod->unit_price, actual_prod->unit_price, 0.01);
    CU_ASSERT_EQUAL(correct_prod->quantity, actual_prod->quantity);

    /**if (strcmp(correct_prod->name, actual_prod->name) != 0
        || !doubleEquals(correct_prod->unit_price, actual_prod->unit_price)
        || correct_prod->quantity != actual_prod->quantity) return error(correct_shop, student_shop);*/

    correct_prod = correct_prod->next;
    actual_prod = actual_prod->next;
  }
  CU_ASSERT_PTR_NULL(correct_prod);
  CU_ASSERT_PTR_NULL(actual_prod);
  //if (correct_prod != NULL || actual_prod != NULL) push_info_msg("Your list of product hasn't a correct size : there is undesired elements in it");
}


void test1() { // Ajoute 1 produit à une liste vide
  // Ajoute le livre "Harry Potter à l'école des sorciers" (product1) à la liste vide

  set_test_metadata("add_product", "Test 1: Ajoute 1 produit à une liste vide", 1);

  struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
  memcpy(product1, initial_product1, sizeof(struct product)) ;

  struct shop *student_shop_empty = (struct shop *)malloc(sizeof(struct shop)) ;
  int count;

  SANDBOX_BEGIN;
  count = add_product(student_shop_empty, product1->name, product1->unit_price, product1->quantity);
  SANDBOX_END;

  CU_ASSERT_EQUAL(1, count);
  if (count != 1) error_ret(1, count);

  struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
  correct_shop->first_product = product1;
  correct_shop->count_products = 1;
  correct_shop->stock_value = (product1->quantity * product1->unit_price) ;

  test_shops(correct_shop, student_shop_empty);
}


void test2() { // Ajoute 1 produit au début d'une liste contenant 1 produit
    // Ajoute la BD "Astérix" (product2) à la liste contenant 1 produit : "Harry Potter à l'école des sorciers" (product1)
    set_test_metadata("add_product", "Test 2: Ajoute 1 produit au début d'une liste contenant 1 produit", 1);

    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *product2 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product2, initial_product2, sizeof(struct product)) ;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int count;
    SANDBOX_BEGIN;
    count = add_product(student_shop1, product2->name, product2->unit_price, product2->quantity);
    SANDBOX_END;
    CU_ASSERT_EQUAL(2, count);
    if (count != 2) error_ret(2, count);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = product2;
    product2->next = product1;
    correct_shop->count_products = 2;
    correct_shop->stock_value = (product1->quantity * product1->unit_price) + 
                                (product2->quantity * product2->unit_price) ;

    test_shops(correct_shop, student_shop1);
}


void test3() { // Ajoute 1 produit à la fin d'une liste contenant 1 produit
    // Ajoute la BD "Spirou et Fantasio" (product3) à la liste contenant 1 produit : 
    // "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("add_product", "Test 3: Ajoute 1 produit à la fin d'une liste contenant 1 produit", 1);

    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *product3 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product3, initial_product3, sizeof(struct product)) ;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int count;
    SANDBOX_BEGIN;
    count = add_product(student_shop1, product3->name, product3->unit_price, product3->quantity);
    SANDBOX_END;
    CU_ASSERT_EQUAL(2, count);
    if (count != 2) error_ret(2, count);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = product1;
    product1->next = product3;
    correct_shop->count_products = 2;
    correct_shop->stock_value = (product1->quantity * product1->unit_price) + 
                                (product3->quantity * product3->unit_price) ;

    test_shops(correct_shop, student_shop1);
}


void test4() { // Ajoute 1 produit au milieu d'une liste contenant 2 produits
    // Ajoute le livre "Le Hobbit" (product4) à la liste contenant 2 produits : 
    // "Harry Potter à l'école des sorciers" (product1), "Spirou et Fantasio" (product3)

    set_test_metadata("add_product", "Test 4: Ajoute 1 produit au milieu d'une liste contenant 2 produits", 1);

    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *product3 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product3, initial_product3, sizeof(struct product)) ;
    struct product *product4 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product4, initial_product4, sizeof(struct product)) ;

    struct shop *student_shop2 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop2->first_product = product1;
    product1->next = product3;
    student_shop2->count_products = 2;
    student_shop2->stock_value = (product1->quantity * product1->unit_price) + 
                                (product3->quantity * product3->unit_price) ;
    int count;
    SANDBOX_BEGIN;
    count = add_product(student_shop2, product4->name, product4->unit_price, product4->quantity);
    SANDBOX_END;
    CU_ASSERT_EQUAL(3, count);
    if (count != 3) error_ret(3, count);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = product1;
    product1->next = product4;
    product4->next = product3;
    correct_shop->count_products = 3;
    correct_shop->stock_value = (product1->quantity * product1->unit_price) + 
                                (product3->quantity * product3->unit_price) +
                                (product4->quantity * product4->unit_price) ;

    test_shops(correct_shop, student_shop2);
}


void test5() { // Ajoute 1 produit déjà existant dans une liste contenant 1 produit
    // Ajoute 10 exemplaires du livre "Harry Potter à l'école des sorciers" (product1) à la liste contenant 1 produit : 
    // "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("add_product", "Test 5: Ajoute 1 produit déjà existant dans une liste contenant 1 produit", 1);

    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;

    int add = 10;
    struct product *modified_product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(modified_product1, initial_product1, sizeof(struct shop)) ;
    modified_product1->quantity += add ;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int count;
    SANDBOX_BEGIN;
    count = add_product(student_shop1, product1->name, 50.0, add);
    SANDBOX_END;
    CU_ASSERT_EQUAL(1, count);
    if (count != 1) error_ret(1, count);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = modified_product1;
    correct_shop->count_products = 1;
    correct_shop->stock_value = (modified_product1->quantity * modified_product1->unit_price) ;

    test_shops(correct_shop, student_shop1);
}





void test6() { // Achète 1 produit d'une liste contenant 1 produit  
    // Achète 5 exemplaires du livre "Harry Potter à l'école des sorciers" (product1) à la liste contenant 1 produit : 
    // "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("buy_product", "Test 6: Achète 1 produit d'une liste contenant 1 produit", 1);

    int substract = 5;
    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *modified_product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(modified_product1, product1, sizeof(struct product)) ;
    modified_product1->quantity -= substract ;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int student_result;
    SANDBOX_BEGIN;
    student_result = buy_product(student_shop1, product1->name, substract);
    SANDBOX_END;
    CU_ASSERT_EQUAL(0, student_result);
    if (student_result != 0) error_ret(0, student_result);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = modified_product1;
    correct_shop->count_products = 1;
    correct_shop->income = (substract * product1->unit_price);
    correct_shop->stock_value = (modified_product1->quantity * modified_product1->unit_price) ;

    test_shops(correct_shop, student_shop1);
}


void test7() { // Achète 1 produit présent en quantité insuffisante dans une liste contenant 1 produit
    // Achète 40 exemplaires du livre "Harry Potter à l'école des sorciers" (product1) à la liste contenant 1 produit : 
    // "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("buy_product", "Test 7: Achète 1 produit présent en quantité insuffisante dans une liste contenant 1 produit", 1);

    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *previous_product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(previous_product1, initial_product1, sizeof(struct product)) ;
    int substract = initial_product1->quantity + 10;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int student_result;
    SANDBOX_BEGIN;
    student_result = buy_product(student_shop1, product1->name, substract);
    SANDBOX_END;
    CU_ASSERT_EQUAL(1, student_result);
    if (student_result != 1) error_ret(1, student_result);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = previous_product1;
    correct_shop->count_products = 1;
    correct_shop->stock_value = (previous_product1->quantity * previous_product1->unit_price) ;

    test_shops(correct_shop, student_shop1);
}


void test8() { // Achète 1 produit qui ne se trouve pas dans une liste vide ou contenant 1 produit
    // Achète 10 exemplaires de la BD "Calvin et Hobbes" à la liste contenant 1 produit : 
    // "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("buy_product", "Test 8: Achète 1 produit qui ne se trouve pas dans une liste vide ou contenant 1 produit", 1);

    int substract = 10;
    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *previous_product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(previous_product1, initial_product1, sizeof(struct shop)) ;

    struct shop *student_shop1 = (struct shop *)malloc(sizeof(struct shop)) ;
    int student_result1;
    SANDBOX_BEGIN;
    student_result1 = buy_product(student_shop1, "Calvin et Hobbes", substract);
    SANDBOX_END;
    CU_ASSERT_EQUAL(2, student_result1);
    if (student_result1 != 2) error_ret(2, student_result1);

    student_shop1->first_product = product1;
    student_shop1->count_products = 1;
    student_shop1->stock_value = (product1->quantity * product1->unit_price);
    int student_result2;
    SANDBOX_BEGIN;
    student_result2 = buy_product(student_shop1, "Calvin et Hobbes", substract);
    SANDBOX_END;
    CU_ASSERT_EQUAL(2, student_result2);
    if (student_result2 != 2) error_ret(2, student_result2);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = previous_product1;
    correct_shop->count_products = 1;
    correct_shop->stock_value = (previous_product1->quantity * previous_product1->unit_price) ;

    test_shops(correct_shop, student_shop1);
}


void test9() { // Vérifie qu'on utilise l'ordre alphabétque pour acheter 1 produit

    set_test_metadata("buy_product", "Test 9: Vérifie qu'on utilise l'ordre alphabétque pour acheter 1 produit", 1);

    int substract = 10;
    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *product3 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product3, initial_product3, sizeof(struct product)) ;
    struct product *product4 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product4, initial_product4, sizeof(struct product)) ;
    struct product *product5 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product5, initial_product5, sizeof(struct product)) ;
    struct product *previous_product5 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(previous_product5, initial_product5, sizeof(struct product)) ;

    struct shop *student_shop3 = (struct shop *)malloc(sizeof(struct shop)) ;
    student_shop3->first_product = product1;
    product1->next = product4;
    product4->next = product3;
    product3->next = product5;
    student_shop3->count_products = 4;
    student_shop3->stock_value =  (product1->quantity * product1->unit_price) +
                                (product3->quantity * product3->unit_price) +
                                (product4->quantity * product4->unit_price) +
                                (product5->quantity * product5->unit_price);
    int student_result;
    SANDBOX_BEGIN;
    student_result = buy_product(student_shop3, product5->name, substract);
    SANDBOX_END;
    CU_ASSERT_EQUAL(2, student_result);
    if (student_result != 2) error_ret(2, student_result);

    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = product1;
    product1->next = product4;
    product4->next = product3;
    product3->next = previous_product5;
    correct_shop->count_products = 4;
    correct_shop->stock_value =  (product1->quantity * product1->unit_price) +
                                (product3->quantity * product3->unit_price) +
                                (product4->quantity * product4->unit_price) +
                                (product5->quantity * product5->unit_price);

    test_shops(correct_shop, student_shop3);
}





void test10() { // Test compliqué utilisant les deux fonctions de multiples fois et traitant tous les cas limites
  // Ajoute les livres "Le Hobbit" (product4), "Les Schtroumpfs" (product5), "Astérix" (product2), 
  // "Spirou et Fantasio" (product3) et "Harry Potter à l'école des sorciers" (product1)

    set_test_metadata("buy_product", "Test 10: Test compliqué utilisant les deux fonctions de multiples fois et traitant tous les cas limites", 1);

    int add1 = 20;
    int add5 = 10;
    int substract1 = 40;
    int substract5 = 10;
    struct product *product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product1, initial_product1, sizeof(struct product)) ;
    struct product *product2 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product2, initial_product2, sizeof(struct product)) ;
    struct product *product3 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product3, initial_product3, sizeof(struct product)) ;
    struct product *product4 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product4, initial_product4, sizeof(struct product)) ;
    struct product *product5 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(product5, initial_product5, sizeof(struct product)) ;

    struct product *modified_product1 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(modified_product1, initial_product1, sizeof(struct shop)) ;
    struct product *modified_product5 = (struct product *)malloc(sizeof(struct product)) ;
    memcpy(modified_product5, initial_product5, sizeof(struct shop)) ;

    struct shop *student_shop_empty = (struct shop *)malloc(sizeof(struct shop)) ;
    int count1;
    int count2;
    int count3;
    int count4;
    int count5;
    int count6;
    int count7;
    int student_result1;
    int student_result2;
    int student_result3;
    SANDBOX_BEGIN;
    count1 = add_product(student_shop_empty, product4->name, product4->unit_price, product4->quantity);
    count2 = add_product(student_shop_empty, product5->name, product5->unit_price, product5->quantity);
    student_result1 = buy_product(student_shop_empty, product5->name, substract5);
    count3 = add_product(student_shop_empty, product2->name, product2->unit_price, product2->quantity);
    count4 = add_product(student_shop_empty, product5->name, 200.0, add5);
    count5 = add_product(student_shop_empty, product3->name, product3->unit_price, product3->quantity);
    count6 = add_product(student_shop_empty, product1->name, product1->unit_price, product1->quantity);
    student_result2 = buy_product(student_shop_empty, product1->name, substract1);
    count7 = add_product(student_shop_empty, product1->name, 100.0, add1);
    student_result3 = buy_product(student_shop_empty, product1->name, substract1);
    SANDBOX_END;

    CU_ASSERT_EQUAL(count1, 1);
    if (count1 != 1) error_ret(1, count1);

    CU_ASSERT_EQUAL(count2, 2);
    if (count2 != 2) error_ret(2, count2);

    CU_ASSERT_EQUAL(0, student_result1);
    if (student_result1 != 0) error_ret(0, student_result1);

    CU_ASSERT_EQUAL(count3, 3);
    if (count3 != 3) error_ret(3, count1);

    CU_ASSERT_EQUAL(count4, 3);
    if (count4 != 3) error_ret(3, count4);

    CU_ASSERT_EQUAL(count5, 4);
    if (count5 != 4) error_ret(4, count5);

    CU_ASSERT_EQUAL(count6, 5);
    if (count6 != 5) error_ret(5, count6);

    CU_ASSERT_EQUAL(1, student_result2);
    if (student_result2 != 1) error_ret(1, student_result2);

    CU_ASSERT_EQUAL(count7, 5);
    if (count7 != 5) error_ret(5, count7);

    CU_ASSERT_EQUAL(0, student_result3);
    if (student_result3 != 0) error_ret(0, student_result3);

    modified_product1->quantity += (add1 - substract1) ;
    modified_product5->quantity += (add5 - substract5) ;
    struct shop *correct_shop = (struct shop *)malloc(sizeof(struct shop)) ;
    correct_shop->first_product = product2;
    product2->next = modified_product1;
    modified_product1->next = product4;
    product4->next = modified_product5;
    modified_product5->next = product3;
    correct_shop->count_products = 5;
    correct_shop->income =  (substract1 * modified_product1->unit_price) +
                            (substract5 * modified_product5->unit_price);
    correct_shop->stock_value = (modified_product1->quantity * modified_product1->unit_price) + 
                                (product2->quantity * product2->unit_price) +
                                (product3->quantity * product3->unit_price) +
                                (product4->quantity * product4->unit_price) +
                                (modified_product5->quantity * modified_product5->unit_price) ;

    test_shops(correct_shop, student_shop_empty);
}

int main(int argc,char** argv)
{
    initial_product1 = (struct product *)malloc(sizeof(struct product)) ;
    initial_product1->name = "Harry Potter à l'école des sorciers" ;
    initial_product1->next = NULL ;
    initial_product1->unit_price = 15.0 ;
    initial_product1->quantity = 30 ;

    initial_product2 = (struct product *)malloc(sizeof(struct product)) ;
    initial_product2->name = "Astérix" ;
    initial_product2->next = NULL ;
    initial_product2->unit_price = 10.0 ;
    initial_product2->quantity = 20 ;

    initial_product3 = (struct product *)malloc(sizeof(struct product)) ;
    initial_product3->name = "Spirou et Fantasio" ;
    initial_product3->next = NULL ;
    initial_product3->unit_price = 7.50 ;
    initial_product3->quantity = 5 ;

    initial_product4 = (struct product *)malloc(sizeof(struct product)) ;
    initial_product4->name = "Le Hobbit" ;
    initial_product4->next = NULL ;
    initial_product4->unit_price = 12.50 ;
    initial_product4->quantity = 10 ;

    initial_product5 = (struct product *)malloc(sizeof(struct product)) ;
    initial_product5->name = "Les Schtroumpfs" ;
    initial_product5->next = NULL ;
    initial_product5->unit_price = 5.50 ;
    initial_product5->quantity = 15 ;
    BAN_FUNCS();
    RUN(test1, test2, test3,test4,test5, test6, test7, test8, test9, test10);
}
