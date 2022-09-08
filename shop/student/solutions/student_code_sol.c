#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

int add_product_sol(struct shop *my_shop, char *product_name, double unit_price, int quantity) {
    // CAS 1 : La liste des produits n'existe pas encore (elle est vide), il faut la créer et on y ajoute le produit en question 
    if (my_shop->first_product == NULL) {
        struct product *new_product = (struct product *)malloc(sizeof(struct product));
        if (new_product == NULL) { return -1; }
        new_product->next = NULL ;
        new_product->unit_price = unit_price ;
        new_product->name = product_name ;
        new_product->quantity = quantity ;

        my_shop->first_product = new_product ;
        my_shop->count_products = 1 ;
        my_shop->stock_value = (quantity * unit_price) ;

        return my_shop->count_products;
    }
    else { // La liste des produits existe déjà (elle n'est pas vide)
        struct product *previous_product = NULL ;
        struct product *next_product = my_shop->first_product ;

        // CAS 2 : Le produit doit se trouver en toute première position
        if (strcmp(product_name, next_product->name) < 0) {
            struct product *new_product = (struct product *)malloc(sizeof(struct product));
            if (new_product == NULL) { return -1; }
            new_product->next = next_product ;
            new_product->unit_price = unit_price ;
            new_product->name = product_name ;
            new_product->quantity = quantity ;

            my_shop->first_product = new_product ;
            my_shop->count_products += 1 ;
            my_shop->stock_value += (quantity * unit_price) ;

            return my_shop->count_products;
        }

        else {
            while ( (next_product != NULL) && (strcmp(product_name, next_product->name) >= 0) ) {
                // CAS 3 : Le produit existe déjà. On met donc ses paramètres à jour
                if (strcmp(product_name, next_product->name) == 0) {
                    next_product->quantity += quantity ;
                    my_shop->stock_value += (quantity * next_product->unit_price);
                    return my_shop->count_products;
                }
                previous_product = next_product ;
                next_product = next_product->next ;
            }

            // CAS 4 : Le produit doit se trouver entre previous_product et next_product pour respecter l'ordre alphabétique
            // CAS 5 : Le produit doit se trouver en toute dernière position
            struct product *new_product = (struct product *)malloc(sizeof(struct product));
            if (new_product == NULL) { return -1; }
            previous_product->next = new_product ;

            new_product->next = next_product ;
            new_product->unit_price = unit_price ;
            new_product->name = product_name ;
            new_product->quantity = quantity ;

            my_shop->count_products += 1 ;
            my_shop->stock_value += (quantity * unit_price) ;

            return my_shop->count_products;
        }
    }
}





int buy_product_sol(struct shop *my_shop, char *product_name, int amount) {
    struct product *product = my_shop->first_product ;
    while (product != NULL) {
        // On est arrivé au produit en question
        if (strcmp(product_name, product->name) == 0) {
            // Le produit est présent en quantité insuffisante
            if (product->quantity < amount) {
                return 1 ;
            }
            else {
                // Le produit peut être acheté
                product->quantity -= amount;
                double difference = amount * product->unit_price;
                my_shop->income += difference;
                my_shop->stock_value -= difference;
                return 0 ;
            }
        }
        // Le produit devait se trouver avant le produit actuel dans l'ordre alphabétique
        // Il ne se trouve donc pas dans la liste
        else if (strcmp(product_name, product->name) < 0) {
            return 2 ;
        }
        else {
            product = product->next;
        }
    }
    // On est arrivé au bout de la liste
    return 2 ;
}
