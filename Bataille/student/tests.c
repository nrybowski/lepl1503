#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "help_functions.h"
#include "../../course/common/student/CTester/CTester.h"

char *str_deck(deck_t* deck){
    card_t* current = deck->head;
    char *msg = _("Player (%d) has %d card(s) : {");
    char *ret = malloc(strlen(msg)+3*deck->size+1);
    sprintf(ret, msg, deck->id_player, deck->size);
    while(current!=NULL){
        char *temp;
        if(current->next!=NULL) temp = "%d, ";
        else temp = "%d";
        char value[strlen(temp)];
        sprintf(value, temp, current->value);
        strcat(ret, value);
        current = current->next;
    }
    strcat(ret, "}");
    return ret;
}

void error_winner(int winner, int exp_winner){
    char *err = _("You returned the wrong winner. The expected winner was %d but you returned %d");
    char errMsg[strlen(err)];
    sprintf(errMsg, err, exp_winner, winner);
    push_info_msg(errMsg);
}

int flag = 1;

void error_deck(deck_t **returned, deck_t **expected, int nbPlayers){

    char *err = "Wrong value returned. Expected was %s, returned was %s";
    char errMsg[strlen(err)+500];
    char exp[250];
    char ret[250];
    strcpy(exp, "[");
    strcpy(ret, "[");
    for (size_t i = 0; i < nbPlayers; i++)
    {
        char *exp_str = str_deck(*(expected+i));
        strcat(exp, exp_str);
        free(exp_str);

        char *ret_str = str_deck(*(returned+i));
        strcat(ret, ret_str);
        free(ret_str);

        if (i != nbPlayers -1){
            strcat(ret, " / ");
            strcat(exp, " / ");
        }
    }

    strcat(exp, "]");
    strcat(ret, "]");
    sprintf(errMsg, err, exp, ret);
    push_info_msg(errMsg);
    
}

void sor_test1(){
    set_test_metadata("simulateOneRound", _("Test manche simple 1 joueur"), 1);
    int p1Hand[] = {4, 2, 9};
    deck_t* p1 =  createDeck(1, p1Hand, 3);
    deck_t* players_decks[] = {p1};

    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 1);
    SANDBOX_END;

    flag = 1;

    int p1HandExpected[] = {2, 9, 4};
    deck_t* p1Expected =  createDeck(1, p1HandExpected, 3);
    deck_t* decksExpected[] = {p1Expected};
    card_t* currentCard = p1->head;
    for(int i = 0; i < 3; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
            if (currentCard->value != p1HandExpected[i]){
                flag = 0;
            }
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL){
        flag = 0;
    }
    if (!flag){
        error_deck(players_decks, decksExpected, 1);
    }
}

void sor_test2(){
    set_test_metadata("simulateOneRound", _("Test manche simple 1 joueur main vide"), 1);
    int p1Hand[] = {};
    deck_t* p1 =  createDeck(1, p1Hand, 0);
    deck_t* players_decks[] = {p1};

    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 1);
    SANDBOX_END;
        flag = 1;
    card_t* currentCard = p1->head;
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL){
        push_info_msg("La main du joueur est censée rester vide");
    }
}

void sor_test3(){
    set_test_metadata("simulateOneRound", _("Test manche simple 2 joueurs"), 1);
    int p1Hand[] = {4, 2, 9};
    deck_t* p1 =  createDeck(1, p1Hand, 3);

    int p2Hand[] = {5, 1, 3};
    deck_t* p2 =  createDeck(2, p2Hand, 3);

    deck_t* players_decks[] = {p1, p2};
    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 2);
    SANDBOX_END;
    flag = 1;

    int p1HandExpected[] = {2, 9};
    deck_t *p1Expected = createDeck(1,p1HandExpected, 2);
    int p2HandExpected[] = {1, 3, 4, 5};
    deck_t *p2Expected = createDeck(2,p2HandExpected, 4);

    deck_t *decks_exp[] = {p1Expected, p2Expected};

    card_t* currentCard = p1->head;
    for(int i = 0; i < 2; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
            if (currentCard->value != p1HandExpected[i]) flag=0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if(currentCard != NULL) flag = 0;

    currentCard = p2->head;
    for(int i = 0; i < 4; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p2HandExpected[i]);
            if (currentCard->value != p2HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL){
        flag = 0;
    }

    if (!flag){
        error_deck(players_decks, decks_exp, 2);
    }
}

void sor_test4(){
    set_test_metadata("simulateOneRound", _("Test manche simple 2 joueurs (1 main vide)"), 1);
    int p1Hand[] = {4, 2, 9};
    deck_t* p1 =  createDeck(1, p1Hand, 3);

    int p2Hand[] = {};
    deck_t* p2 =  createDeck(2, p2Hand, 0);

    deck_t* players_decks[] = {p1, p2};
    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 2);
    SANDBOX_END;
    flag = 1;

    int p1HandExpected[] = {2, 9, 4};
    deck_t* p1_exp = createDeck(1, p1HandExpected, 3);
    int temp[0];
    deck_t*p2_exp = createDeck(2, temp , 0);

    deck_t *decks_exp[] ={p1_exp, p2_exp};


    card_t* currentCard = p1->head;
    for(int i = 0; i < 3; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
            if (currentCard->value != p1HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    CU_ASSERT_EQUAL(p2->head, NULL);
    if (p2->head != NULL) flag = 0;

    if (!flag){
        error_deck(players_decks, decks_exp, 2);
    }
}

void sor_test5(){
    set_test_metadata("simulateOneRound", _("Test manche simple 4 joueurs"), 1);
    int p1Hand[] = {4, 2, 9};
    deck_t* p1 =  createDeck(1, p1Hand, 3);

    int p2Hand[] = {5, 1, 3};
    deck_t* p2 =  createDeck(2, p2Hand, 3);

    int p3Hand[] = {6, 2, 3};
    deck_t* p3 =  createDeck(3, p3Hand, 3);

    int p4Hand[] = {7, 2, 1};
    deck_t* p4 =  createDeck(4, p4Hand, 3);

    deck_t* players_decks[] = {p1, p2, p3, p4};
    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 4);
    SANDBOX_END;

    flag = 1;

    int p1HandExpected[] = {2, 9};
    deck_t* p1_exp =  createDeck(1, p1HandExpected, 2);
    int p2HandExpected[] = {1, 3};
    deck_t* p2_exp =  createDeck(2, p2HandExpected, 2);
    int p3HandExpected[] = {2, 3};
    deck_t* p3_exp =  createDeck(3, p3HandExpected, 2);
    int p4HandExpected[] = {2, 1, 4, 5, 6, 7};
    deck_t* p4_exp =  createDeck(4, p4HandExpected, 6);

    deck_t *decks_exp[] = {p1_exp, p2_exp, p3_exp, p4_exp};

    card_t* currentCard = p1->head;
    for(int i = 0; i < 2; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
            if (currentCard->value != p1HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
        if (currentCard->value != p1HandExpected[i]) flag = 0;
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p2->head;
    for(int i = 0; i < 2; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p2HandExpected[i]);
            if (currentCard->value != p2HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p3->head;
    for(int i = 0; i < 2; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p3HandExpected[i]);
            if (currentCard->value != p3HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p4->head;
    for(int i = 0; i < 6; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p4HandExpected[i]);
            if (currentCard->value != p4HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    if (!flag){
        error_deck(players_decks, decks_exp, 4);
    }
}

void sor_test6(){
    set_test_metadata("simulateOneRound", _("Test manche moyenne égalité 2 joueurs"), 1);
    int p1Hand[] = {4, 2, 9, 5};
    deck_t* p1 =  createDeck(1, p1Hand, 4);

    int p2Hand[] = {4, 1, 3, 8};
    deck_t* p2 =  createDeck(2, p2Hand, 4);

    deck_t* players_decks[] = {p1, p2};

    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 2);
    SANDBOX_END;

    flag = 1;

    int p1HandExpected[] = {5, 4, 4, 2, 9, 1, 3};
    deck_t *p1_exp = createDeck(1, p1HandExpected, 7);
    int p2HandExpected = 8;
    int temp[] = {8};
    deck_t *p2_exp = createDeck(2, temp , 1);

    deck_t *decks_exp[] = {p1_exp, p2_exp};

    card_t* currentCard = p1->head;
    for(int i = 0; i < 7; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p1HandExpected[i]);
            if (currentCard->value != p1HandExpected[i]) flag = 0;
        }
        else {
            flag = 0;
            break;
        }
        currentCard = currentCard->next;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p2->head;
    if(currentCard != NULL) {
        CU_ASSERT_EQUAL(currentCard->value, p2HandExpected);
        if (currentCard->value != p2HandExpected) flag = 0;
        currentCard = currentCard->next;
    }
    else {
        flag = 0;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    
    if (!flag){
        error_deck(players_decks, decks_exp, 4);
    }

}

void sor_test7(){
    set_test_metadata("simulateOneRound", _("Test manche moyenne égalité 3 joueurs"), 1);
    int p1Hand[] = {4, 2, 9, 5};
    deck_t* p1 =  createDeck(1, p1Hand, 4);

    int p2Hand[] = {4, 1, 3, 8};
    deck_t* p2 =  createDeck(2, p2Hand, 4);

    int p3Hand[] = {4, 2, 11, 1};
    deck_t* p3 =  createDeck(2, p3Hand, 4);

    deck_t* players_decks[] = {p1, p2, p3};

    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 3);
    SANDBOX_END;

    flag = 1;

    int temp[] = {5};
    int p1HandExpected = 5;
    deck_t *p1_exp = createDeck(1, temp, 1);
    int p2HandExpected = 8;
    int temp2[] = {8};
    deck_t *p2_exp = createDeck(2, temp2, 1);
    int p3HandExpected[] = {1, 4, 4, 4, 2, 9, 1, 3, 2, 11};  
    deck_t *p3_exp = createDeck(3, p3HandExpected, 10);

    deck_t *decks_exp[] = {p1_exp, p2_exp, p3_exp};

    card_t* currentCard = p1->head;
    if(currentCard != NULL) {
        CU_ASSERT_EQUAL(currentCard->value, p1HandExpected);
        if (currentCard->value != p1HandExpected) flag = 0;
        currentCard = currentCard->next;
    }
    else {
        flag = 0;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p2->head;
    if(currentCard != NULL) {
        CU_ASSERT_EQUAL(currentCard->value, p2HandExpected);
        if (currentCard->value != p2HandExpected) flag = 0;
        currentCard = currentCard->next;
    }
    else {
        flag = 0;
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p3->head;
    for(int i = 0; i < 10; i++){
        if(currentCard != NULL) {
            CU_ASSERT_EQUAL(currentCard->value, p3HandExpected[i]);
            if (currentCard->value != p3HandExpected[i]) flag = 0;
            currentCard = currentCard->next;
        }
        else {
            flag = 0;
            break;
        }
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    
    if (!flag){
        error_deck(players_decks, decks_exp, 4);
    }
}

void sor_test8(){
    set_test_metadata("simulateOneRound", _("Test manche compliquée plusieurs égalités 4 joueurs"), 1);
    int p1Hand[] = {4, 2, 9, 5};
    deck_t* p1 =  createDeck(1, p1Hand, 4);

    int p2Hand[] = {4, 1, 9, 8};
    deck_t* p2 =  createDeck(2, p2Hand, 4);

    int p3Hand[] = {4, 2, 11, 1, 3};
    deck_t* p3 =  createDeck(3, p3Hand, 5);

    int p4Hand[] = {4, 2, 11, 2, 5};
    deck_t* p4 =  createDeck(4, p4Hand, 5);

    deck_t* players_decks[] = {p1, p2, p3, p4};

    SANDBOX_BEGIN;
    simulateOneRound(players_decks, 4);
    SANDBOX_END;

    flag = 1;

    int p1HandExpected = 5;
    int temp[]  = {5};
    deck_t *p1_exp = createDeck(1, temp, 1);
    int p2HandExpected = 8;
    int temp2[] = {8};
    deck_t *p2_exp = createDeck(2, temp2, 1);
    int temp3[0];
    deck_t *p3_exp = createDeck(3, temp3, 0);
    // Empty for player 3 //
    int p4HandExpected[] = {4, 4, 4, 4, 2, 9, 1, 9, 2, 11, 2, 11, 1, 3, 2, 5};
    deck_t *p4_exp = createDeck(4, p4HandExpected, 16);

    deck_t *decks_exp[] = {p1_exp, p2_exp, p3_exp, p4_exp};

    card_t* currentCard = p1->head;
    if(currentCard != NULL) {
        CU_ASSERT_EQUAL(currentCard->value, p1HandExpected);
        if (currentCard->value != p1HandExpected) flag = 0;
        currentCard = currentCard->next;
        CU_ASSERT_EQUAL(currentCard, NULL);
        if (currentCard != NULL) flag = 0;
    }
    else {
        flag = 0;
    }

    currentCard = p2->head;
    if(currentCard != NULL) {
        CU_ASSERT_EQUAL(currentCard->value, p2HandExpected);
        if (currentCard->value != p2HandExpected) flag = 0;
        currentCard = currentCard->next;
        CU_ASSERT_EQUAL(currentCard, NULL);
        if (currentCard != NULL) flag = 0;
    }
    else {
        flag = 0;
    }

    currentCard = p3->head;
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    currentCard = p4->head;
    for(int i = 0; i < 16; i++){
        if(currentCard != NULL){
            CU_ASSERT_EQUAL(currentCard->value, p4HandExpected[i]);
            if (currentCard->value != p4HandExpected[i]) flag = 0;
            currentCard = currentCard->next;
        }
        else{
            flag = 0;
            break;
        }
    }
    CU_ASSERT_EQUAL(currentCard, NULL);
    if (currentCard != NULL) flag = 0;

    
    if (!flag){
        error_deck(players_decks, decks_exp, 4);
    }
}

void gww_test1(){
    set_test_metadata("guessWhoWin", _("Test partie 1 joueur"), 1);
    int maxRounds = 100;
    int p1Hand[] = {4, 2, 9};
    deck_t* p1 = createDeck(0, p1Hand, 3);
    deck_t* players_decks[] = {p1};
    int winner;
    SANDBOX_BEGIN;
    winner = guessWhoWins(players_decks, 1, maxRounds);
    SANDBOX_END;
    CU_ASSERT_EQUAL(winner, 0);
    if (winner != 0){
        error_winner(winner, 0);
    }
}

void gww_test2(){
    set_test_metadata("guessWhoWin", _("Test partie 2 joueurs qui se finit en n manches avec n < maxRounds"), 1);
    int maxRounds = 100;

    int cardsP1[] = {3, 2, 9, 5, 5, 10, 2, 13, 4, 1};
    deck_t* p1 = createDeck(1, cardsP1, 10);

    int cardsP2[] = {4, 1, 2, 9, 8, 13, 2, 2, 4, 10};
    deck_t* p2 = createDeck(2, cardsP2, 10);

    deck_t* players_decks[] = {p1, p2};

    int winner;
    SANDBOX_BEGIN;
    winner = guessWhoWins(players_decks, 2, maxRounds);
    SANDBOX_END;
    CU_ASSERT_EQUAL(winner, 2);
    if (winner != 2){
        error_winner(winner, 2);
    }
}

void gww_test3(){
    set_test_metadata("guessWhoWin", _("Test partie 2 joueurs qui ne se finit pas en n manches et n > maxRounds"), 1);
    int maxRounds = 100;

    int cardsP1[] = {3, 2, 9, 5, 2, 5, 10, 2, 13, 4};
    deck_t* p1 = createDeck(1, cardsP1, 10);

    int cardsP2[] = {4, 1, 9, 8, 10, 13, 2, 2, 4, 3};
    deck_t* p2 = createDeck(2, cardsP2, 10);

    deck_t* players_decks[] = {p1, p2};

    int winner;
    SANDBOX_BEGIN;
    winner = guessWhoWins(players_decks, 2, maxRounds);
    SANDBOX_END;
    CU_ASSERT_EQUAL(winner, -1);
    if (winner != -1){
        char buf[100];
        sprintf(buf, "You returned the wrong value (%d). The game is still going up to these days...", winner);
        push_info_msg(buf);
    }
}

void gww_test4(){
    set_test_metadata("guessWhoWin", _("Test partie compliquée à 4 joueurs qui se finit en n manches avec  100 < n < maxRounds"), 1);
    int maxRounds = 200;

    int cardsP1[] = {3, 2, 9, 5, 2, 5, 10, 2, 13, 4};
    deck_t* p1 = createDeck(1, cardsP1, 10);

    int cardsP2[] = {4, 1, 9, 8, 10, 13, 2, 2, 4, 3};
    deck_t* p2 = createDeck(2, cardsP2, 10);

    int cardsP3[] = {8, 7, 9, 8, 10, 11, 2, 1, 4, 13};
    deck_t* p3 = createDeck(3, cardsP3, 10);

    int cardsP4[] = {10, 1, 13, 8, 11, 7, 2, 2, 5, 3};
    deck_t* p4 = createDeck(4, cardsP4, 10);

    deck_t* players_decks[] = {p1, p2, p3, p4};

    int winner;
    SANDBOX_BEGIN;
    winner = guessWhoWins(players_decks, 4, maxRounds);
    SANDBOX_END;
    CU_ASSERT_EQUAL(winner, 1);
    if (winner != 1){
        error_winner(winner, 1);
    }
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(sor_test1, sor_test2, sor_test3, sor_test4, sor_test5, sor_test6, sor_test7, sor_test8, gww_test1, gww_test2, gww_test3, gww_test4);
}
