#ifndef LISTES_H
#define LISTES_H

//Implemantation basique d'une liste chainee
struct maillon {int val;struct maillon* suivant;};
typedef struct maillon maillon ;
typedef maillon* liste;

typedef struct 
{   int x;
    int y;
} duo ;

struct maillon_duo_s 
{
    duo val;
    struct maillon_duo_s* suivant;
};

typedef struct maillon_duo_s maillon_duo ;

typedef maillon_duo* duo_liste;


//Libere une liste
void free_liste(liste l);

//Ajoute un element a la liste
liste add_to_liste(int x,liste l);

//Ajoute un element en tete d'une liste de duo
duo_liste cons(duo head,duo_liste tail);

//Libere une liste de duo
void free_duo_liste(duo_liste l);

//Affiche un duo
void print_duo(duo d);

//Imprime une listes
void print_liste(liste l);

//Affiche une liste de duo
void print_duo_liste(duo_liste d);

//Donne la longeur de la liste
int len_liste(liste l);

//Transforme une liste en tableau
int* list_to_tab(liste l);
#endif