#include <stdlib.h>
#include <stdio.h>


#include "listes.h"

void free_liste(liste l){
    if (l != NULL){
        free_liste(l->suivant);
        free(l);
    }
}

liste add_to_liste(int x,liste l){
    liste res = (liste)malloc(sizeof(maillon));
    res->val = x;
    res->suivant = l;
    return res;
}

void print_liste(liste l){
    printf("[");
    liste liste_to_print = l;
    if (l==NULL){
        printf("0");
    }
    while (liste_to_print != NULL){
        printf("%d ",liste_to_print->val);
        liste_to_print = liste_to_print->suivant;
    }
    printf("]");
}