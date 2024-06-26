#ifndef PICROSS_H
#define PICROSS_H

#include "automates.h"
#include "listes.h"


struct picross_grid_s {int size; int** grid;};
typedef struct picross_grid_s picross_grid;

struct picross_numbers_s {liste* lig;liste* col;int size;};
typedef struct picross_numbers_s picross_numbers;

//Genere une grille vide
picross_grid* gen_empty_grid(int size);

//Genere une grille inconnue
picross_grid* gen_unk_grid(int size);

//Genere une grille aleatoire avec chance% que chaque case soit noire
picross_grid* gen_random_grid(int size, int chance);

//Fait transposer la grille tel une matrice 
picross_grid* tourner_grille(picross_grid* grid);

//Récupere la colonne de la grille
int* get_col(picross_grid* g, int size,int col_n);

//Affiche une grille de picross
void print_picc(picross_grid* p);

//Affiche les nombres des lignes et colonnes
void print_nums(picross_numbers* nums);

//prend une grille et en tire ses nombres
picross_numbers* gen_numbers_from_grid(picross_grid* grid);

//Prend un tableau et change la colonne col_n de la grille en ce tableau
void apply_tab_to_col(picross_grid* g,int* col,int col_n);

//Libere une grille
void free_picross(picross_grid* p);

//Libere les nombres
void free_numbers(picross_numbers* nums);


#endif