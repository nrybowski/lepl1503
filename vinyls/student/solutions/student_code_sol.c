#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

Recommendations possible_vinyls_sol(Artist* artists, Client client, int a_length){
  int count_list = 0;
  Artist* result = malloc(a_length*sizeof(Artist));  // create a list of Artists to be returned

  for (size_t j = 0; j < a_length; j++) {  // iterate over the number of artists to consider
    for (size_t k = 0; k < client.genre_number; k++) {  // iterate over the genres the client likes
      if (artists[j].genre == client.genres[k] && artists[j].price <= client.budget && artists[j].stock != 0){  // check if the client likes the current genre and if he can afford it
        result[count_list] = artists[j];
        count_list++;
        break;  // not necessary
      }
    }
  }
  Recommendations rec = {result, count_list};  // create the output structure (count_list needed to manipulate the list, knowing its length, in the future)
  return rec;
}