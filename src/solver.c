#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "automates.h"
#include "picross.h"
#include "utils.h"
#include "valideurs.h"

bool est_solution_valide_total(picross_grid* grid,valideur_det* valideur){
    bool res = true;
    picross_grid* grid_turned = tourner_grille(grid);
    for (int i=0;i<grid->size;i++){
        res = res && reconnu_afd(valideur->ligne[i], grid->grid[i],grid->size);
        res = res && reconnu_afd(valideur->col[i], grid_turned->grid[i],grid->size);
    }
    free_picross(grid_turned);
    return res;
}

bool verif_ligne_col(picross_grid* grid,valideur_det* valideur,int ligne,int col){
    int* col_arr = get_col(grid, grid->size, col);
    bool res = 
        reconnu_afd(valideur->ligne[ligne],grid->grid[ligne],grid->size) 
        &&
        reconnu_afd(valideur->col[col], col_arr, grid->size);
    free(col_arr);
    return res;

    
}

bool verif_ligne_col_ndet(picross_grid* grid,valideur_ndet* valideur,int ligne,int col){
    int* col_arr = (int*)malloc(sizeof(int)*grid->size);
    for (int i = 0; i < grid->size; i++){
        col_arr[i] = grid->grid[i][col];
    }
    bool res = 
        reconnu_afnd(valideur->ligne[ligne],grid->grid[ligne],grid->size) 
        &&
        reconnu_afnd(valideur->col[col], col_arr, grid->size);
    free(col_arr);
    return res;

    
}

bool bruteforce(picross_grid* grid,valideur_det* valideur,int i,int j){
    if (i == grid->size-1 && j==grid->size-1){
        //print_picc(grid);
        if (est_solution_valide_total(grid,valideur)){
            return true;
        }
        grid->grid[i][j] = 1;
        if (est_solution_valide_total(grid,valideur)){
            return true;
        }
        grid->grid[i][j] = 0;
        return false;
    }
    int j_next = (j+1) % grid->size;
    int i_next;
    if (j == grid->size -1){
        i_next = i+1;
    }
    else{
        i_next = i;
    }
    
    if (bruteforce(grid,valideur, i_next, j_next)){
        return true;
    }
    grid->grid[i][j] = 1;
    if (bruteforce(grid,valideur, i_next, j_next)){
        return true;
    }
    grid->grid[i][j] = 0;
    return false;
}


bool backtracking(picross_grid* grid, valideur_det* valideur, int i, int j){
    if (i == grid->size -1 && j == grid->size-1){
        if (grid->grid[i][j] != 2){
            return true;
        }
        grid->grid[i][j] = 0;
        if (verif_ligne_col(grid,valideur,i,j)){
            return true;
        }
        grid->grid[i][j] = 1;
        if (verif_ligne_col(grid,valideur,i,j)){
            return true;
        }
        grid->grid[i][j] = 2;
        return false;
    }
    int j_next = (j+1) % grid->size;
    int i_next;
    if (j == grid->size -1){
        i_next = i+1;
    }
    else{
        i_next = i;
    }
    if (grid->grid[i][j] != 2){
        return backtracking(grid,valideur,i_next,j_next);
    }
    grid->grid[i][j] = 0;
    if (verif_ligne_col(grid,valideur,i,j)){
        if (backtracking(grid,valideur,i_next,j_next)){
            return true;
        }
    }
    grid->grid[i][j] = 1;
    if (verif_ligne_col(grid,valideur,i,j)){
        if (backtracking(grid,valideur,i_next,j_next)){
            return true;
        }
    }
    grid->grid[i][j] = 2;
    return false;

}

bool backtracking_ndet(picross_grid* grid, valideur_ndet* valideur, int i, int j){
    if (i == grid->size -1 && j == grid->size-1){
        if (grid->grid[i][j] != 2){
            return true;
        }
        grid->grid[i][j] = 0;
        if (verif_ligne_col_ndet(grid,valideur,i,j)){
            return true;
        }
        grid->grid[i][j] = 1;
        if (verif_ligne_col_ndet(grid,valideur,i,j)){
            return true;
        }
        grid->grid[i][j] = 2;
        return false;
    }
    int j_next = (j+1) % grid->size;
    int i_next;
    if (j == grid->size -1){
        i_next = i+1;
    }
    else{
        i_next = i;
    }
    //assert(i_next < grid->size);
    if (grid->grid[i][j] != 2){
        return backtracking_ndet(grid,valideur,i_next,j_next);
    }
    grid->grid[i][j] = 0;
    if (verif_ligne_col_ndet(grid,valideur,i,j)){
        if (backtracking_ndet(grid,valideur,i_next,j_next)){
            return true;
        }
    }
    //printf("Zero raté:%d %d\n",i,j);
    grid->grid[i][j] = 1;
    if (verif_ligne_col_ndet(grid,valideur,i,j)){
        if (backtracking_ndet(grid,valideur,i_next,j_next)){
            return true;
        }
    }
    //printf("Tout raté:%d %d\n",i,j);
    grid->grid[i][j] = 2;
    return false;

}