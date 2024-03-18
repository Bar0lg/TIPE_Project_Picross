#ifndef LOGICRULES_H
#define LOGICRULES_H

#include "listes.h"

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
void print_estimation(line_est_t* e);
void free_estimation(line_est_t* e);
#endif