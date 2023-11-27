#ifndef DICTS_H
#define DICTS_H

#include "listes.h"
#include <stdbool.h>

typedef struct
{   duo_liste* table;
    int length;
} dict ;


dict* create_dict(int n);

duo_liste cons(duo head,duo_liste tail);

void free_duo_liste(duo_liste l);

void add_dict(dict* dico, int key,int val);

bool is_in_dico(dict* dico, int key);

int find_dico(dict* dico, int key);

void remove_dico(dict* dico, int key);

liste all_keys(dict* dico);

void free_dico(dict* dico);

void print_dico(dict* dico);
#endif