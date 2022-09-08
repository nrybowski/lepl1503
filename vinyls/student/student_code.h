#include <stdlib.h>

typedef struct{
  char* name;
  char* genre;
  int price;
  int stock;
} Artist;

typedef struct{
  char** genres;
  int genre_number;
  int budget;
} Client;

typedef struct{
  Artist* rec_list;
  int rec_number;
} Recommendations;


/* 
 *@pre liste d'artistes : struct Artist* artists!=NULL, length = a_length!=0
 *@pre client : struct Client client
 *@pre a_length
 *@post retourne une structure Recommendations contenant la liste d'artistes conforme au client
 */
Recommendations possible_vinyls(Artist* artists, Client client, int a_length);