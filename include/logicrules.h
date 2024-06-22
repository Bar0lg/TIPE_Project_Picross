#ifndef LOGICRULES_H
#define LOGICRULES_H

#include "listes.h"
#include "picross.h"
typedef struct {
    int nb_blocks;
    duo* est;
}line_est_t;

typedef struct {
    int n;
    line_est_t** lines;
    line_est_t** cols;
} estimation_t;

//Une estimation est la la portee possible de chaque blocs nessesaire pour appliquer les regles
//Pour comprendre ce qui est fait voir "an efficient algorithm for solving nonograms" : DOI:10.1007/s10489-009-0200-0
//(Le noms des règles est aussi basé sur ce document)

//Donne l'esimation d'une ligne
line_est_t* estimate_line(liste numbers,int n);

//Donne l'estimation d'une grille
estimation_t* full_estimation(picross_numbers* nums);

//Les 5 fonctions en dessous marche par effet de bord et renvoie le nombre de cases changé


//Remplie une ligne avec 0
int fill_with_0(int* line,int size);

//Applique le regle 1.1
int rule1_1_line(int* line,int* nums,line_est_t* est);

//Applique le regle 1.2
int rule1_2_line(int* line,int size,line_est_t* est);

//Applique le regle 2.2
int rule2_2line(int* line,int size,line_est_t* est);

//Aplique la règle 1.3
int rule1_3line(int* line,int size,int* nums,line_est_t* est);



void print_full_estimation(estimation_t* e);


void print_estimation(line_est_t* e);


void free_estimation(line_est_t* e);


void free_full_estimation(estimation_t* e);

//Applique toutes les règles en passant k fois dans la grille (une valeur de 4-6 permet de trouver la majorité des cases décrouvrabe avec règles logiques)
int apply_rules(picross_grid* grille_a_completer,picross_numbers* nums,estimation_t* est,int k);
#endif