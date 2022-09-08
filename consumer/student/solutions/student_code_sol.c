#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student_code_sol.h"


int AddStuff_sol(consumer_t* client, char* name, unsigned int price){
    if (!client || !name) return -1;
    if (client->total + price > client->budget) return -2;
    for(int j = 0; j < client->size; j++){
        if(strcmp(client->dontLike[j], name) == 0 ){
            return -3;
        }
    }
    if (client->total == 0 && client->bagSize != 0){
        client->bag = malloc(sizeof(stuff_t *)*client->bagSize);
        if (client->bag == NULL) return -4;
        for (int i = 0; i < client->bagSize; i++){
            client->bag[i] = NULL;
        }
    }
    for(int i = 0 ; i < client->bagSize ; i++){
        if(client->bag[i] == NULL){
            stuff_t * NewStuff = ( stuff_t *) malloc(sizeof( stuff_t));
            if (NewStuff == NULL) return -4;
            NewStuff->name = name;
            NewStuff->price = price;
            free(client->bag[i]);
            client->bag[i] = NewStuff;
            client->total += price;
            return 0;
        }
    }
    return -5;
}
