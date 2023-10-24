#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "automates.h"
#include "picross.h"
#include "utils.h"

bool est_solution_valide_total(picross_grid* grid,valideur_total* valideur){
    bool res = true;
    picross_grid* grid_turned = tourner_grille(grid);
    for (int i=0;i<grid->size;i++){
        res = res && reconnu_afd(valideur->ligne[i], grid->grid[i],grid->size);
        res = res && reconnu_afd(valideur->col[i], grid_turned->grid[i],grid->size);
    }
    free_picross(grid_turned);
    return res;
}

bool brute_force_rec(picross_grid* grid,valideur_total* valideur,int i,int j){
    //printf("\n%d %d\n",i,j);
    if(i==grid->size-1 && j==grid->size-1){
        bool test = est_solution_valide_total(grid,valideur);
        if (!test){
            grid->grid[i][j] = inverse_valeur(grid->grid[i][j]);
            test = est_solution_valide_total(grid,valideur);
        }
        return test;
    }
    
    bool res = false;
    if (j == grid->size -1){
        res =brute_force_rec(grid,valideur,i+1,0);
        if (!res){
            grid->grid[i][j] = inverse_valeur(grid->grid[i][j]);
            res = brute_force_rec(grid,valideur,i+1,0);
        }
    }
    else{
        res =brute_force_rec(grid,valideur,i,j+1);
        if (!res){
            grid->grid[i][j] = inverse_valeur(grid->grid[i][j]);
            res = brute_force_rec(grid,valideur,i,j+1);
        }
    }
    //printf("\n%d\n",res);
    return res;
}

picross_grid* brute_force(valideur_total* valideur){
    picross_grid* res = gen_empty_grid(valideur->size);
    brute_force_rec(res,valideur, 0,0);
    return res;
}