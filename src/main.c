#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "automates.h"
#include "utils.h"
#include "gen_picross.h"

int main(){
    printf("Hello world!\n");
    srand(time(NULL));

    picross_grid* test = gen_random_grid(5, 35);
    print_picc(test);
    picross_numbers* test_nums = gen_numbers_from_grid(test);
    free_picross(test);
    automate_cd* test_2 = generer_automate_ligne(test_nums->lig[0],test_nums->size);
    print_auto(test_2);
    return 0;
}