#include <stdlib.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define STRLEN 200

list cpy(list lst){
    if (lst == NULL) return NULL;
    list new = malloc(sizeof(list));
    memcpy(new, lst, sizeof(item));
    new->next = cpy(lst->next);
    return new;
}

char *str_list(item *list){
    if (list == NULL){
        char *ret = malloc(strlen("NULL")+1);
        strcpy(ret, "NULL");
        return ret;
    }
    char *ret = malloc(STRLEN);
    char *template = "%d";
    strcpy(ret, "[");
    while (list){
        char temp[strlen(template)];
        sprintf(temp, template, list->val);
        strcat(ret, temp);
        if (list->next) strcat(ret, ", ");
        list = list->next;
    }
    strcat(ret, "]");
    return ret;
}


void error(item *init, item *ret, int val, int index){
    char *template = _("Error while inserting value %d at index %d with the initial list %s. You returned the list %s");
    char msg[strlen(template) + 2*STRLEN];
    char *list_init = str_list(init);
    char *list_ret = str_list(ret);
    sprintf(msg, template, val, index,  list_init, list_ret);
    push_info_msg(msg);
    free(list_init);
    free(list_ret);
}

void check_equal(list init, list ret, int *exp, int nb, int value, int index){
    list temp = ret;
    for (int i = 0; i < nb; i++){
        CU_ASSERT_PTR_NOT_NULL(temp);
        if (temp == NULL) return error(init, ret, value, index);
        CU_ASSERT_EQUAL(temp->val, exp[i]);
        if (temp->val != exp[i]) return error(init, ret, value, index);
        temp = temp->next;
    }
}

void test1(){
    set_test_metadata("insert", "Test d'insertion valeur 1", 1);

    int valueReturn = 1; //si je met une autre valeur que 1, le test ne passe évidemment pas
    item* nouveau = malloc(sizeof(item));
    nouveau->val = 1;

    list init = NULL; 
    list listeGlobal = NULL;
    /* j'insere au debut*/
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 0, nouveau);
    SANDBOX_END;

    CU_ASSERT_EQUAL(valueReturn, listeGlobal->val);
    if (valueReturn != listeGlobal->val) error(init , listeGlobal, 1, 0);
    //je teste que la valeur de retour est bien = à 1
}

void test2(){
    set_test_metadata("insert", "Test que le pointeur de notre liste pointe sur la zone mémoire passée en paramètre et pas non sur une nouvelle", 1);

    item* nouveau = malloc(sizeof(item));
    nouveau->val = 1;

    list listeGlobal = NULL;

    /* j'insere au debut*/
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 0, nouveau);  
    SANDBOX_END;

    //je vérifie que listeglobal pointe bien sur le même pointeur que nouveau et donc que l'on ne realloue pas une nouvelle zone mémoire inutilement
    CU_ASSERT_PTR_EQUAL(listeGlobal, nouveau);
    if (listeGlobal != nouveau) push_info_msg("The return value should be the first node when inserted at index 0");
}

void test3(){
    set_test_metadata("insert", "Test que le pointeur suivant est bien égal à NULL", 1);

    item* nouveau = malloc(sizeof(item));
    nouveau->val = 1;
    list init = NULL;
    list listeGlobal = NULL;
    /* j'insere au debut*/
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 0, nouveau);  
    SANDBOX_END;
    CU_ASSERT_PTR_NULL(listeGlobal->next);
    if (listeGlobal == NULL) return error(init, listeGlobal, 1, 0);
    if (listeGlobal->next != NULL) push_info_msg("You don't initialize the next pointer to NULL when inserting");
    //je verifie que l'on a pas oublie d'initialiser nouveau->next à NULL;
}

void test4(){
    set_test_metadata("insert", "Test que l'ajout est bien à la suite du premier élément ajouté", 1);

    item* nouveau = malloc(sizeof(item));
    item* nouveau2 = malloc(sizeof(item));
    nouveau->val = 1;
    nouveau2->val = 2;
    list init = NULL;
    list listeGlobal = NULL;
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 0, nouveau); 
    SANDBOX_END;
    CU_ASSERT_PTR_NOT_NULL(listeGlobal);
    CU_ASSERT_EQUAL(listeGlobal->val, 1);
    if (listeGlobal == NULL || listeGlobal->val != 1) return error(init, listeGlobal, 1, 0);

    init = cpy(listeGlobal);

    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 1, nouveau2);  
    SANDBOX_END;

    CU_ASSERT_PTR_EQUAL(listeGlobal->next, nouveau2);
    if (listeGlobal->next != nouveau2) error(init, listeGlobal, 2, 1);

    free(init);
    //je teste que l'ajout est bien a la suite du premier élément ajouté
}

void test5(){
    set_test_metadata("insert", "Test d'insertion entre 2 blocs", 1);

    item* nouveau = malloc(sizeof(item));
    item* nouveau2 = malloc(sizeof(item));
    item* nouveau3 = malloc(sizeof(item));
    nouveau->val = 1;
    nouveau2->val = 3;
    nouveau3->val = 2;

    list init = NULL;
    list listeGlobal = NULL;

    int exp[] = {1};
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 0, nouveau);
    SANDBOX_END;
    check_equal(init, listeGlobal, exp, 1, 1, 0);

    init = cpy(listeGlobal);

    int exp2[] = {1,3};
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 1, nouveau2);
    SANDBOX_END;
    check_equal(init, listeGlobal, exp2, 2, 3, 1);

    free(init);
    init = cpy(listeGlobal);

    int exp3[] = {1, 2 ,3};
    SANDBOX_BEGIN;
    listeGlobal = addToIndex(listeGlobal, 1, nouveau3);  
    SANDBOX_END;
    check_equal(init, listeGlobal, exp3, 3, 2, 1);

    free(init);
}


int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5);
}
