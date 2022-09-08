#include <stdlib.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

void error(int ret, int exp){
    char *template = "You returned the wrong value. For information, your fonction returned %d, while it should return %d";
    char msg[strlen(template)];
    sprintf(msg, template, ret, exp);
    push_info_msg(msg);
}

void check_ret(int ret, int exp){
    CU_ASSERT_EQUAL(ret, exp);
    if (ret != exp) error(ret, exp);
}

void test1_add(){
    set_test_metadata("addstuff", "Test simple", 1);

    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret1 = 42;
    int ret2 = 42;
    int ret3 = 42;

    SANDBOX_BEGIN;
    ret1 = AddStuff(client, "teddy bear", 10);
    ret2 = AddStuff(client, "candy", 0);
    ret3 = AddStuff(client, "TV", 200);
    SANDBOX_END;

    check_ret(ret1, 0);
    check_ret(ret2, 0);
    check_ret(ret3, 0);

    char* listName[] = {"teddy bear","candy", "TV"};
    CU_ASSERT_EQUAL(client->total, 210);
    if (client->total != 210) push_info_msg("You don't update correctly the client total");
    for(int j = 0; j < 3; j++){
        CU_ASSERT_STRING_EQUAL(client->bag[j]->name, listName[j]);
        if (strcmp(client->bag[j]->name, listName[j]) != 0) push_info_msg("The items aren't inserted correctly in the bag");
    }
    for(int i = 0; i < client->bagSize; i++){
        free(client->bag[i]);
    }
    free(client->bag);
    free(client);
    return;
}

void test2_add(){
    set_test_metadata("addstuff", "Test dontLike", 1);

    char* dontLike[] = {"fish", "salad", "teddy bear"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 3);

    int ret1 = 42;
    int ret2 = 42;
    int ret3 = 42;
    int ret4 = 42;
    int ret5 = 42;
    int ret6 = 42;

    SANDBOX_BEGIN;
    ret1 = AddStuff(client, "teddy bear", 10);
    ret2 = AddStuff(client, "poney", 2000);
    ret3 = AddStuff(client, "salad", 5);
    ret4 = AddStuff(client, "candy", 2);
    ret5 = AddStuff(client, "TV", 200);
    ret6 = AddStuff(client, "fish", 20);
    SANDBOX_END;

    check_ret(ret1, -3);
    check_ret(ret2, 0);
    check_ret(ret3, -3);
    check_ret(ret4, 0);
    check_ret(ret5, 0);
    check_ret(ret6, -3);

    char* listName[] = {"poney", "candy", "TV"};
    CU_ASSERT_EQUAL(client->total, 2202);
    if (client->total != 2202) push_info_msg("You don't update correctly the client total");
    for(int j = 0; j < 3; j++){
        CU_ASSERT_STRING_EQUAL(client->bag[j]->name, listName[j]);
        if (strcmp(client->bag[j]->name, listName[j]) != 0) push_info_msg("The items aren't inserted correctly in the bag. Don't forget to reject items which are in the dontLike list");
    }
    for(int i = 0; i < client->bagSize; i++){
        free(client->bag[i]);
    }
    free(client->bag);
    free(client);
    return;
}

void test3_add(){
    set_test_metadata("addstuff", "Test budget (1)", 1);

    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret1 = 42;
    int ret2 = 42;
    int ret3 = 42;

    SANDBOX_BEGIN;
    ret1 = AddStuff(client, "car", 30000);
    ret2 = AddStuff(client, "Laptop", 1200);
    ret3 = AddStuff(client, "House", 500000);
    SANDBOX_END;

    check_ret(ret1, -2);
    check_ret(ret2, 0);
    check_ret(ret3, -2);

    char* listName[] = {"Laptop"};
    CU_ASSERT_EQUAL(client->total, 1200);
    if (client->total != 1200) push_info_msg("You don't update correctly the client total");
    for(int j = 0; j < 1; j++){
        CU_ASSERT_STRING_EQUAL(client->bag[j]->name, listName[j]);
        if (strcmp(client->bag[j]->name, listName[j]) != 0) push_info_msg("The items aren't inserted correctly in the bag. Don't forget to put only items which cost less than the client's budget");
    }
    for(int i = 0; i < client->bagSize; i++){
        free(client->bag[i]);
    }
    free(client->bag);
    free(client);
    return;
}

void test4_add(){
    set_test_metadata("addstuff", "Test budget (2)", 1);
    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret1 = 42;
    int ret2 = 42;
    int ret3 = 42;
    int ret4 = 42;

    SANDBOX_BEGIN;
    ret1 = AddStuff(client, "TV", 500);
    ret2 = AddStuff(client, "Laptop", 1200);
    ret3 = AddStuff(client, "Gaz", 3000);
    ret4 = AddStuff(client, "Clothes", 400);
    SANDBOX_END;

    check_ret(ret1, 0);
    check_ret(ret2, 0);
    check_ret(ret3, 0);
    check_ret(ret4, -2);

    char* listName[] = {"TV", "Laptop", "Gaz"};
    CU_ASSERT_EQUAL(client->total, 4700);
    if (client->total != 4700) push_info_msg("You don't update correctly the client total");
    for(int j = 0; j < 3; j++){
        CU_ASSERT_STRING_EQUAL(client->bag[j]->name, listName[j]);
        if (strcmp(client->bag[j]->name, listName[j]) != 0) push_info_msg("The items aren't inserted correctly in the bag. Don't forget to put only items which cost less than the client's budget");
    }
    for(int i = 0; i < client->bagSize; i++){
        free(client->bag[i]);
    }
    free(client->bag);
    free(client);
    return;
}

void test5_add(){
    set_test_metadata("addstuff", "Test size", 1);

    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret[11];
    for (size_t i = 0; i < 11; i++)
    {
        ret[i] = 42;
    }
    
    SANDBOX_BEGIN;
    ret[0] = AddStuff(client, "Teddy bear", 10);
    ret[1] = AddStuff(client, "Candy", 2);
    ret[2] = AddStuff(client, "TV", 200);
    ret[3] = AddStuff(client, "beer", 1);
    ret[4] = AddStuff(client, "Food", 15);
    ret[5] = AddStuff(client, "Comics books", 8);
    ret[6] = AddStuff(client, "T-shirt", 7);
    ret[7] = AddStuff(client, "Toys", 30);
    ret[8] = AddStuff(client, "Sponge", 11);
    ret[9] = AddStuff(client, "bread", 3);
    ret[10] = AddStuff(client, "water", 5);
    SANDBOX_END;

    for (int i = 0; i < 10; i++)
    {
        check_ret(ret[i], 0);
    }
    check_ret(ret[10], -5);
    

    CU_ASSERT_EQUAL(client->total, 287);
    if (client->total != 287) push_info_msg("You don't update correctly the client total");

    char* listName[] = {"Teddy bear","Candy", "TV", "beer", "Food", "Comics books", "T-shirt", "Toys", "Sponge", "bread"};
    for(int j = 0; j < 10; j++){
        CU_ASSERT_STRING_EQUAL(client->bag[j]->name, listName[j]);
        if (strcmp(client->bag[j]->name, listName[j]) != 0) push_info_msg("The items aren't inserted correctly in the bag. You can't put any item in the bag when it's already fulls");
    }
    for(int i = 0; i < client->bagSize; i++){
        free(client->bag[i]);
    }
    free(client->bag);
    free(client);
    return;
}

void test6_add(){
    set_test_metadata("addstuff", "Test name==NULL", 1);

    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret = 42;

    SANDBOX_BEGIN;
    ret = AddStuff(client, NULL, 15);
    SANDBOX_END;

    check_ret(ret, -1);

    free(client);
}

void test7_add(){
    set_test_metadata("addstuff", "Test client==NULL", 1);

    char *name = "Switch";

    int ret = 42;

    SANDBOX_BEGIN;
    ret = AddStuff(NULL, name, 289);
    SANDBOX_END;

    check_ret(ret, -1);
}

void test8_add(){
    set_test_metadata("addstuff", "Test malloc fail", 1);

    char *name = "Switch";
    char* dontLike[] = {"fish", "salad"};
    consumer_t * client = NewConsumer("Maximus", 10, 5000, dontLike, 2);

    int ret = 42;

    monitored.malloc = true;
    failures.malloc = FAIL_ALWAYS;

    SANDBOX_BEGIN;
    ret = AddStuff(client, name, 289);
    SANDBOX_END;

    check_ret(ret, -4);

    free(client);
}

int main(int argc,char** argv)
{
    BAN_FUNCS(NewConsumer);
    RUN(test1_add, test2_add, test3_add, test4_add, test5_add, test6_add, test7_add, test8_add);
}
