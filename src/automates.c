#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "automates.h"
#include "utils.h"

automate_cd* init_automate(int size_alpha,int size_etats){
    automate_cd* res = (automate_cd*)malloc(sizeof(automate_cd));
    int** delta_res = (int**)malloc(sizeof(int*)*size_etats);
    for (int i=0;i<size_etats;i++){
        int* delta_bis = (int*)malloc(sizeof(int)*size_alpha);
        for (int j=0;j<size_alpha;j++){
            delta_bis[j] = size_etats-1;
        }
        delta_res[i] = delta_bis;
    }
    bool* finaux_res = (bool*)calloc(sizeof(bool),size_etats);

    res->nb_etats = size_etats;
    res->nb_lettres = size_alpha;
    res->depart = 0;
    res->finaux = finaux_res;
    res->puit = size_etats -1;
    res->delta = delta_res;
    return res;
}

void free_auto(automate_cd* a){
    free_int_int(a->delta, a->nb_etats);
    free(a->finaux);
    free(a);
}


void add_connection(automate_cd* A,int etat_d,int lettre,int etat_f){
    A->delta[etat_d][lettre] = etat_f;
}

int delta_etoile_afd(automate_cd* A,int q,int* input,int size_input){
    int etat_curr = q;
    int i = 0;
    while (i < size_input && etat_curr != A->puit){
        etat_curr = A->delta[etat_curr][input[i]];
        i++;
    }
    return etat_curr;

}

bool reconnu_afd(automate_cd* A,int* input,int size_input){
    return A->finaux[delta_etoile_afd(A, A->depart,input,size_input)];
}