#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "automates.h"
#include "utils.h"
#include "gen_picross.h"
#include "solver.h"

int main(){
    printf("Hello world!\n");
    srand(time(NULL));

    picross_grid* test = gen_random_grid(4, 35);
    print_picc(test);
    picross_numbers* test_nums = gen_numbers_from_grid(test);
    print_nums(test_nums);
    
    valideur_total* valid_1 = gen_valideur_total(test_nums);

    //print_auto(valid_1->ligne[3]);
    //print_auto(valid_1->col[3]);
    
    picross_grid* test_brute = brute_force(valid_1);

    print_picc(test_brute);


    free_valideur_total(valid_1);
    free_numbers(test_nums);
    free_picross(test);
    free_picross(test_brute);
    return 0;
}