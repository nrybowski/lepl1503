#include <stdlib.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

char *str_array(char **array, int nb){
    char *res = malloc(200);
    strcpy(res, "[");
    for (int i = 0; i<nb; i++){
        strcat(res, "\"");
        strcat(res, *(array+i));
        strcat(res,"\"");
        if (i != nb - 1) strcat(res, ", ");
    }
    strcat(res, "]");
    return res;
}

void error(char **result, char **expected, int nb){
    char *template = _("Wrong array returned. The expected answer was %s, while you returned %s");
    char msg[strlen(template)+400];
    char *res_str = str_array(result, nb);
    char *exp_str = str_array(expected, nb);
    sprintf(msg, template, exp_str, res_str);
    push_info_msg(msg);
    free(res_str);
    free(exp_str);
}

void test1(){
    set_test_metadata("get_last_generation", "Test avec tree==NULL", 1);
    // test pour vérifier que l'étudiant retourne NULL lorsque l'argument tree est NULL
    family_tree_t * tree=NULL;
    char ** expected=NULL;
    char ** result=NULL;
    char **ret;
    SANDBOX_BEGIN;
    ret = get_last_generation(tree,result);
    SANDBOX_END;
    CU_ASSERT_EQUAL(ret,expected);   
    if (ret != expected) push_info_msg("You should return NULL when the tree is NULL");
}

void test2(){
    //test dans le cas où toutes les personnes de la seconde génération ont au moins un enfant
    set_test_metadata("get_last_generation", "Test quand chaque personne de la deuxième génération a au moins 1 enfant", 1);

    char * all_surnames[8]={"Arthur","Marie","Théo","Elisa","Léa","Léo","Antoine","Julie"};
    int all_number_children[8]={2,2,1,3,0,0,0,0};

    //création de toutes les personnes
    person_t tab[8];
    for (int i = 0; i < 8; i++){
        tab[i].surname=all_surnames[i];
        tab[i].n_children=all_number_children[i];
        
    }
    //les 4 dernières personnes (les petits-enfants) n'ont pas d'enfant
    for (int i = 4; i<8; i++)
    {
        tab[i].children=NULL;
    }
    //enfant de Théo
    person_t enfants_theo[1]={tab[4]};
    tab[2].children=enfants_theo;
    
    //enfants de Elisa
    person_t enfants_Elisa[3]={tab[5],tab[6],tab[7]};
    tab[3].children=enfants_Elisa;

    // les 2 premières personnes (les grands-parents) ont les mêmes enfants
    person_t enfants_grandsparents [2]={tab[2],tab[3]};
    tab[0].children=enfants_grandsparents;
    tab[1].children=enfants_grandsparents;
    
    family_tree_t tree;
    tree.grand_father=&tab[0];
    tree.grand_mother=&tab[1];

    char * expected[4]={"Antoine","Julie","Léa","Léo"}; // prénoms des petits-enfants triés par ordre alphabétique
    char *res[4];
    char ** result;
    SANDBOX_BEGIN;
    result=get_last_generation(&tree,res);
    SANDBOX_END;
    for (int i = 0; i < 4; i++)
    {
        CU_ASSERT_STRING_EQUAL(result[i],expected[i]);
        if (result[i] != expected[i]) return error(result, expected, 4);
    }
    
}
void test3(){
  // test dans le cas où aucune personne de la seconde génération n'a d'enfant
   set_test_metadata("get_last_generation", "Test quand aucune personne de la deuxième génération n'a d'enfant", 1);
   char * all_surnames[5]={"Arthur","Marie","Théo","Elisa","Léa"};
   int all_number_children[5]={3,3,0,0,0};

    //création de toutes les personnes
    person_t tab[5];
    for (int i = 0; i < 5; i++){
        tab[i].surname=all_surnames[i];
        tab[i].n_children=all_number_children[i];
        
    }
    //les personnes de la deuxième génération n'ont pas d'enfant
    for (int i = 2; i<=4; i++)
    {
        tab[i].children=NULL;
    }
    
    // les 2 premières personnes (les grands-parents) ont les mêmes enfants
    person_t enfants_grandsparents [3]={tab[2],tab[3],tab[4]};
    tab[0].children=enfants_grandsparents;
    tab[1].children=enfants_grandsparents;
    
    family_tree_t tree;
    tree.grand_father=&tab[0];
    tree.grand_mother=&tab[1];
    char * expected[1]={"Pas d'enfant"};
    char * res[1];
    char ** result;
    SANDBOX_BEGIN;
    result = get_last_generation(&tree,res);
    SANDBOX_END;
    CU_ASSERT_STRING_EQUAL(result[0],expected[0]);
    if (strcmp(result[0], expected[0]) != 0) error(result, expected, 1);
    
}
void test4(){
    // test dans le cas où certaines personnes de seconde génération ont un enfant et d'autres n'en ont pas
    set_test_metadata("get_last_generation", "Test quand des personnes de la deuxième génération ont des enfants et d'autres non", 1);

    char * all_surnames[9]={"Arthur","Marie","Théo","Elisa","Léa","Léo","Antoine","Julie","Arnaud"};
    int all_number_children[9]={3,3,1,3,0,0,0,0,0};

    //création de toutes les personnes
    person_t tab[9];
    for (int i = 0; i < 9; i++){
        tab[i].surname=all_surnames[i];
        tab[i].n_children=all_number_children[i];
        
    }
    //les 4 dernières personnes (les petits-enfants et une personne de seconde génération) n'ont pas d'enfant
    for (int i = 4; i<=8; i++)
    {
        tab[i].children=NULL;
    }
    //enfant de Théo
    person_t enfants_theo[1]={tab[5]};
    tab[2].children=enfants_theo;
    
    //enfants de Elisa
    person_t enfants_Elisa[3]={tab[6],tab[7],tab[8]};
    tab[3].children=enfants_Elisa;

    // les 2 premières personnes (les grands-parents) ont les mêmes enfants
    person_t enfants_grandsparents [3]={tab[2],tab[3],tab[4]};
    tab[0].children=enfants_grandsparents;
    tab[1].children=enfants_grandsparents;
    
    family_tree_t tree;
    tree.grand_father=&tab[0];
    tree.grand_mother=&tab[1];

    char * expected[4]={"Antoine","Arnaud","Julie","Léo"}; // prénoms des petits-enfants triés par ordre alphabétique
    char *res[4];
    char ** result;

    SANDBOX_BEGIN;
    result=get_last_generation(&tree,res);
    SANDBOX_END;

    for (int i = 0; i < 4; i++)
    {
        CU_ASSERT_STRING_EQUAL(result[i],expected[i]);
        if (strcmp(result[i],expected[i]) != 0) return error(result, expected, 4);
    }
      
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4);
}
