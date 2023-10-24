#ifndef VALIDEURS_H
#define VALIDEURS_H

#include "picross.h"
#include "automates.h"

//Automate qui reconnais une ligne vide
automate_d* auto_de_zeros(void);

//Genere un automate qui recconais la ligne donnee
automate_d* generer_automate_ligne(liste ligne);

//Genere tous les automates poutes tt lignes et colonnes
valideur_total* gen_valideur_total(picross_numbers* nums);


//Libere le valideur
void free_valideur_total(valideur_total* A);
#endif