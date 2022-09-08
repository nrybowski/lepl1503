#include "help_functions.h"

// Functions' body
void print_deck(deck_t* deck){
    card_t* current = deck->head;
    printf("Player (%d) has %d card(s) : {", deck->id_player, deck->size);
    while(current!=NULL){
        printf("%d", current->value);
        if(current->next!=NULL) printf(", ");
        current = current->next;
    }
    printf("}\n");
}



int addCard(deck_t* d, int val){
    card_t* new_card = (card_t*) malloc(sizeof(card_t));
    if(new_card==NULL) return -1;
    new_card->value = val;
    new_card->next=NULL;
    if(d->tail == NULL){
        d->head = new_card;
        d->tail = new_card;
    }
    else {
        d->tail->next = new_card;
        d->tail = new_card;
    }
    d->size++;
    return 0;
}


int drawCard(deck_t* d){
    card_t* temp = d->head;
    int cardVal;
    if(temp != NULL){
        cardVal = temp->value;
        d->head = d->head->next;
        d->size--;
        if(d->size == 0) d->tail=NULL;
    }
    else cardVal = -1;

    free(temp);
    return cardVal;
}


deck_t* createDeck(int id, int* cardsData, int nCards){
    deck_t* deck = malloc(sizeof(deck_t));
    deck->id_player=id;
    deck->size=0;
    deck->head=NULL;
    deck->tail=NULL;
    for(int i = 0; i < nCards; i++) addCard(deck, cardsData[i]);
    return deck;
}

int findBestActiveCard(const int* activeCards, int manyPlayers){
    int currBest = 0;
    for(int i = 0; i < manyPlayers; i++){
        if(activeCards[i] > currBest) currBest=activeCards[i];
    }
    return currBest;
}
