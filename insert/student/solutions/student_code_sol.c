#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

list addToIndex_sol(list list, int index, item* nouveau){
    // Variable temporaire qui va me permettre de suivre l'index
    int i = 0;
    // Je teste l'index car le plus petit est egal a 0
    if(index < 0){
        index = 0;
    }
    // Si ma liste == NULL => cela signifie que l'on ne doit pas chercher ou mettre la donnee. On la met simplement au debut
    if(list == NULL){
        // Ne pas oublier de mettre NULL pour le suivant car une zone memoire est aleatoire donc il faut instancier une valeur
        nouveau->next = NULL;
        return nouveau;
    }
    // Si index = 0, c'est que l'on desire le mettre au debut
    else if(index == 0){
        // On specicie que la suite de notre nouveau bloc est la liste en cours
        nouveau->next = list;
        return nouveau;
    } // Les lignes 20 jusque 30 : je realise ces tests pour des raisons d'optimisation, pas besoin de faire des boucles inutiles dans le while. 
    else{
        // On cree un pointeur sur notre liste
        item* t = list;
        // On cree un futur pointeur qui reprendra un bloc de notre liste
        item* tprec = NULL;
        // Tant que nous ne sommes pas arrive a la fin de notre liste et que nous sommes en dessous de notre index, nous devons parcourir la liste
        while(t->next != NULL && i < index){
            // On incremente notre variable compteur afin de  comparer par rapport a l'index et donc pouvoir s'arreter avant
            ++i;
            // Notre nouveau bloc aura comme suivant le suivant du bloc en cours : ainsi, quand on sera a l'index-1, nouveau->suivant != list[index]
            nouveau->next = t->next;
            // On doit recuperer dans une variable  le bloc en cours. Ainsi, quand on aura atteint le bon index, cette variable aura l'index-1 et donc le suivant devra etre notre nouveau bloc
            tprec = t;
            // On passe au bloc suivant
            t = t->next;
        }
        // Si le bloc en cours ne possede pas de suivant, c'est que nous sommes a la fin de la liste. Des lors, notre nouveau bloc est a la fin. En faisant ca, meme si on demande de mettre a un index qui est superieur a la taille de notre liste, il n'y aura pas de bug
        if(t->next == NULL && i < index){
            nouveau->next = NULL;
            t->next = nouveau;
        }
        else{
            // Nous reprenons notre bloc[index-1], et nous lui mettons comme suivant notre nouveau bloc
            tprec->next = nouveau;
        }
        return list;
    }
}