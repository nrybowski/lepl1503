#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

void test1(){
    set_test_metadata("insert", "Test ajout sans élément présent dans l'arbre", 1);

    struct obtree* t1 = (struct obtree*) calloc(1, sizeof(struct obtree));

    SANDBOX_BEGIN;
    insert(t1, 36282000 , "Armand", 12.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t1->head, NULL);

    if(t1->head != NULL){
        CU_ASSERT_EQUAL(t1->head->noma, 36282000);
        if (t1->head->noma != 36282000) push_info_msg("Wrong noma inserted");
        CU_ASSERT_EQUAL(t1->head->name, "Armand");
        if (strcmp(t1->head->name, "Armand") != 0) push_info_msg("Wrong name inserted");
        CU_ASSERT_EQUAL(t1->head->grade, 12.2);
        if (t1->head->grade != 12.2) push_info_msg("Wrong grade inserted");
    }
    free(t1->head);
    free(t1);
}

void test2(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma le même", 1);
    struct obtree* t2 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h2 = (struct element*) calloc(1, sizeof(struct element));
    h2->name = "Bruno";
    h2->noma = 24892000;
    h2->grade = 15.5;
    t2->head = h2;

    SANDBOX_BEGIN;
    insert(t2, 24892000 , "Léon", 13.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t2->head, NULL);
    if (t2->head != NULL){
        CU_ASSERT_EQUAL(t2->head->noma, 24892000);
        CU_ASSERT_EQUAL(t2->head->name, "Léon");
        if (strcmp(t2->head->name, "Léon") != 0) push_info_msg("You have to update the informations");
        CU_ASSERT_EQUAL(t2->head->grade, 13.2);
        if (t2->head->grade != 13.2) push_info_msg("You have to update the informations");
    }
    free(t2->head);
    free(t2);
}

void test3(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma plus grand que celui de head", 1);
    struct obtree* t3 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h3 = (struct element*) calloc(1, sizeof(struct element));
    h3->name = "Bruno";
    h3->noma = 24892000;
    h3->grade = 15.5;
    t3->head = h3;

    SANDBOX_BEGIN;
    insert(t3, 46452000 , "Cédric", 15.6);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t3->head->right, NULL);
    if (t3->head->right == NULL) return push_info_msg("You have to insert greater nodes on the right side of the tree");
    if (t3->head->right != NULL){
        CU_ASSERT_EQUAL(t3->head->right->noma, 46452000);
        CU_ASSERT_EQUAL(t3->head->right->name, "Cédric");
        CU_ASSERT_EQUAL(t3->head->right->grade, 15.6);
    }
    free(t3->head->right);
    free(t3->head);
    free(t3);

}

void test4(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma plus petit que celui de head", 1);
    struct obtree* t4 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h4 = (struct element*) calloc(1, sizeof(struct element));
    h4->name = "Bruno";
    h4->noma = 24892000;
    h4->grade = 15.5;
    t4->head = h4;

    SANDBOX_BEGIN;
    insert(t4, 12192000 , "Didier", 11.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t4->head->left, NULL);
    if (t4->head->left == NULL) return push_info_msg("You have to insert smaller nodes on the left side of the tree");
    if (t4->head->left != NULL){
        CU_ASSERT_EQUAL(t4->head->left->noma, 12192000);
        CU_ASSERT_EQUAL(t4->head->left->name, "Didier");
        CU_ASSERT_EQUAL(t4->head->left->grade, 11.2);
    }
    CU_ASSERT_EQUAL(t4->head->right, NULL);
    free(t4->head->left);
    free(t4->head);
    free(t4);

}

void test5(){
    set_test_metadata("insert", "Test ajout à un arbre ayant plusieurs éléments, avec noma plus petit que tout ceux présents", 1);
    // 
    struct obtree* t5 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h5 = (struct element*) calloc(1, sizeof(struct element));
    h5->name = "Jean";
    h5->noma = 50002000;
    h5->grade = 14.8;
    t5->head = h5;

    SANDBOX_BEGIN;
    insert(t5, 40002000 , "Paul", 18.8);
    insert(t5, 30002000 , "Marie", 10.2);
    insert(t5, 20002000 , "Chloe", 19.8);
    insert(t5, 10002000 , "Loic", 10.1);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t5->head->left, NULL);
    if (t5->head->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t5->head->left->left->left, NULL);
    if (t5->head->left->left->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t5->head->left->left->left->left, NULL);
    if (t5->head->left->left->left->left != NULL) return push_info_msg("You didn't insert correctly");
    if (t5->head->left->left->left->left != NULL){
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->noma, 10002000);
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->name, "Loic");
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->grade, 10.1);
    }
    CU_ASSERT_EQUAL(t5->head->right, NULL);
    if (t5->head->right != NULL) push_info_msg("Right tree should be NULL");
    free(t5->head->left->left->left->left);
    free(t5->head->left->left->left);
    free(t5->head->left->left);
    free(t5->head->left);
    free(t5->head);
    free(t5);

}

void test6(){
    set_test_metadata("insert", "Test ajout à un arbre ayant plusieurs éléments, avec noma random", 1);
    struct obtree* t6 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h6 = (struct element*) calloc(1, sizeof(struct element));
    h6->name = "Jean";
    h6->noma = 50002000;
    h6->grade = 14.8;
    t6->head = h6;
    SANDBOX_BEGIN;
    insert(t6, 45472000 , "Pauline", 17.8);
    insert(t6, 69902000 , "Marine", 13.2);
    insert(t6, 22102000 , "Claire", 14.8);
    insert(t6, 26472000 , "Léa", 17.1);
    insert(t6, 78742000 , "Juliette", 16.5);
    SANDBOX_END;
    CU_ASSERT_NOT_EQUAL(t6->head->left, NULL);
    if (t6->head->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t6->head->left->left, NULL);
    if (t6->head->left->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t6->head->left->left->right, NULL);
    if (t6->head->left->left->right == NULL) return push_info_msg("You didn't insert correctly");
    if (t6->head->left->left->right != NULL){
        CU_ASSERT_EQUAL(t6->head->left->left->right->noma, 26472000);
        CU_ASSERT_EQUAL(t6->head->left->left->right->name, "Léa");
        CU_ASSERT_EQUAL(t6->head->left->left->right->grade, 17.1);
    }
    CU_ASSERT_NOT_EQUAL(t6->head->right->right, NULL);
    if (t6->head->right->right == NULL) return push_info_msg("You didn't insert correctly");
    if (t6->head->right->right != NULL) {
        CU_ASSERT_EQUAL(t6->head->right->right->noma, 78742000);
        CU_ASSERT_EQUAL(t6->head->right->right->name, "Juliette");
        CU_ASSERT_EQUAL(t6->head->right->right->grade, 16.5);
    }
    free(t6->head->left->left->right);
    free(t6->head->left->left);
    free(t6->head->left);
    free(t6->head->right->right);
    free(t6->head->right);
    free(t6->head);
    free(t6);
}

void test7(){
    set_test_metadata("convert", "Test convert avec un arbre ne contenant pas d'élément", 1);
    struct obtree* t7 = (struct obtree*) calloc(1, sizeof(struct obtree));
    t7->head = NULL;
    struct linked_list * m = (struct linked_list *) calloc(1, sizeof(struct linked_list));
    m->first = NULL;
    m->nbr_of_element = 0;

    SANDBOX_BEGIN;
    convert(t7->head, m);
    SANDBOX_END;

    CU_ASSERT_EQUAL(m->first, NULL);
    if (m->first != NULL) push_info_msg("You should return NULL when the tree is NULL");
    free(t7);
    free(m);
}

void test8(){
    set_test_metadata("convert", "Test convert avec un arbre contenant 1 seul élément", 1);
    struct obtree* t8 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h8 = (struct element*) calloc(1, sizeof(struct element));
    h8->name = "Jean";
    h8->noma = 50002000;
    h8->grade = 14.8;
    t8->head = h8;
    struct linked_list * m = (struct linked_list *) calloc(1, sizeof(struct linked_list));
    m->first = NULL;
    m->nbr_of_element = 0;
    convert(t8->head, m);
    CU_ASSERT_NOT_EQUAL(m->first, NULL);
    CU_ASSERT_EQUAL(m->nbr_of_element, 1);
    if (m->nbr_of_element != 1) push_info_msg("Don't forget to update the size of the list");
    if (m->first != NULL){
        CU_ASSERT_EQUAL(m->first->noma, 50002000);
        CU_ASSERT_EQUAL(m->first->grade, 14.8);
        CU_ASSERT_EQUAL(m->first->name, "Jean");
        CU_ASSERT_EQUAL(m->first->next, NULL);
    }
    free(m->first);
    free(m);
    free(h8);
    free(t8);

}

void test9(){
    set_test_metadata("convert", "Test convert avec un arbre contenant des éléments ajouté avec des noma random", 1);
    struct obtree* t9 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h9 = (struct element*) calloc(1, sizeof(struct element));
    h9->name = "Jean";
    h9->noma = 50002000;
    h9->grade = 14.8;
    t9->head = h9;

    SANDBOX_BEGIN;
    insert(t9, 45472000 , "Pauline", 17.8);
    insert(t9, 69902000 , "Marine", 13.2);
    insert(t9, 22102000 , "Claire", 14.8);
    insert(t9, 26472000 , "Léa", 17.1);
    insert(t9, 78742000 , "Juliette", 16.5);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t9->head->left, NULL);
    if (t9->head->left == NULL){
        return;
    }
    CU_ASSERT_NOT_EQUAL(t9->head->left->left, NULL);
    if (t9->head->left->left == NULL){
        return;
    }
    struct linked_list * m = (struct linked_list *) calloc(1, sizeof(struct linked_list));
    m->first = NULL;
    m->nbr_of_element = 0;

    SANDBOX_BEGIN;
    convert(t9->head, m);
    SANDBOX_END;

    int cnt = m->nbr_of_element;
    struct linked_node* n = m->first;
    int expected_noma[] = {22102000, 26472000, 45472000, 50002000, 69902000, 78742000};
    double expected_grade[] = {14.8, 17.1, 17.8, 14.8, 13.2, 16.5};
    int i = 0;
    while(cnt>0){
        CU_ASSERT_NOT_EQUAL(n, NULL);
        if (n!= NULL){
            CU_ASSERT_EQUAL(n->noma, expected_noma[i]);
            CU_ASSERT_EQUAL(n->grade, expected_grade[i++]);
        }
        n = n->next;
        cnt--;
    }
    free(t9->head->left->left->right);
    free(t9->head->left->left);
    free(t9->head->left);
    free(t9->head->right->right);
    free(t9->head->right);
    free(t9->head);
    free(t9);
    free(m->first->next->next->next->next->next);
    free(m->first->next->next->next->next);
    free(m->first->next->next->next);
    free(m->first->next->next);
    free(m->first->next);
    free(m->first);
    free(m);
}

void test10(){
    set_test_metadata("convert", "Test convert avec un arbre contenant des éléments ajouté avec des noma décroissants (l'arbre est fortement déséquilibré)", 1);
    struct obtree* t10 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h10 = (struct element*) calloc(1, sizeof(struct element));
    h10->name = "Jean";
    h10->noma = 50002000;
    h10->grade = 14.8;
    t10->head = h10;

    SANDBOX_BEGIN;
    insert(t10, 40002000 , "Paul", 18.8);
    insert(t10, 30002000 , "Marie", 10.2);
    insert(t10, 20002000 , "Chloe", 19.8);
    insert(t10, 10002000 , "Loic", 10.1);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t10->head->left, NULL);
    if (t10->head->left == NULL){
        return;
    }
    CU_ASSERT_NOT_EQUAL(t10->head->left->left->left, NULL);
    if (t10->head->left->left->left == NULL){
        return;
    }
    struct linked_list * m = (struct linked_list *) calloc(1, sizeof(struct linked_list));
    m->first = NULL;
    m->nbr_of_element = 0;

    SANDBOX_BEGIN;
    convert(t10->head, m);
    SANDBOX_END;

    int cnt = m->nbr_of_element;
    struct linked_node* n = m->first;
    int expected_noma[] = {10002000, 20002000, 30002000, 40002000, 50002000};
    double expected_grade[] = {10.1, 19.8, 10.2, 18.8, 14.8};
    int i = 0;
    CU_ASSERT_EQUAL(cnt, 5);
    while(cnt>0){
        CU_ASSERT_NOT_EQUAL(n, NULL);
        if (n!= NULL){
            CU_ASSERT_EQUAL(n->noma, expected_noma[i]);
            CU_ASSERT_EQUAL(n->grade, expected_grade[i++]);
        }
        n = n->next;
        cnt--;
    }
    free(t10->head->left->left->left->left);
    free(t10->head->left->left->left);
    free(t10->head->left->left);
    free(t10->head->left);
    free(t10->head);
    free(t10);
    free(m->first->next->next->next->next);
    free(m->first->next->next->next);
    free(m->first->next->next);
    free(m->first->next);
    free(m->first);
    free(m);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1,test2, test3, test4, test5, test6, test7, test8, test9,test10);
}
