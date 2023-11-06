#ifndef SOLVER_H
#define SOLVER_H

#include "picross.h"
#include "valideurs.h"

//Verifie si une grille complete est valide O(n^2)
bool est_solution_valide_total(picross_grid* grid,valideur_det* valideur);

//Verifie une seule ligne et colonne O(n)
bool verif_ligne_col(picross_grid* grid,valideur_partiel* valideur,int ligne,int col);

//Boucle de reccurance du brute-force O(2^(n^2))
bool brute_force_rec(picross_grid* grid,valideur_det* valideur,int i,int j);

//Brute-force
picross_grid* brute_force(valideur_det* valideur);
#endif