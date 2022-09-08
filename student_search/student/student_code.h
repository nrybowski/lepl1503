//structures données dans l'énoncé
struct element {
    struct element* left;
    struct element* right;
    int noma;
    char* name;
    double grade;
};

struct obtree{
    struct element* head;
};

struct linked_node{
    struct linked_node* next;
    int noma;
    char* name;
    double grade;
};

struct linked_list{
    struct linked_node* first;
    int nbr_of_element;
};



struct obtree* insert(struct obtree *tree, int noma, char* name, double grade);


/*
 *@pre n!=NULL
 *@post retourne la liste chainée n contenant tous les éléments présent dans l'arbre passé en argument, dont les étudiants sont triés par
        ordre croissant suivant leur noma
 */

void convert(struct element * head, struct linked_list * n);
