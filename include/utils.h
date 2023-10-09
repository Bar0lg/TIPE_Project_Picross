#ifndef UTILS_H
#define UTILS_H

#include "gen_picross.h"

void free_int_int(int** t,int n);

void print_picc(picross_grid* p);

void print_tab(int* t, int size);

void print_nums(picross_numbers* nums);
#endif