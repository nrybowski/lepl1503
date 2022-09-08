#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



struct shop {
    int count_products;             // Le nombre de produits différents que propose le magasin
    struct product *first_product;  // Un pointeur vers le premier produit
    double income;                  // Les revenus du magasin
    double stock_value;             // La valeur du stock du magasin
} ;



struct product {
    char *name;             // Le nom du produit
    struct product *next;   // Un pointeur vers le produit suivant
    double unit_price;      // Le prix unitaire du produit
    int quantity;           // La quantité de ce produit qu'il reste en stock
} ;



/**
 * 
 * @pre my_shop != NULL
 * @post Le produit a été ajouté dans la liste en respectant l'ordre alphabétique.
 * Si le produit y figurait déjà, on modifie uniquement la quantité présente dans le stock de ce produit.
 * Le nombre de produits différents présents dans le stock est modifié 
 * uniquement si le produit ajouté n'y figurait pas encore.
 * La valeur du stock est toujours modifiée lorsqu'un produit est ajouté.
 * 
 * @param my_shop: Pointeur vers la structure chaînée du magasin
 * @param product_name: Le nom du produit à ajouter dans la liste
 * @param unit_price: Le prix (> 0) unitaire du produit
 * @param quantity: La quantité (> 0) de ce produit ajoutée au stock
 *
 * @return: 
 * - Retourne le nombre de produits différents présents dans le stock du magasin
 * - Retourne -1 s'il y a eu une erreur
 * 
 */
int add_product(struct shop *my_shop, char *product_name, double unit_price, int quantity);



/**
 * 
 * @pre my_shop != NULL
 * @post La quantité du produit se trouvant dans le stock est modifiée ssi 
 * le produit se trouve dans la liste ET qu'il est présent en quantité suffisante 
 * La valeur du stock et les revenus du magasin sont modifiés uniquement si l'achat a réussi.
 * Le nombre de produits différents présents dans le stock n'est jamais modifié 
 * car un produit restera dans le stock même s'il n'y a plus d'exemplaires de ce produit.
 * 
 * @param my_shop: Pointeur vers la structure chaînée du magasin
 * @param product_name: Le nom du produit à acheter
 * @param amount: La quantité achetée (> 0) de ce produit
 * 
 * @return:
 * - Si l'achat a réussi, la fonction retourne 0.
 * - Si le produit se trouve dans la liste mais en quantité insuffisante, la fonction retourne 1
 * - Si le produit ne se trouve pas dans la liste, la fonction retourne 2
 *
 */
int buy_product(struct shop *my_shop, char *product_name, int amount);
