#ifndef UTILS_H
#define UTILS_H

#include "gen_picross.h"
#include <stdbool.h>

void free_int_int(int** t,int n);

void print_picc(picross_grid* p);

void print_tab(int* t, int size);

void print_bool_tab(bool* t, int size);

void print_nums(picross_numbers* nums);

int max_size_line(int size_picc);

void print_auto(automate_cd* A);
#endif