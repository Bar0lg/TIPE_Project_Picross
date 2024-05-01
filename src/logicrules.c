#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "picross.h"
#include "logicrules.h"
#include "listes.h"


line_est_t* estimate_line(liste numbers,int n){
    if (numbers == NULL){
        return NULL;
    }
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

    return res;
}

int fill_with_0(int* line,int size){
    int res = 0;
    if (line[0] == 0 && line[size-1] == 0){
        return 0;
    }
    for (int i = 0;i<size;i++){
        if (line[i] != 0){
            res++;
            line[i] = 0;
        }
    }
    return res;
}

int rule1_1_line(int* line,int* nums,line_est_t* est){
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
    int res = 0;
    int nb_blocks = est->nb_blocks;
    for (int i = 0;i<size;i++){
        if (line[i] != 2){
            continue;
        }
        //printf("%d <",i);print_tab(line,size);printf("\n");
        if (i < est->est[0].x){
            //res++;
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
    for (int j = 0;j<nb_blocks;j++){
        //Start_blocks
        int first = est->est[j].x;
        bool any_one = false;
        bool all_one = true;
        if (line[first] == 1 && (first != 0 && line[first-1] == 2)){
            for (int i = 0;i<nb_blocks;i++){
                if (i == j){
                    continue;
                }
                if (est->est[i].x <= first && est->est[i].y >= first){
                    any_one = true;
                    if (nums[i] == 1){
                        all_one = all_one && true;
                    }
                    else{
                        all_one = false;
                    }
                }
            }
            if (any_one && all_one){
                line[first-1] = 0; //Since we need overlap this can never be the first block so no error expected
                res++;
            }
        }
        int last = est->est[j].y;
        any_one = false;
        all_one = true;
        if (line[last] == 1 && (last != (size-1) && line[last+1] == 2)){
            for (int i = 0;i<nb_blocks;i++){
            if (i == j){
                continue;
            }
            if (est->est[i].x <= last && est->est[i].y >= last){
                any_one = true;
                if (nums[i] == 1){
                    all_one = all_one && true;
                }
                else{
                    all_one = false;
                }
            }
        }
        if (any_one && all_one){
            line[last+1] = 0; //Since we need overlap this can never be the last block so no error expected
            res++;
        }}
    }
    return res;
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
            if (est_line == NULL){
                //Cas ou la ligne est 0
                res += fill_with_0(line, size);
            }
            else{
                res += rule1_1_line(line, num_line, est_line);
                rule2_2line(line, size, est_line);
                res += rule1_2_line(line, size, est_line);
                res += rule1_3line(line, size, num_line, est_line);
            }
            //Cols
            int* col = get_col(grille_a_completer, size, i);
            int* num_col = list_to_tab(nums->col[i]);
            line_est_t* est_col = est->cols[i];
            if (est_col == NULL){
                res += fill_with_0(col, size);
            }
            else{
                res += rule1_1_line(col, num_col, est_col);
                rule2_2line(col, size, est_col);
                res += rule1_2_line(col, size, est_col);
                res += rule1_3line(col, size, num_col, est_col);
            }
            apply_tab_to_col(grille_a_completer, col, i);
            free(col);
            free(num_col);
            free(num_line);

        }
    }
    return res;
}


void print_estimation(line_est_t* e){
    if (e == NULL){
        printf("(NULL) ");
        return;
    }
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
    if (e == NULL){
        return;
    }
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