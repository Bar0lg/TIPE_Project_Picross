#ifndef UTILS_H
#define UTILS_H

#include "gen_picross.h"
#include <stdbool.h>


//Implemantation basique d'une liste chainee
struct maillon {int val;struct maillon* suivant;};
typedef struct maillon maillon ;
typedef maillon* liste;


//Libere un tableau de tableau d'entier
void free_int_int(int** t,int n);

//Affiche une grille de picross
void print_picc(picross_grid* p);

//Affiche un tableau d'entier
void print_tab(int* t, int size);

//Affiche un tableau de booleen
void print_bool_tab(bool* t, int size);

//Affiche les nombres des lignes et colonnes
void print_nums(picross_numbers* nums);

int max_size_line(int size_picc);

//Affiche l'automate
void print_auto(automate_cd* A);

//Fait transposer la grille tel une matrice 
picross_grid* tourner_grille(picross_grid* grid);

//Envoie 1 quand envoye 0 et 0 quand envoiye 1
int inverse_valeur(int i);

//Libere une liste
void free_liste(liste l);

//Ajoute un element a la liste
liste add_to_liste(int x,liste l);
#endif