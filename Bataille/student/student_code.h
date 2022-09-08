#ifndef SCODE_H
#define SCODE_H
#include "help_functions.h"





/*
 * @pre playersDeck != NULL, manyPlayers > 0
 * @post simule un tour du jeu bataille en modifiant les decks des joueurs
 */
void simulateOneRound(deck_t** playersDeck, int manyPlayers);

/*
 * @pre playersDeck != NULL, manyPlayers > 0, maxRounds > 0
 * @post retourne l'id du joueur gagnant, ou -1 si la partie n'est pas terminée
 */
int guessWhoWins(deck_t ** playersDeck, int manyPlayers, int maxRounds);
#endif