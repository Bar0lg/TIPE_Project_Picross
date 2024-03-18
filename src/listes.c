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
        printf("NULL");
    }
    while (liste_to_print != NULL){
        printf("%d ",liste_to_print->val);
        liste_to_print = liste_to_print->suivant;
    }
    printf("]");
}

duo_liste cons(duo head,duo_liste tail){
    duo_liste res = (duo_liste)malloc(sizeof(maillon_duo));
    res->val = head;
    res->suivant = tail;
    return res;
}

void free_duo_liste(duo_liste l){
    if (l != NULL){
        free_duo_liste(l->suivant);
        free(l);
    }
}

void print_duo(duo_liste d){
    duo_liste d_cpy = d;
    while (d_cpy){
        printf("{%d %d} ",d_cpy->val.x,d_cpy->val.y);
        d_cpy = d_cpy->suivant;
    }
    return;

}

int len_liste(liste l){
    int res =0;
    liste l_c = l;
    while (l_c != NULL){
        res++;
        l_c = l_c->suivant;
    }
    return res;
}

int* list_to_tab(liste l){
    int n = len_liste(l);
    int* res = (int*)malloc(sizeof(int)*n);
    liste l_c = l;
    for (int i = 0;i<n;i++){
        res[i] = l_c->val;
        l_c =  l_c->suivant;
    }
    return res;
}