#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 400

char *artist_str(Artist *a){
    char *template = _("Album( from : %s, genre : %s, price : %d, stock : %d)");
    char *msg = malloc(strlen(template) + 50);
    sprintf(msg, template, a->name, a->genre, a->price, a->stock);
    return msg;
}

char *list_art_str(Artist *a, int nb){
    char *ret = malloc(SIZE);
    char *template = "%d";
    strcpy(ret, "[");
    for (int i = 0; i < nb; i++){
        char temp[strlen(template)];
        char *art_str = artist_str(a + i);
        sprintf(temp, template, art_str);
        strcat(ret, art_str);
        if (i != nb - 1) strcat(ret, ", ");
        free(art_str);
    }
    strcat(ret, "]");
    return ret;
}

void error(Artist *exp, Artist *ret, int exp_len, int ret_len){
    char *template = _("Wrong returned value. The expected answer was %s, while you returned %s");
    char msg[strlen(template) + 2*SIZE];
    char *exp_str = list_art_str(exp, exp_len);
    char *ret_str = list_art_str(ret, ret_len);
    sprintf(msg, template, exp_str, ret_str);
    push_info_msg(msg);
    free(exp_str);
    free(ret_str);
}

void test1(){

    set_test_metadata("possible_vinyls", "Basic 1st test", 1);

    Artist Led = {"Led_Zeppelin", "Rock", 10, 2};
    Artist Bruce = {"Bruce_Springsteen", "Rock", 5, 1};
    Artist Jackson = {"Michael_Jackson", "Pop", 7, 5};
    Artist Swift = {"Taylor_Swift", "Pop", 15, 2};

    char* list_genre[1] = {"Rock"};
    Client Yves = {list_genre, 1, 12};
    Artist List[4] = {Led, Jackson, Bruce, Swift};
    Recommendations result;

    SANDBOX_BEGIN;
    result = possible_vinyls(List, Yves, 4);
    SANDBOX_END;

    int expected_length = 2;
    Artist expected_list[2] = {Led, Bruce};

    CU_ASSERT_EQUAL(expected_length, result.rec_number);
    if (expected_length != result.rec_number) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    for (size_t i = 0; i < result.rec_number; i++) {
        CU_ASSERT_STRING_EQUAL(expected_list[i].name, result.rec_list[i].name);
        if (strcmp(expected_list[i].name, result.rec_list[i].name) != 0) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    }

}

void test2(){

    set_test_metadata("possible_vinyls", "Limited bugdet test", 1);

    Artist Led = {"Led_Zeppelin", "Rock", 10, 2};
    Artist Bruce = {"Bruce_Springsteen", "Rock", 12, 1};
    Artist Jackson = {"Michael_Jackson", "Pop", 7, 5};
    Artist Swift = {"Taylor_Swift", "Pop", 10, 2};

    char* list_genre[1] = {"Pop"};
    Client Yves = {list_genre, 1, 10};
    Artist List[4] = {Led, Jackson, Bruce, Swift};
    Recommendations result;

    SANDBOX_BEGIN;
    result = possible_vinyls(List, Yves, 4);
    SANDBOX_END;

    int expected_length = 2;
    Artist expected_list[2] = {Jackson, Swift};

    CU_ASSERT_EQUAL(expected_length, result.rec_number);
    if (expected_length != result.rec_number) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    for (size_t i = 0; i < result.rec_number; i++) {
        CU_ASSERT_EQUAL(expected_list[i].name, result.rec_list[i].name);
        if (strcmp(expected_list[i].name, result.rec_list[i].name) != 0) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    }

}

void test3(){

    set_test_metadata("possible_vinyls", "Sold out music test", 1);

    Artist Led = {"Led_Zeppelin", "Rock", 10, 2};
    Artist Bruce = {"Bruce_Springsteen", "Rock", 12, 0};
    Artist Jackson = {"Michael_Jackson", "Pop", 7, 0};
    Artist Swift = {"Taylor_Swift", "Pop", 15, 2};

    char* list_genre[2] = {"Pop", "Rock"};
    Client Yves = {list_genre, 2, 36};
    Artist List[4] = {Led, Jackson, Swift, Bruce};

    Recommendations result = {NULL, 0};
    SANDBOX_BEGIN;
    result = possible_vinyls(List, Yves, 4);
    SANDBOX_END;

    int expected_length = 2;
    Artist expected_list[2] = {Led, Swift};

    CU_ASSERT_EQUAL(expected_length, result.rec_number);
    if (expected_length != result.rec_number) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    for (size_t i = 0; i < result.rec_number; i++) {
        CU_ASSERT_EQUAL(expected_list[i].name, result.rec_list[i].name);
        if (strcmp(expected_list[i].name, result.rec_list[i].name) != 0) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    }

}

void test4(){

    set_test_metadata("possible_vinyls", "Nothing corresponds to Yves :'(", 1);

    Artist Led = {"Led_Zeppelin", "Rock", 10, 2};
    Artist Bruce = {"Bruce_Springsteen", "Rock", 12, 1};
    Artist Jackson = {"Michael_Jackson", "Pop", 7, 5};
    Artist Swift = {"Taylor_Swift", "Pop", 15, 2};

    char* list_genre[1] = {"Classic"};
    Client Yves = {list_genre, 1, 10};
    Artist List[4] = {Led, Jackson, Bruce, Swift};
    Recommendations result;
    SANDBOX_BEGIN;
    result = possible_vinyls(List, Yves, 4);
    SANDBOX_END;

    int expected_length = 0;

    CU_ASSERT_EQUAL(expected_length, result.rec_number);
    if (expected_length != result.rec_number){
        char *template = "Wrong return value. Your returned list was of length %d, while the expected is of size %d";
        char msg[strlen(template)];
        sprintf(msg, template, result.rec_number, expected_length);
        push_info_msg(msg);
    }

}

void test5(){

    set_test_metadata("possible_vinyls", "Huuuuge final test", 1);

    Artist Led = {"Led_Zeppelin", "Rock", 10, 2};
    Artist Bruce = {"Bruce_Springsteen", "Rock", 12, 1};
    Artist Beatles = {"The_Beatles", "Rock", 45, 7};
    Artist Clash = {"The_clash", "Rock", 4, 0};
    Artist Aerosmith = {"Aerosmith", "Rock", 19, 1};
    Artist Rs = {"Rolling_stones", "Rock", 56, 23};
    Artist Queen = {"Queen", "Rock", 15, 0};
    Artist Doors = {"The_doors", "Rock", 19.7, 100};

    Artist Dems = {"Damso", "Rap", 15, 5};
    Artist Orelsan = {"Orelsan", "Rap", 25, 7};
    Artist Vald = {"Vald", "Rap", 28, 0};
    Artist Booba = {"Booba", "Rap", 2, 0};
    Artist Sch = {"SCH", "Rap", 10, 25};
    Artist Disiz = {"Disiz", "Rap", 4, 34};

    Artist Ewf = {"Earth_wind_and_fire", "Disco", 34, 2};
    Artist Chic = {"Chic", "Disco", 23, 5};
    Artist Kool = {"Kool_and_the_gang", "Disco", 12, 0};
    Artist Bee = {"Bee_gees", "Disco", 24, 12};
    Artist Abba = {"ABBA", "Disco", 9, 0};

    Artist Daft = {"Daft_punk", "French_touch", 15, 15};
    Artist Justice = {"Justice", "French_touch", 22, 0};

    char* list_genre[4] = {"Rap", "Rock", "Variété", "Disco"};
    Client Vincent = {list_genre, 4, 23};
    Artist List[21] = {Ewf, Booba, Aerosmith, Abba, Bee, Clash, Daft, Chic, Led, Bruce, Disiz, Doors, Justice, Kool, Vald, Dems, Rs, Orelsan, Queen, Sch, Beatles};

    Recommendations result;
    SANDBOX_BEGIN;
    result = possible_vinyls(List, Vincent, 21);
    SANDBOX_END;

    int expected_length = 8;
    Artist expected_list[8] = {Aerosmith, Chic, Led, Bruce, Disiz, Doors, Dems, Sch};

    CU_ASSERT_EQUAL(expected_length, result.rec_number);
    if (expected_length != result.rec_number) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    for (size_t i = 0; i < result.rec_number; i++) {
        CU_ASSERT_EQUAL(expected_list[i].name, result.rec_list[i].name);
        if (strcmp(expected_list[i].name, result.rec_list[i].name) != 0) return error(expected_list, result.rec_list, expected_length, result.rec_number);
    }
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5);
}
