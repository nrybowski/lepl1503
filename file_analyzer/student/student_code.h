#include <stdlib.h>
#include <string.h>

struct FilesStream {
   char *filename;
   char *extension;
   int  size;
   struct FilesStream *next;
};

struct Output {
   char *extension;
   int  number;
   int  totalSize;
};

/* 
 *@pre maximum de 10 extensions différentes
 *@post retourne l'adresse mémoire de la première structure "Output" suivie des autres structures "Output" contenant chacune:
    1) l'extension (char *)
    2) le nombre de fichiers ayant cette extension (int)
    3) la taille totale des fichiers ayant cette extension (int)
  /!\ l'ordre des structures "Output" DOIT être le même que l'ordre d'apparition des extensions dans la liste chainée
  /!\ il doit y avoir 10 structures "Output"
*/
struct Output * fileAnalyzer(struct FilesStream *);
