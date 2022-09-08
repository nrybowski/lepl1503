/**
* Structure node
*
* @next: pointeur vers le noeud suivant de la liste, NULL si c'est le dernier node_t
* @value: valeur contenue dans le noeud
*/

typedef struct node{
  struct node* next;
  char value;
} node_t;

/* 
 *@pre n peut être égale à NULL
 *@pre size_mess est la taille du message non filtré.
 *@post retourne le message filtré, NULL si la liste est vide ou s'il y a une erreur
 */
char* filter(node_t* node, unsigned int size_mess);
