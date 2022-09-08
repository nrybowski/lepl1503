#include <stdlib.h>

typedef struct file
{
    struct file ** files;// liste contenant tous les pointeurs vers les fichiers contenus dans le fichier (si celui-ci est un répertoire)
    int folder;    // true (=1) si c'est un répertoire, false (=0) sinon
    int n_files;    // le nombre de fichier contenus dans le fichier, si celui-ci est un répertoire
    void * content; // modélise le contenu du fichier (pas utilisé dans cet exercice)
} file_t;


int get_number_of_files (file_t * file);
