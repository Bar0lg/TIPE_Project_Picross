#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gen_picross.h"
#include "utils.h"
#include "automates.h"
#include "listes.h"

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
    liste* res_ligne = (liste*)malloc(sizeof(liste)*size);
    for (int i =0;i<size;i++){
        liste res_ligne_bis = NULL;
        int size_chunk = 0;
        for (int j=0;j<size;j++){
            if (grid->grid[i][j] == 1){
                size_chunk++;
            }
            else{
                if (size_chunk != 0){
                    res_ligne_bis = add_to_liste(size_chunk,res_ligne_bis);
                    size_chunk = 0;
                }
            }
        }
        if (size_chunk != 0){
            res_ligne_bis = add_to_liste(size_chunk,res_ligne_bis);
            size_chunk = 0;
        }
        res_ligne[i] = res_ligne_bis;
    
    }
    //Cols
    liste* res_cols = (liste*)malloc(sizeof(liste)*size);
    for (int i =0;i<size;i++){
        liste res_cols_bis = NULL;
        int size_chunk = 0;
        for (int j=0;j<size;j++){
            if (grid->grid[j][i] == 1){
                size_chunk++;
            }
            else{
                if (size_chunk != 0){
                    res_cols_bis = add_to_liste(size_chunk,res_cols_bis);
                    size_chunk = 0;
                }
            }
        }
        if (size_chunk != 0){
            res_cols_bis = add_to_liste(size_chunk,res_cols_bis);
            size_chunk = 0;
        }
        res_cols[i] = res_cols_bis;
    
    }
    picross_numbers* res = (picross_numbers*)malloc(sizeof(picross_numbers));
    res->size = size;
    res->lig = res_ligne;
    res->col = res_cols;

}

picross_grid* tourner_grille(picross_grid* grid){
    int** res_grid = (int**)malloc(sizeof(int*)*grid->size);
    for (int i=0;i<grid->size;i++){
        int* res_grid_bis = (int*)malloc(sizeof(int)*grid->size);
        for (int j=0;j<grid->size;j++){
            res_grid_bis[j] = grid->grid[j][i];
        }
        res_grid[i] = res_grid_bis;
    }
    picross_grid* res = (picross_grid*)malloc(sizeof(picross_grid));
    res->size = grid->size;
    res->grid = res_grid;
    return res;

}

void print_picc(picross_grid* p){
    printf("\n\n");
    printf("--------------\n");
    for(int i=0;i<p->size;i++){
        for (int j=0;j<p->size;j++){
            if (p->grid[i][j] == 1){
                printf("#");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("--------------\n");
}

void print_nums(picross_numbers* nums){
    int size_small = ceil((float)nums->size/2);
    printf("\n");
    printf("Ligne:[");
    for (int i=0;i<nums->size;i++){
        print_tab(nums->lig[i],size_small);printf(" ");
    }
    printf("]\nCols:[");
    for (int i=0;i<nums->size;i++){
        print_tab(nums->col[i],size_small);printf(" ");
    }
    printf("]\n");
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

void free_numbers(picross_numbers* nums){
    for(int i=0;i<nums->size;i++){
        free_liste(nums->lig[i]);
        free_liste(nums->col[i]);

    }
    free(nums);
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