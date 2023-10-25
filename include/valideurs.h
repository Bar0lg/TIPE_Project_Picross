#ifndef VALIDEURS_H
#define VALIDEURS_H

#include "picross.h"
#include "automates.h"

struct valideur_d_s {automate_d** ligne;automate_d** col;int size;};
typedef struct valideur_d_s valideur_det;

struct valideur_nd_s {automate_nd** ligne;automate_nd** col;int size;};
typedef struct valideur_nd_s valideur_ndet ;

//Automate qui reconnais une ligne vide
automate_d* auto_de_zeros(void);

//Automate partiel qui recconais une ligne vide
automate_nd* auto_nd_zeros(void);

//Genere un automate qui recconais la ligne donnee
automate_d* generer_automate_ligne(liste ligne);

//Genere tous les automates poutes tt lignes et colonnes
valideur_det* gen_valideur_total(picross_numbers* nums);

//Genere l'automate partiel d'une ligne
automate_nd* generer_automate_partiel_ligne(liste ligne);

//Genere un valideur non det
valideur_ndet* gen_valideur_ndet(picross_numbers* nums);

//Libere le valideur
void free_valideur_total(valideur_det* A);

//Libere un vlaideur ndet
void free_valideur_ndet(valideur_ndet *A);
#endif