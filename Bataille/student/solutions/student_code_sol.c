#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"
#include "../help_functions.h"

void simulateOneRound_sol(deck_t** playersDeck, int manyPlayers){
    int playersActiveCard[manyPlayers];
    deck_t* table = createDeck(0, NULL, 0);

    for(int i = 0; i < manyPlayers; i++){
        int cardVal = drawCard(playersDeck[i]);
        playersActiveCard[i] = cardVal;
        if(cardVal > 0) addCard(table, cardVal);
    }

    int playersLeft = 0;
    int bestCardVal = findBestActiveCard(playersActiveCard, manyPlayers);

    for(int i = 0; i < manyPlayers; i++){
        if(playersActiveCard[i] < bestCardVal) playersActiveCard[i] = -1;
        else playersLeft++;
    }

    while(playersLeft > 1){
        for(int i = 0; i < manyPlayers; i++){
            if(playersActiveCard[i] > 0){
                // Hidden card
                int cardVal = drawCard(playersDeck[i]);
                if(cardVal>0) addCard(table, cardVal);

                // New card
                cardVal = drawCard(playersDeck[i]);
                playersActiveCard[i]=cardVal;
                if(cardVal>0) addCard(table, cardVal);
            }
        }

        bestCardVal = findBestActiveCard(playersActiveCard, manyPlayers);
        playersLeft = 0;
        for(int i = 0; i < manyPlayers; i++){
            if(playersActiveCard[i] < bestCardVal) playersActiveCard[i] = -1;
            else playersLeft++;
        }
    }

    int winner = 0;
    for(int i = 0; i < manyPlayers; i++) if(playersActiveCard[i]>0) winner=i;

    int totalCards = table->size;

    for(int i = 0; i < totalCards; i++){
        int cardVal = drawCard(table);
        addCard(playersDeck[winner], cardVal);
    }
}

int guessWhoWins_sol(deck_t ** playersDeck, int manyPlayers, int maxRounds){
    int cardsCount = 0;

    // Counting cards
    for(int i = 0; i < manyPlayers; i++)
        cardsCount += playersDeck[i]->size;

    // Check each turn if the game is over
    for(int i = 0; i < maxRounds; i++){
        simulateOneRound_sol(playersDeck, manyPlayers);
        for(int j = 0; j < manyPlayers; j++)
            if (playersDeck[j]->size == cardsCount) return playersDeck[j]->id_player;
    }
    return -1;
}
