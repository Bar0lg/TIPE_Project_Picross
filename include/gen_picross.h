#ifndef GEN_PICROSS_H
#define GEN_PICROSS_H

#include "automates.h"
#include "listes.h"


struct picross_grid_s {int size; int** grid;};
typedef struct picross_grid_s picross_grid;

struct picross_numbers_s {liste* lig;liste* col;int size;};
typedef struct picross_numbers_s picross_numbers;

struct valideur_total_s {automate_d** ligne;automate_d** col;int size;};
typedef struct valideur_total_s valideur_total;

//Genere une grille vide
picross_grid* gen_empty_grid(int size);

//Genere une grille aleatoire avec chance% que chaque case soit noire
picross_grid* gen_random_grid(int size, int chance);

//Fait transposer la grille tel une matrice 
picross_grid* tourner_grille(picross_grid* grid);

//Affiche une grille de picross
void print_picc(picross_grid* p);

//Affiche les nombres des lignes et colonnes
void print_nums(picross_numbers* nums);

//prend une grille et en tire ses nombres
picross_numbers* gen_numbers_from_grid(picross_grid* grid);

//Automate qui reconnais une ligne vide
automate_d* auto_de_zeros(void);

//Genere un automate qui recconais la ligne donnee
automate_d* generer_automate_ligne(liste ligne);

//Genere tous les automates poutes tt lignes et colonnes
valideur_total* gen_valideur_total(picross_numbers* nums);

//Libere une grille
void free_picross(picross_grid* p);

//Libere les nombres
void free_numbers(picross_numbers* nums);

//Libere le valideur
void free_valideur_total(valideur_total* A);
#endif