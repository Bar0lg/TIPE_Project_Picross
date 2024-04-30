#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "picross.h"
#include "logicrules.h"
#include "listes.h"


line_est_t* estimate_line(liste numbers,int n){
    int nb_blocks = len_liste(numbers);
    int* numbers_tab = list_to_tab(numbers);
    duo* blocks = (duo*)malloc(sizeof(duo)*nb_blocks);
    for (int i = 0;i<nb_blocks;i++){
        if (i==0){
            blocks[i].x = 0;
        }
        else{
            int tmp = 0;
            for (int j=0;j<i;j++){
                tmp += numbers_tab[j] +1;
            }
            blocks[i].x = tmp;
        }

        if (i==nb_blocks-1){
            blocks[i].y = n-1;
        }
        else {
            int tmp = 0;
            for (int j=i+1;j<nb_blocks;j++){
                tmp += numbers_tab[j] +1;
            }
            blocks[i].y = (n-1) - tmp;
        }

    }
    line_est_t* res = (line_est_t*)malloc(sizeof(line_est_t));
    res->nb_blocks = nb_blocks;
    res->est = blocks;
    free(numbers_tab);
    return res;
}

estimation_t* full_estimation(picross_numbers* nums){
    int n = nums->size;
    estimation_t* res = (estimation_t*)malloc(sizeof(estimation_t));
    line_est_t** lines = (line_est_t**)malloc(sizeof(line_est_t*)*n);
    line_est_t** cols = (line_est_t**)malloc(sizeof(line_est_t*)*n);
    for (int i =0;i<n;i++){
        line_est_t* line = estimate_line(nums->lig[i],n);
        line_est_t* col = estimate_line(nums->col[i],n);
        lines[i] = line;
        cols[i] = col;
    }
    res->n = n;
    res->cols = cols;
    res->lines = lines;
    printf("TEST:%d\n",res->n);

    return res;
}



int rule1_1_line(int* line,int* nums,line_est_t* est,int size){
    int res = 0;
    int nb_blocks = est->nb_blocks;
    for (int j = 0;j<nb_blocks;j++){
        int start_of_block = est->est[j].x;
        int end_of_block = est->est[j].y;
        int u = (end_of_block - start_of_block + 1) - nums[j];
        for (int i = start_of_block; i<end_of_block+1;i++){
            if ( i >= 0 && line[i] != 2){
                continue;
            }
            if (start_of_block + u <= i && end_of_block - u >= i){
                res++;
                line[i] = 1;
            }
        }
    }
    return res;
}

int rule1_2_line(int* line,int size,line_est_t* est){
    int res =  0;
    int nb_blocks = est->nb_blocks;
    for (int i = 0;i<size;i++){
        if (line[i] != 2){
            continue;
        }
        if (i<est->est[0].x){
            res++;
            line[i] = 0;
        }
        if (i > est->est[nb_blocks-1].y){
            res++;
            line[i] = 0;
        }
        for (int j = 0;j<nb_blocks -1;j++){
            if (est->est[j].y<i && i< est->est[j+1].x){
                res++;
                line[i] = 0;
            }
        }
    }
    return res;
}

int rule2_2line(int* line,int size,line_est_t* est){
    int res = 0;
    int nb_blocks = est->nb_blocks;
    for (int j =0;j<nb_blocks;j++){
        if (est->est[j].x-1 >=0 && line[est->est[j].x-1] ==1){
            res++;
            est->est[j].x++;
        }
        if ((est->est[j].y+1 < size )&& (line[est->est[j].y+1] == 1)){
            res++;
            est->est[j].y--;
        }
    }
    return res;
}


int rule1_3line(int* line,int size,int* nums,line_est_t* est){
    int res = 0;
    int nb_blocks = est->nb_blocks;
    //TODO
}

int apply_rules(picross_grid* grille_a_completer,picross_numbers* nums,estimation_t* est,int k){
    int res = 0;
    for (int passage = 0;passage<k;passage++){
        for (int i = 0;i<nums->size;i++){
            //Lignes
            int* line = grille_a_completer->grid[i];
            int* num_line = list_to_tab(nums->lig[i]);
            int size = nums->size;
            line_est_t* est_line = est->lines[i];
            res += rule1_1_line(line, num_line, est_line,size);
            rule2_2line(line, size, est_line);
            res += rule1_2_line(line, size, est_line);
            //Cols
            int* col = get_col(grille_a_completer, size, i);
            int* num_col = list_to_tab(nums->col[i]);
            line_est_t* est_col = est->cols[i];
            res += rule1_1_line(col, num_col, est_col,size);
            rule2_2line(col, size, est_col);
            res += rule1_2_line(col, size, est_col);
            apply_tab_to_col(grille_a_completer, col, i);
            free(col);
            free(num_col);
            free(num_line);

        }
    }
    return res;
}


void print_estimation(line_est_t* e){
    printf("NB_BLOCKS:%d",e->nb_blocks);
    for (int i = 0;i<e->nb_blocks;i++){
        printf("(%d,%d) ",e->est[i].x,e->est[i].y);
    }
    printf("\n");
}

void print_full_estimation(estimation_t* e){
    printf("LINES:\n");
    for (int i = 0;i < e->n;i++){
        print_estimation(e->lines[i]);
    }
    printf("COLS:\n");
    for (int i = 0;i < e->n;i++){
        print_estimation(e->cols[i]);
    }
    printf("\n");
}

void free_estimation(line_est_t* e){
    free(e->est);
    free(e);
}
void free_full_estimation(estimation_t* e){
    for (int i = 0;i < e->n;i++){
        free_estimation(e->lines[i]);
    }
    for (int i = 0;i < e->n;i++){
        free_estimation(e->cols[i]);
    }
    free(e->cols);
    free(e->lines);
    free(e);
}