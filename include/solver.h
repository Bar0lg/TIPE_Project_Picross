#ifndef SOLVER_H
#define SOLVER_H

#include "picross.h"
#include "valideurs.h"

//Verifie si une grille complete est valide O(n^2)
bool est_solution_valide_total(picross_grid* grid,valideur_det* valideur);

//Verifie une seule ligne et colonne O(n)
bool verif_ligne_col(picross_grid* grid,valideur_det* valideur,int ligne,int col);

bool verif_ligne_col_ndet(picross_grid* grid,valideur_ndet* valideur,int ligne,int col);

//Brute-force O(2^(n^2))
bool bruteforce(picross_grid* grid,valideur_det* valideur,int i,int j);


//Backtracking
bool backtracking(picross_grid* grid,valideur_det* valideur,int i,int j);

bool backtracking_ndet(picross_grid* grid, valideur_ndet* valideur, int i, int j);
#endif