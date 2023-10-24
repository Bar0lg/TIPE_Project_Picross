#ifndef AUTOMATES_H
#define AUTOMATES_H

#include <stdbool.h>

struct automate_cd_s {
    int nb_lettres;
    int nb_etats;
    int depart;
    bool* finaux;
    int puit;
    int** delta;
};
typedef struct automate_cd_s automate_cd;


automate_cd* init_automate(int size_alpha,int size_etats);

void free_auto(automate_cd* a);

void add_connection(automate_cd* A,int etat_d,int lettre,int etat_f);

int delta_etoile_afd(automate_cd* A,int q,int* input, int size_input);

bool reconnu_afd(automate_cd* A,int* input, int size_input);

//Affiche l'automate
void print_auto(automate_cd* A);

#endif