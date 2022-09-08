typedef struct
{
    int price;
    char * name;
} stuff_t;

typedef struct
{
    stuff_t ** bag;
    char * name;
    unsigned int bagSize;
    unsigned int total;
    unsigned int budget;
    char** dontLike;
    unsigned int size;
} consumer_t;

/**
 *
 * Création d'un nouveau client avec un sac rempli d'objets "vide" de coût 0
 *
 * @param name: une chaine de caratcères représantant le nom du client
 * @param bagsize: la taille maximum du sac du client (bagsize >= 0)
 * @param budget: le budget maximum du client (budget >= 0)
 * @param lst: la liste des chose que le client n'aime pas
 * @param size: la taille de la liste lst (size >= 0)
 * @return: une structure représentant le client et toutes ses informations
 *
 */
 consumer_t * NewConsumer(char*, unsigned int, unsigned int, char**, unsigned int);



/**
 *
 * Ajout d'un objet dans le sac du client. Il n'y a pas d'ordre défini pour les objets.
 *
 * Si le prix total des objets du sac dépasse le budget du client, il ne pourra pas acheter l'objet et dans ce cas rien n'est ajouté au sac
 * Si le client n'aime pas l'objet proposé, il ne l'achètera pas et dans ce cas rien n'est ajouté au sac
 * S'il n'y a plus d'objet "vide" dans le sac (c'est-à-dire qu'il n'y a plus de place), le client ne pourra pas acheter l'objet proposé et dans ce cas rien n'est ajouté au sac
 *
 * @param client: le client en question
 * @param name: une chaine de caratcères représantant le nom de l'objet (le nom est différent de "vide")
 * @param price: le prix de l'objet (price >= 0)
 * @return: une structure représentant le client et toutes ses informations
 *
 */
int AddStuff(consumer_t*, char*, unsigned int);