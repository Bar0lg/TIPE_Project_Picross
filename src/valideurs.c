#include <stdbool.h>
#include <stdlib.h>

#include "automates.h"
#include "picross.h"
#include "valideurs.h"
#include "listes.h"
#include "utils.h"

automate_d* auto_de_zeros(void){
    automate_d* res = init_automate(2,1);
    res->depart = 0;
    res->finaux[0] = true;
    add_connection_d(res,0,0,0);
    return res;
}

automate_nd* auto_nd_zeros(void){
    automate_nd* res = init_automate_nd(3,1);
    res->depart[0] = true;
    res->finaux[0] = true;
    add_connection_nd(res,0,0,0);
    add_connection_nd(res, 0, 2, 0);
    return res;
}

automate_d* generer_automate_ligne(liste ligne){
    if (ligne == NULL){
        return auto_de_zeros();
    }
    int nb_of_states = 1; //L'etat vide
    liste ligne_to_parse = ligne;
    while (ligne_to_parse != NULL){
        nb_of_states += 1 + ligne_to_parse->val;
        ligne_to_parse = ligne_to_parse->suivant;
    }
    automate_d* res = init_automate(2, nb_of_states);

    ligne_to_parse = ligne;
    int state_index =0;
    while (ligne_to_parse != NULL){
        //Connect to itself
        add_connection_d(res, state_index,0,state_index);
        //Fait une chaine de 1
        for (int j = 0;j<ligne_to_parse->val;j++){
            add_connection_d(res, state_index,1,state_index +1);
            state_index++;
        }
        //On DOIT finir par un zero si on est pas le dernier nombre
        if (ligne_to_parse->suivant != NULL){
            add_connection_d(res, state_index, 0, state_index+1);
            state_index++;
        }
        //Sinon on boucle en 0 sur le dernier
        else{
            add_connection_d(res,state_index,0,state_index);
            state_index++;
        }
        ligne_to_parse = ligne_to_parse->suivant;
    }
    res->depart = 0;
    res->finaux[res->nb_etats -2] = true;

    return res;

}

valideur_det* gen_valideur_total(picross_numbers* nums){
    automate_d** ligne = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    automate_d** cols = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    for(int i=0;i<nums->size;i++){
        ligne[i] = generer_automate_ligne(nums->lig[i]);
        cols[i] = generer_automate_ligne(nums->col[i]);
    }
    valideur_det* res = (valideur_det*)malloc(sizeof(valideur_det));
    res->size = nums->size;
    res->ligne = ligne;
    res->col = cols;
    return res;
}


automate_nd* generer_automate_partiel_ligne(liste ligne){
    if (ligne == NULL){
        return auto_nd_zeros();
    }
    int nb_of_states = 1; //L'etat vide
    liste ligne_to_parse = ligne;
    while (ligne_to_parse != NULL){
        nb_of_states += 1 + ligne_to_parse->val;
        ligne_to_parse = ligne_to_parse->suivant;
    }
    automate_nd* res = init_automate_nd(3, nb_of_states);
    //print_auto_nd(res);

    ligne_to_parse = ligne;
    int state_index =0;
    while (ligne_to_parse != NULL){
        //Connect to itself
        add_connection_nd(res, state_index,0,state_index);
        add_connection_nd(res, state_index,2,state_index);
        //Fait une chaine de 1
        for (int j = 0;j<ligne_to_parse->val;j++){
            add_connection_nd(res, state_index,1,state_index +1);
            add_connection_nd(res, state_index,2,state_index +1);
            state_index++;
        }
        //On DOIT finir par un zero si on est pas le dernier nombre
        if (ligne_to_parse->suivant != NULL){
            add_connection_nd(res, state_index, 0, state_index+1);
            add_connection_nd(res, state_index, 2, state_index+1);
            state_index++;
        }
        //Sinon on boucle en 0 sur le dernier
        else{
            add_connection_nd(res,state_index,0,state_index);
            add_connection_nd(res,state_index,2,state_index);
            state_index++;
        }
        ligne_to_parse = ligne_to_parse->suivant;
    }
    res->depart[0] = true;
    res->finaux[res->nb_etats -2] = true;

    return res;

}

valideur_ndet* gen_valideur_ndet(picross_numbers* nums){
    automate_nd** ligne = (automate_nd**)malloc(sizeof(automate_nd*)*nums->size);
    automate_nd** cols = (automate_nd**)malloc(sizeof(automate_nd*)*nums->size);
    for(int i=0;i<nums->size;i++){
        ligne[i] = generer_automate_partiel_ligne(nums->lig[i]);
        cols[i] = generer_automate_partiel_ligne(nums->col[i]);
    }
    valideur_ndet* res = (valideur_ndet*)malloc(sizeof(valideur_ndet));
    res->size = nums->size;
    res->ligne = ligne;
    res->col = cols;
    return res;
}

valideur_det* gen_valideur_partiel(picross_numbers* nums){
    automate_d** ligne = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    automate_d** cols = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    for(int i=0;i<nums->size;i++){
        automate_nd* tmp_ligne = generer_automate_partiel_ligne(nums->lig[i]);
        automate_nd* tmp_col = generer_automate_partiel_ligne(nums->col[i]);
        ligne[i] = determiniser(tmp_ligne);
        cols[i] = determiniser(tmp_col);
        free_auto_nd(tmp_ligne);
        free_auto_nd(tmp_col);
    }
    valideur_det* res = (valideur_det*)malloc(sizeof(valideur_det));
    res->size = nums->size;
    res->ligne = ligne;
    res->col = cols;
    return res;
}

void free_valideur_det(valideur_det* A){
    for (int i = 0;i<A->size;i++){
        free_auto(A->ligne[i]);
        free_auto(A->col[i]);
    }
    free(A->ligne);
    free(A->col);
    free(A);
}

void free_valideur_ndet(valideur_ndet *A){
    for (int i = 0;i<A->size;i++){
        free_auto_nd(A->ligne[i]);
        free_auto_nd(A->col[i]);
    }
    free(A->ligne);
    free(A->col);
    free(A);
}
