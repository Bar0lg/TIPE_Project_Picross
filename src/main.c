#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "automates.h"
#include "utils.h"
#include "picross.h"
#include "solver.h"
#include "valideurs.h"

int main(){
    printf("Hello world!\n");
    srand(time(NULL));

    picross_grid* test = gen_random_grid(3, 40);
    print_picc(test);
    picross_numbers* test_nums = gen_numbers_from_grid(test);
    print_nums(test_nums);
    
    //valideur_det* valid_1 = gen_valideur_total(test_nums);

    //print_auto(valid_1->ligne[3]);
    //print_auto(valid_1->col[3]);

    valideur_partiel* valid_par = gen_valideur_partiel(test_nums);
    valideur_ndet* debug_test = gen_valideur_ndet(test_nums);

    picross_grid* unk_grid = gen_unk_grid(5);

    print_picc(unk_grid);
    print_auto(valid_par->ligne[0]);
    print_auto_nd(debug_test->ligne[0]);
    
    //picross_grid* test_brute = brute_force(valid_1);

    //print_picc(test_brute);
    bool res_test = verif_ligne_col(unk_grid, valid_par, 0, 0);

    printf("TEST:%d\n",res_test);
    //free_valideur_total(valid_1);
    free_numbers(test_nums);
    free_picross(test);
    free_picross(unk_grid);
    //free_picross(test_brute);
    free_valideur_partiel(valid_par);
    free_valideur_ndet(debug_test);
    return 0;
}