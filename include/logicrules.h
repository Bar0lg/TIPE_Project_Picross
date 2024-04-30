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


line_est_t* estimate_line(liste numbers,int n);
estimation_t* full_estimation(picross_numbers* nums);
void print_full_estimation(estimation_t* e);
void print_estimation(line_est_t* e);
void free_estimation(line_est_t* e);
void free_full_estimation(estimation_t* e);
int rule1_1_line(int* line,int* nums,line_est_t* est,int size);
int apply_rules(picross_grid* grille_a_completer,picross_numbers* nums,estimation_t* est,int k);
#endif