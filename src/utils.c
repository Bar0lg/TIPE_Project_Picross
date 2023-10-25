#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>



void free_int_int(int** t,int n){
    for(int i =0;i<n;i++){
        free(t[i]);
    }
    free(t);
}



void print_tab(int* t, int size){
    printf("[");
    for (int i = 0;i<size;i++){
        printf("%d ",t[i]);
    }
    printf("]");
}

void print_bool_tab(bool* t, int size){
    printf("[");
    for (int i = 0;i<size;i++){
        if (t[i]){
            printf("true ");
        }else{
            printf("false ");
        }
    }
    printf("]");

}


int binary_from_bool_int(bool* t,int size){
    int res =0;
    for (int i=0;i<size;i++){
        if (t[i]){
            res += pow(2,i);
        }
    }
    return res;
}


int inverse_valeur(int i){
    if (i==0){
        return 1;
    }else {
    return 0;
    }
}

