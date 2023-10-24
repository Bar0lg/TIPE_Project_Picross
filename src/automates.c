#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "automates.h"
#include "listes.h"
#include "utils.h"

automate_d* init_automate(int size_alpha,int size_etats){
    automate_d* res = (automate_d*)malloc(sizeof(automate_d));
    int** delta_res = (int**)malloc(sizeof(int*)*size_etats);
    for (int i=0;i<size_etats;i++){
        int* delta_bis = (int*)malloc(sizeof(int)*size_alpha);
        for (int j=0;j<size_alpha;j++){
            delta_bis[j] = -1;
        }
        delta_res[i] = delta_bis;
    }
    bool* finaux_res = (bool*)calloc(sizeof(bool),size_etats);

    res->nb_etats = size_etats;
    res->nb_lettres = size_alpha;
    res->depart = 0;
    res->finaux = finaux_res;
    res->delta = delta_res;
    return res;
}

void free_auto(automate_d* a){
    free_int_int(a->delta, a->nb_etats);
    free(a->finaux);
    free(a);
}


void add_connection_d(automate_d* A,int etat_d,int lettre,int etat_f){
    A->delta[etat_d][lettre] = etat_f;
}

int delta_etoile_d(automate_d* A,int q,int* input,int size_input){
    int etat_curr = q;
    int i = 0;
    while (i < size_input && etat_curr != -1){
        etat_curr = A->delta[etat_curr][input[i]];
        i++;
    }
    return etat_curr;

}

bool reconnu_afd(automate_d* A,int* input,int size_input){
    int etat_final = delta_etoile_d(A, A->depart,input,size_input);
    if (etat_final == -1){
        return false;
    }else
    {
    return A->finaux[etat_final];
    }
}

void print_auto(automate_d* A){
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

automate_nd* init_automate_ncd(int size_alpha,int size_etats){
    automate_nd* res = (automate_nd*)malloc(sizeof(automate_nd));
    liste** delta_res = (liste**)malloc(sizeof(liste*)*size_etats);
    for (int i=0;i<size_etats;i++){
        liste* delta_res_bis = (liste*)calloc(size_alpha,sizeof(liste));
        delta_res[i] = delta_res_bis;
    }
    bool* finaux_res = (bool*)calloc(size_etats,sizeof(bool));
    bool* depart_res = (bool*)calloc(size_etats,sizeof(bool));
    res->nb_etats = size_etats;
    res->nb_lettres = size_alpha;
    res->depart = depart_res;
    res->finaux = finaux_res;
    res->delta = delta_res;
    return res;
    
}

void add_connection_nd(automate_nd *A, int etat_d, int lettre, int etat_f){
    A->delta[etat_d][lettre] = add_to_liste(etat_f, A->delta[etat_d][lettre]);
}

bool* delta_nd(automate_nd* A,bool* etats_depart,int lettre){
    bool* res = (bool*)calloc(A->nb_etats,sizeof(bool));
    for(int i=0;i<A->nb_etats;i++){
        if (etats_depart[i]){
            liste liste_to_parse = A->delta[i][lettre];
            while (liste_to_parse != NULL){
                res[liste_to_parse->val] = true;
                liste_to_parse = liste_to_parse->suivant;
            }
        }
    }
    return res;
}

bool* delta_etoile_nd(automate_nd* A,bool* etats_depart,int* input,int size_input){
    bool* etat_curr = (bool*)malloc(sizeof(bool)*A->nb_etats);
    memcpy(etat_curr,etats_depart, sizeof(bool)*A->nb_etats);
    for (int i=0;i<size_input;i++){
        bool* new_etat = delta_nd(A,etat_curr,input[i]);
        free(etat_curr);
        etat_curr = new_etat;
    }
    return etat_curr;
}

bool reconnu_afnd(automate_nd *A, int *input, int size_input){
    bool* res_tab = delta_etoile_nd(A,A->depart,input,size_input);
    bool res = false;
    for (int i=0;i<A->nb_etats;i++){
        res = res || (!A->finaux[i] || res_tab[i]);
    }
    return res;
}

void print_auto_nd(automate_nd* A){
    printf("\n");
    printf("Nb delta: %d\n",A->nb_lettres);
    printf("Nb etats: %d\n",A->nb_etats);

    printf("Etat depart:");print_bool_tab(A->depart,A->nb_etats);
    printf("Etat finaux:");print_bool_tab(A->finaux,A->nb_etats);printf("\n");
    for (int i=0;i<A->nb_etats;i++){
        for (int j=0;j<A->nb_lettres;j++){
            print_liste(A->delta[i][j]);
        }
    }
    printf("\n");
}