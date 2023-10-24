#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "gen_picross.h"
#include "automates.h"
#include "utils.h"

void free_int_int(int** t,int n){
    for(int i =0;i<n;i++){
        free(t[i]);
    }
    free(t);
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
    printf("Etat puit:%d\n",A->puit);
    printf("Etat depart: %d\n",A->depart);
    printf("Etat finaux:");print_bool_tab(A->finaux,A->nb_etats);printf("\n");
    for (int i=0;i<A->nb_etats;i++){
        print_tab(A->delta[i],A->nb_lettres);
    }
    printf("\n");
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

int inverse_valeur(int i){
    if (i==0){
        return 1;
    }else {
    return 0;
    }
}

void free_liste(liste l){
    if (l->suivant != NULL){
        free_liste(l->suivant);
    }
    free(l);
}

liste add_to_liste(int x,liste l){
    liste res = (liste)malloc(sizeof(maillon));
    res->val = x;
    res->suivant = l;
    return res;
}