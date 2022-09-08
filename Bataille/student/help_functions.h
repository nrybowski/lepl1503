#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <stdlib.h>

// Structures
typedef struct card{
    int value;
    struct card* next;
} card_t;

typedef struct deck{
    int id_player;
    int size;
    struct card* tail;
    struct card* head;
} deck_t;

// Prototypes
/**
*/

/**
* @brief: print the deck
*
* @arg : deck != NULL : the deck to print
*/
void print_deck(deck_t* deck);

/**
* @brief: add a card of value val to the bottom of deck d
*
* @arg : 0<=val<=12 : value of the card
* @arg : deck != NULL : the deck in which we insert the card
*
*@return 0 if no error
*       -1 otherwise
*/
int addCard(deck_t* d, int val);

/**
* @brief: remove the card at the top of deck d and return it's value
*
* @arg : deck != NULL : the deck in which we draw a card
*
* @return the value of the card at top of the deck
*         -1 if the deck is empty
*/
int drawCard(deck_t* d);

/**
* @brief: create a new deck
*
* @arg id        : the id of the player/deck
* @arg cardsData : the list of value of cards to insert in the deck, NULL if empty
* @arg nCards    : the length of the list cardsData
* @return the new deck
*/
deck_t* createDeck(int id, int* cardsData, int nCards);

/**
* @brief: compare the cards and return the value of the best card
*
* @arg activeCards : list of cards to compare
* @arg manyPlayers : length of the list activeCards
*
* @return the value of the best card
*/
int findBestActiveCard(const int* activeCards, int manyPlayers);


#endif