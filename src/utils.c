#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "gen_picross.h"
#include "automates.h"

void free_int_int(int** t,int n){
    for(int i =0;i<n;i++){
        free(t[i]);
    }
    free(t);
}

void print_picc(picross_grid* p){
    printf("\n\n");
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
}

void print_tab(int* t, int size){
    printf("[");
    for (int i = 0;i<size;i++){
        printf("%d ",t[i]);
    }
    printf("]");
}

void print_bool_tab(bool* t, int size){
    printf("[");
    for (int i = 0;i<size;i++){
        if (t[i]){
            printf("true ");
        }else{
            printf("false ");
        }
    }
    printf("]");

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

int max_size_line(int size_picc){
    return ceil((float)size_picc / 2);
}

void print_auto(automate_cd* A){
    printf("\n");
    printf("Nb delta: %d\n",A->nb_lettres);
    printf("Nb etats: %d\n",A->nb_etats);
    printf("Etat depart: %d\n",A->depart);
    printf("Etat finaux:");print_bool_tab(A->finaux,A->nb_etats);printf("\n");
    for (int i=0;i<A->nb_etats;i++){
        print_tab(A->delta[i],A->nb_lettres);
    }
    printf("\n");
}