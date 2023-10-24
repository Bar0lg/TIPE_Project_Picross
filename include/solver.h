#ifndef SOLVER_H
#define SOLVER_H

#include "gen_picross.h"

//Verifie si une grille complete est valide
bool est_solution_valide_total(picross_grid* grid,valideur_total* valideur);

//Boucle de reccurance du brute-force
bool brute_force_rec(picross_grid* grid,valideur_total* valideur,int i,int j);

//Brute-force
picross_grid* brute_force(valideur_total* valideur);
#endif