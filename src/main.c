#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "automates.h"
#include "utils.h"
#include "gen_picross.h"

int main(){
    printf("Hello world!\n");
    srand(time(NULL));

    picross_grid* test = gen_random_grid(10, 35);
    print_picc(test);
    picross_numbers* test_nums = gen_numbers_from_grid(test);
    
    print_nums(test_nums);
    automate_cd* test_2 = generer_automate_ligne(test_nums->lig[0],test_nums->size);
    print_auto(test_2);

    printf("Test:%d\n",reconnu_afd(test_2, test->grid[0],10));
    free_auto(test_2);
    free_picross(test);
    free_numbers(test_nums);
    return 0;
}