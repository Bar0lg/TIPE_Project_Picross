#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dicts.h"
#include "listes.h"

dict* create_dict(int n){
    dict* res = (dict*)malloc(sizeof(dict));
    duo_liste* table = (duo_liste*)malloc(sizeof(duo_liste)*n);
    for (int i=0;i<n;i++){
        table[i] = NULL; 
    }
    res->table = table;
    res->length = n;

    return res;
}




void add_dict(dict* dico, int key,int val){
    int array_index = key % dico->length;
    duo couple;
    couple.x = key;
    couple.y = val;
    dico->table[array_index] = cons(couple,dico->table[array_index]); 
}

bool is_in_dico(dict* dico, int key){
    int array_index = key % dico->length;
    duo_liste l = dico->table[array_index];
    while (l != NULL){
        if (l->val.x == key){
            return true;
        }
        l = l->suivant;
    }
    return false;
}

int find_dico(dict* dico, int key){
    int array_index = key % dico->length;
    duo_liste l = dico->table[array_index];
    while (l != NULL){
        if (l->val.x == key){
            return l->val.y;
        }
        l = l->suivant;
    }
    return -1;
}

void remove_dico(dict* dico, int key){
    int array_index = key % dico->length;
    duo_liste l = dico->table[array_index];
    duo_liste prev = l;
    while (l != NULL){
        if (l->val.x == key){
            prev->suivant = l->suivant;
            free(l);
        }
        prev = l;
        l = l->suivant;
    }
    return;
}

void replace_dico(dict* dico,int key,int val){
    if (is_in_dico(dico,key)){
        remove_dico(dico,key);
    }
    add_dict(dico,key,val);
}

liste all_keys(dict* dico){
    liste res = NULL;
    for (int i=0; i<dico->length;i++){
        if (dico->table[i] != NULL){
            res = add_to_liste(i,res);
        }
    }
    return res;
}

void free_dico(dict* dico){
    for (int i=0;i<dico->length;i++){
        free_duo_liste(dico->table[i]);
    }
    free(dico->table);
    free(dico);
}

void print_dico(dict* dico){
    for (int i=0; i<dico->length;i++){
        printf("%d:",i);
        print_duo_liste(dico->table[i]);
        printf("\n");
    }
}