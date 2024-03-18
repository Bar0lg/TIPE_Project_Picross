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

void print_estimation(line_est_t* e){
    printf("NB_BLOCKS:%d\n",e->nb_blocks);
    for (int i = 0;i<e->nb_blocks;i++){
        printf("(%d,%d) ",e->est[i].x,e->est[i].y);
    }
    printf("\n");
}

void free_estimation(line_est_t* e){
    free(e->est);
    free(e);
}