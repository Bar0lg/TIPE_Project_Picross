#ifndef LISTES_H
#define LISTES_H

//Implemantation basique d'une liste chainee
struct maillon {int val;struct maillon* suivant;};
typedef struct maillon maillon ;
typedef maillon* liste;

//Libere une liste
void free_liste(liste l);

//Ajoute un element a la liste
liste add_to_liste(int x,liste l);


//Imprime une listes
void print_liste(liste l);

#endif