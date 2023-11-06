#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "picross.h"
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

picross_grid* gen_unk_grid(int size){
    int** res_grid = (int**)malloc(sizeof(int*)*size);
    for (int i=0;i<size;i++){
        int* res_grid_bis = (int*)malloc(size*sizeof(int));
        for (int j =0;j<size;j++){
            res_grid_bis[j] = 2;
        }
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
    liste* res_cols = (liste*)malloc(sizeof(liste)*size);
    for (int i =0;i<size;i++){
        liste res_ligne_bis = NULL;
        liste res_cols_bis = NULL;
        int size_chunk_ligne = 0;
        int size_chunk_col =0;
        for (int j=size-1;j>-1;j--){
            //Ligne
            if (grid->grid[i][j] == 1){
                size_chunk_ligne++;
            }
            else{
                if (size_chunk_ligne != 0){
                    res_ligne_bis = add_to_liste(size_chunk_ligne,res_ligne_bis);
                    size_chunk_ligne = 0;
                }
            }
            //Colonnes
            if (grid->grid[j][i] == 1){
                size_chunk_col++;
            }
            else{
                if (size_chunk_col != 0){
                    res_cols_bis = add_to_liste(size_chunk_col,res_cols_bis);
                    size_chunk_col = 0;
                }
            }
            
        }
        if (size_chunk_ligne != 0){
            res_ligne_bis = add_to_liste(size_chunk_ligne,res_ligne_bis);
            size_chunk_ligne = 0;
        }
        if (size_chunk_col != 0){
            res_cols_bis = add_to_liste(size_chunk_col,res_cols_bis);
            size_chunk_col = 0;
        }
        res_ligne[i] = res_ligne_bis;
        res_cols[i] = res_cols_bis;
    
    } 
    picross_numbers* res = (picross_numbers*)malloc(sizeof(picross_numbers));
    res->size = size;
    res->lig = res_ligne;
    res->col = res_cols;
    return res;

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
            }else if (p->grid[i][j] == 0){
                printf(" ");
            }else {
                printf("?");
            }
        }
        printf("\n");
    }
    printf("--------------\n");
}

void print_nums(picross_numbers* nums){
    printf("\n");
    printf("Ligne:[");
    for (int i=0;i<nums->size;i++){
        print_liste(nums->lig[i]);printf(" ");
    }
    printf("]\nCols:[");
    for (int i=0;i<nums->size;i++){
        print_liste(nums->col[i]);printf(" ");
    }
    printf("]\n");
}




/*bool cmp_grid(picross_grid* g1,picross_grid* g2){
    bool res = true;
}*/

void free_picross(picross_grid* p){
    free_int_int(p->grid,p->size);
    free(p);
}

void free_numbers(picross_numbers* nums){
    for(int i=0;i<nums->size;i++){
        free_liste(nums->lig[i]);
        free_liste(nums->col[i]);

    }
    free(nums->lig);
    free(nums->col);
    free(nums);
}
