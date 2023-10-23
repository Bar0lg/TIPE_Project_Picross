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

void add_connection(automate_cd* A,int etat_d,char lettre,int etat_f);

int delta_etoile_afd(automate_cd* A,int q,char* input);

bool reconnu_afd(automate_cd* A,char* input);

#endif