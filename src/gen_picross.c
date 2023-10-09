#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "gen_picross.h"

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



void free_picross(picross_grid* p){
    free_int_int(p->grid,p->size);
    free(p);
}

void free_numbers(picross_numbers* n){
    free_int_int(n->col,n->size);
    free_int_int(n->lig,n->size);
    free(n);
}