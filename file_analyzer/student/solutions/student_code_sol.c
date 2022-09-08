#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

struct Output * fileAnalyzer_sol(struct FilesStream *FS){

  // Nombre maximum d'extension
  int numberOfOutputs = 10;

  struct Output *outputArray = malloc(numberOfOutputs * sizeof(struct Output));
  for (size_t i = 0; i < numberOfOutputs; i++){
    struct Output *extensionFound = outputArray + i;
    extensionFound->extension = NULL;
    extensionFound->number = 0;
    extensionFound->totalSize = 0;
  }

  struct FilesStream *explorer = FS;

  // On explore
  while (explorer != NULL){

    // On vérifie si l'extension "explorer->extension" a déja été rencontrée
    for (size_t i = 0; i < numberOfOutputs; i++){
      struct Output *extensionFound = outputArray + i;

      if(extensionFound->extension == NULL){
        /* New extension */

        extensionFound->extension = explorer->extension;
        extensionFound->number = 1;
        extensionFound->totalSize = explorer->size;

        break;
      }

      if (strcmp(extensionFound->extension, explorer->extension) == 0){
        /* Existing extension */

        extensionFound->number++; // +1
        extensionFound->totalSize += explorer->size; // +explorer->size

        break;
      }
    }

    explorer = explorer->next;
  }

  return outputArray;

}
