#ifndef DICTS_H
#define DICTS_H

#include "listes.h"
#include <stdbool.h>

typedef struct
{   duo_liste* table;
    int length;
} dict ;

//Cree un dictionaire
dict* create_dict(int n);

//Ajoute un element dans le dictionaire
void add_dict(dict* dico, int key,int val);

//Renvoie vrai si un element est dans le dictionaire
bool is_in_dico(dict* dico, int key);

//Trouve la valeur lié a la clé dans le dictionaire
int find_dico(dict* dico, int key);

//Retire un element dans le dictionaire 
void remove_dico(dict* dico, int key);

//Renvoie toutes le clées dans une liste
liste all_keys(dict* dico);

//Libere le dictionaire
void free_dico(dict* dico);

//Affiche le dictionaire
void print_dico(dict* dico);
#endif