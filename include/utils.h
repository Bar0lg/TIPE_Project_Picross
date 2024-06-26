#ifndef UTILS_H
#define UTILS_H

#include "listes.h"
#include <stdbool.h>

//Permet de creer les flags dans main.c
#define Fl(n) (int)1 << n


//Libere un tableau de tableau d'entier
void free_int_int(int** t,int n);


//Affiche un tableau d'entier
void print_tab(int* t, int size);

//Affiche un tableau de booleen
void print_bool_tab(bool* t, int size);

//Converti un tableau de bool en un entier unique a ce tableau
int binary_from_bool_int(bool* t,int size);

//Fait l'inverse
bool* bool_arr_from_int(int num,int size);

//Envoie 1 quand envoye 0 et 0 quand envoiye 1
int inverse_valeur(int i);

//Operation binaire AND sur un array
bool and_bool_arr(bool* a1,bool* a2,int size);

bool equal_bool_arr(bool* a1,bool* a2,int size);

void copy_tab(int* dest,int* src,int size);
#endif