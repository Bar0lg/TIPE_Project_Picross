#ifndef SOLVER_H
#define SOLVER_H

#include "gen_picross.h"

bool est_solution_valide_total(picross_grid* grid,valideur_total* valideur);

bool brute_force_rec(picross_grid* grid,valideur_total* valideur,int i,int j);

picross_grid* brute_force(valideur_total* valideur);
#endif