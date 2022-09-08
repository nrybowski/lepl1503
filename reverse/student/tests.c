#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 200

char *str_list(node_t *s){
    if (s==NULL){
        char *temp = "NULL";
        char *ret = malloc(strlen(temp)+1);
        strcpy(ret, temp);
        return ret;
    }
    char *ret = malloc(SIZE);
    char *template = "%d";
    strcpy(ret, "[");
    while(s){
        char temp[strlen(template)];
        sprintf(temp, template, s->val);
        strcat(ret, temp);
        if (s->next) strcat(ret, ", ");
        s = s->next;
    }
    strcat(ret, "]");
    return ret;

}

void error(char *init, node_t *s){
    char *template = _("Wrong list value. With the initial list %s, you returned %s");
    char msg[strlen(template) + 2*SIZE];
    char *list_str = str_list(s);
    sprintf(msg, template, init, list_str);
    push_info_msg(msg);
    free(list_str);
}

char *list_init;

void compare_list(node_t *res, int *exp, int nb){
    node_t * temp = res;
    for (int i = 0; i < nb; i++){
        CU_ASSERT_NOT_EQUAL(res, NULL);
        if (res == NULL) return error(list_init, temp);
        CU_ASSERT_EQUAL(res->val, *(exp+i));
        if (res->val !=  *(exp+i)) return error(list_init, temp);
        res = res->next;
    }
    CU_ASSERT_EQUAL(res, NULL);
    if (res != NULL) push_info_msg("Your last node's next should be initialized to NULL");
}

void test1(){

    set_test_metadata("reverse", "Test minimum de [-1,1,5,10]", 1);

    // test de base minimaliste
    node_t e3={10,NULL};
    node_t e2={5,&e3};
    node_t e1={1,&e2};
    node_t heade={-1,&e1};

    list_init = str_list(&heade);


    node_t* ans = NULL;
    SANDBOX_BEGIN;
    ans=reverse(&heade);
    SANDBOX_END;

    int exp[] = {10,5,1,-1};

    compare_list(ans, exp, 4);

    free(list_init);
    
}
    
void test2(){

    set_test_metadata("reverse", "Test minimum de [-10, 1, 5]", 1);

    // test de base minimaliste
    node_t e2={5,NULL};
    node_t e1={1,&e2};
    node_t heade={-10,&e1};

    list_init = str_list(&heade);
    
    node_t* ans = NULL;

    SANDBOX_BEGIN;
    ans=reverse(&heade);
    SANDBOX_END;

    int exp[] = {5,1, -10};

    compare_list(ans, exp, 3);

    free(list_init);
    
}


void test3(){

    set_test_metadata("reverse", "Test on more elements", 1);

    node_t e6={1,NULL};
    node_t e5={2,&e6};
    node_t e4={3,&e5};
    node_t e3={4,&e4};
    node_t e2={5,&e3};
    node_t e1={6,&e2};
    node_t heade={7,&e1};

    list_init = str_list(&heade);

    node_t* ans = NULL;
    
    SANDBOX_BEGIN;
    ans=reverse(&heade);
    SANDBOX_END;

    int exp[] = {1, 2, 3, 4, 5, 6, 7};

    compare_list(ans, exp, 7);

    free(list_init);
    
}

void test4(){

    set_test_metadata("reverse", "Test for NULL as last next", 1);

    // test pour verifer que NULL se trouve bien a la fin de la liste retourné
    node_t e1={1,NULL};
    node_t heade={-10,&e1};

    list_init = str_list(&heade);

    node_t* ans = NULL;

    SANDBOX_BEGIN;
    ans=reverse(&heade);
    SANDBOX_END;

    int exp[] = {1, -10};

    compare_list(ans, exp, 2);

    free(list_init);
    
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4);
}
