#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "gen_picross.h"

int main(){
    printf("Hello world!\n");
    srand(time(NULL));

    picross_grid* test = gen_random_grid(10, 35);
    print_picc(test);
    picross_numbers* test_nums = gen_numbers_from_grid(test);
    print_nums(test_nums);
    free_numbers(test_nums);
    free_picross(test);
    return 0;
}