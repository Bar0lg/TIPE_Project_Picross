#ifndef AUTOMATES_H
#define AUTOMATES_H

#include <stdbool.h>
#include "listes.h"

struct automate_d_s {
    int nb_lettres;
    int nb_etats;
    int depart;
    bool* finaux;
    int** delta;
};
typedef struct automate_d_s automate_d;

struct automate_nd {
    int nb_lettres;
    int nb_etats;
    bool* depart;
    bool* finaux;
    liste** delta;
};
typedef struct automate_nd automate_nd ;

//Initialise un automate deterministe
automate_d* init_automate(int size_alpha,int size_etats);

//Libere un automate
void free_auto(automate_d* a);

//Ajoute une connection dans l'automate
void add_connection_d(automate_d* A,int etat_d,int lettre,int etat_f);

//Delta etoile de l'automate
int delta_etoile_d(automate_d* A,int q,int* input, int size_input);

//Verifie si un mot est reconnu par l'automate
bool reconnu_afd(automate_d* A,int* input, int size_input);

//Affiche l'automate
void print_auto(automate_d* A);

//Initialise un automate non deterministe
automate_nd* init_automate_ncd(int size_alpha,int size_etats);

//Delta de l'automate non deterministe
bool* delta_nd(automate_nd* A,bool* etats_depart,int lettre);

//Delta etoile de l'Automte non deterministe
bool* delta_etoile_nd(automate_nd* A,bool* etats_depart,int* input,int size_input);

//Verifie si un mot est reconnu par l'automate
bool reconnu_afnd(automate_nd *A, int *input, int size_input);

//Affiche l'automate non deterministe
void print_auto_nd(automate_nd* A);
#endif