#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "gen_picross.h"
#include "automates.h"

picross_grid* gen_empty_grid(int size){
    int** res_grid = (int**)malloc(sizeof(int*)*size);
    for (int i=0;i<size;i++){
        int* res_grid_bis = (int*)calloc(size,sizeof(int));
        res_grid[i] = res_grid_bis;
    }
    picross_grid* res = (picross_grid*)malloc(sizeof(picross_grid));
    res->size = size;
    res->grid = res_grid;
    return res;
}

picross_grid* gen_random_grid(int size, int chance){
    int** res = (int**)malloc(sizeof(int*)*size);
    for (int i = 0;i<size;i++){
        int* tab_bis = (int*)malloc(sizeof(int)*size);
        for (int j=0;j<size;j++){
            if ((rand() % 100) > chance){
                tab_bis[j] = 0;
            }else{
                tab_bis[j] = 1;
            }
        }
        res[i] = tab_bis;
    }
    picross_grid* res_piccross = (picross_grid*)malloc(sizeof(picross_grid));
    res_piccross->size = size;
    res_piccross->grid = res;
    return res_piccross;
}

picross_numbers* gen_numbers_from_grid(picross_grid* grid){
    int size = grid->size;
    //Lines
    int** lines_tab = (int**)malloc(sizeof(int*)*size);
    int count = 0;
    int index_tab = 0;
    for (int i = 0;i<size;i++){
        int* line_tmp = (int*)calloc(ceil((float)size / 2), sizeof(int));
        for (int j=0;j<size;j++){
            if (grid->grid[i][j] == 1){
                count++;
            }else{
                if (count != 0){
                    line_tmp[index_tab] = count;
                    count = 0;
                    index_tab++;
                }   
            }
        }
        if (count != 0){
            line_tmp[index_tab] = count;
        }   
        lines_tab[i] = line_tmp;
        count = 0;
        index_tab = 0;
    }
    //Cols
    int** cols_tab = (int**)malloc(sizeof(int*)*size);
    count = 0;
    index_tab = 0;
    for (int i = 0;i<size;i++){
        int* col_tmp = (int*)calloc(ceil((float)size / 2), sizeof(int));
        for (int j=0;j<size;j++){
            if (grid->grid[j][i] == 1){
                count++;
            }else{
                if (count != 0){
                col_tmp[index_tab] = count;
                count = 0;
                index_tab++;
                }
            }
        }
        if (count != 0){
            col_tmp[index_tab] = count;
            count = 0;
        }
        cols_tab[i] = col_tmp;
        count = 0;
        index_tab = 0;
    }
    picross_numbers* res = (picross_numbers*)malloc(sizeof(picross_numbers));
    res->size = size;
    res->lig = lines_tab;
    res->col = cols_tab;
    return res;
}

automate_cd* auto_de_zeros(void){
    automate_cd* res = init_automate(2,2);
    res->depart = 0;
    res->finaux[0] = true;
    res->puit = 1;
    add_connection(res,0,0,0);
    return res;
}

automate_cd* generer_automate_ligne(int* ligne,int size_picc){
    if (ligne[0] == 0){
        return auto_de_zeros();
    }
    int size_tab = max_size_line(size_picc);
    int nb_of_states = 1; //L'etat vide
    int index = 0;
    while (index < size_tab  && ligne[index] != 0 ){
        nb_of_states += 1 + ligne[index];
        index++;
    }
    automate_cd* res = init_automate(2, nb_of_states);

    int state_index =0;
    for (int i=0;i<size_tab;i++){
        if (ligne[i] == 0){
            break;
        }
        //Connect to itself
        add_connection(res, state_index,0,state_index);
        //Fait une chaine de 1
        for (int j = 0;j<ligne[i];j++){
            add_connection(res, state_index,1,state_index +1);
            state_index++;
        }
        //On DOIT finir par un zero si on est pas le dernier nombre
        if (i != size_tab-1 && ligne[i+1] != 0){
            add_connection(res, state_index, 0, state_index+1);
            state_index++;
        }
        //Sinon on boucle en 0 sur le dernier
        else{
            add_connection(res,state_index,0,state_index);
            state_index++;
        }
    }
    res->depart = 0;
    res->finaux[res->nb_etats -2] = true;
    res->puit = res->nb_etats -1;

    return res;

}

valideur_total* gen_valideur_total(picross_numbers* nums){
    automate_cd** ligne = (automate_cd**)malloc(sizeof(automate_cd*)*nums->size);
    automate_cd** cols = (automate_cd**)malloc(sizeof(automate_cd*)*nums->size);
    for(int i=0;i<nums->size;i++){
        ligne[i] = generer_automate_ligne(nums->lig[i],nums->size);
        cols[i] = generer_automate_ligne(nums->col[i],nums->size);
    }
    valideur_total* res = (valideur_total*)malloc(sizeof(valideur_total));
    res->size = nums->size;
    res->ligne = ligne;
    res->col = cols;
    return res;
}


void free_picross(picross_grid* p){
    free_int_int(p->grid,p->size);
    free(p);
}

void free_numbers(picross_numbers* n){
    free_int_int(n->col,n->size);
    free_int_int(n->lig,n->size);
    free(n);
}

void free_valideur_total(valideur_total* A){
    for (int i = 0;i<A->size;i++){
        free_auto(A->ligne[i]);
        free_auto(A->col[i]);
    }
    free(A->ligne);
    free(A->col);
    free(A);
}