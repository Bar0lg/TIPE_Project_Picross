#ifndef GEN_PICROSS_H
#define GEN_PICROSS_H

struct picross_grid_s {int size; int** grid;};
typedef struct picross_grid_s picross_grid;

struct picross_numbers_s {int** lig;int** col;int size;};
typedef struct picross_numbers_s picross_numbers;

picross_grid* gen_random_grid(int size, int chance);

picross_numbers* gen_numbers_from_grid(picross_grid* grid);

void free_picross(picross_grid* p);

void free_numbers(picross_numbers* n);
#endif