#include <stdlib.h>

#include "automates.h"
#include "picross.h"

automate_d* auto_de_zeros(void){
    automate_d* res = init_automate(2,1);
    res->depart = 0;
    res->finaux[0] = true;
    add_connection_d(res,0,0,0);
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

valideur_total* gen_valideur_total(picross_numbers* nums){
    automate_d** ligne = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    automate_d** cols = (automate_d**)malloc(sizeof(automate_d*)*nums->size);
    for(int i=0;i<nums->size;i++){
        ligne[i] = generer_automate_ligne(nums->lig[i]);
        cols[i] = generer_automate_ligne(nums->col[i]);
    }
    valideur_total* res = (valideur_total*)malloc(sizeof(valideur_total));
    res->size = nums->size;
    res->ligne = ligne;
    res->col = cols;
    return res;
}

void free_valideur_total(valideur_total* A){
    for (int i = 0;i<A->size;i++){
        free_auto(A->ligne[i]);
        free_auto(A->col[i]);
    }
    free(A->ligne);
    free(A->col);
    free(A);
}