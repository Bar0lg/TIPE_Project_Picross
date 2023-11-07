#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "automates.h"
#include "utils.h"
#include "picross.h"
#include "solver.h"
#include "valideurs.h"

#define BRUTE Fl(1)
#define BACKTRACK Fl(2)
#define PRINTTIMEVALIDEUR Fl(3)
#define PRINTTIMEALGO Fl(4)
#define QUIET Fl(5)
#define PRINTSEED Fl(6)
#define DEBUG Fl(7)

int main(int argc,char** argv){
    int n = 3;
    int iter = 1;
    int seed = time(NULL);
    int options = BACKTRACK |/* PRINTTIMEVALIDEUR | PRINTTIMEALGO |*/PRINTSEED; //Options par defaut
    int chance = 50;
    printf("Hello world!\n");

    for (int i=1;i<argc;i++){
        char* arg = argv[i];
        if (strcmp(arg,"--seed") == 0){
            assert(argc >= i+1);
            seed = atoi(argv[i+1]);
        }
        if (strcmp(arg,"-n") == 0){
            assert(argc >= i+1);
            n = atoi(argv[i+1]);
        }
        if (strcmp(arg, "--iter") ==0){
            assert(argc >= i+1);
            iter = atoi(argv[i+1]);
        }
        if (strcmp(arg, "--chance") ==0){
            assert(argc >= i+1);
            chance = atoi(argv[i+1]);
        }
        if (strcmp(arg,"--backtrck")== 0){
            options |= BACKTRACK;
        }
        if (strcmp(arg,"--brute") == 0){
            options |= BRUTE;
        }
        if (strcmp(arg,"--print-time-valideur") == 0){
            options |= PRINTTIMEVALIDEUR;
        }
        if (strcmp(arg,"--print-time-algo") == 0){
            options |= PRINTTIMEALGO;
        }
        if (strcmp(arg,"--print-seed") == 0){
            options |= PRINTSEED;
        }
        if (strcmp(arg,"--quiet") == 0){
            options |= QUIET;
        }
        if (strcmp(arg,"--debug") == 0){
            options |= DEBUG;
        }
        if (strcmp(arg, "--help") == 0){
            printf("Options: -n --seed --iter --chance --backtrack --brute --print-time-valideur --print-time-algo --print-seed --quiet --debug\n ");
        }
    }
    printf("Debut du programme...\n");
    if (options & DEBUG){
        //Mettre le code debug ici
        return 0;
    }
    for (int boucle = 1;boucle < iter +1;boucle++){
        clock_t t1_valid = 0;
        clock_t t2_valid = 0;
        double delta_valid = 0;
        clock_t t1_algo = 0;
        clock_t t2_algo = 0;
        double delta_algo = 0;

        srand(seed+boucle);
        picross_grid* grille_a_trouver = gen_random_grid(n,chance);
        picross_numbers* numeros = gen_numbers_from_grid(grille_a_trouver);

        if (BRUTE & options){
            picross_grid* grille_vide = gen_empty_grid(n);
            t1_valid = clock();
            valideur_det* valideur_complet = gen_valideur_total(numeros);
            t2_valid = clock();

            t1_algo = clock();
            bool res = bruteforce(grille_vide,valideur_complet,0,0);
            t2_algo = clock();

            delta_valid = (double)(t2_valid - t1_valid) / CLOCKS_PER_SEC;
            delta_algo  = (double)(t2_algo - t1_algo) / CLOCKS_PER_SEC;

            free_picross(grille_vide);
            free_valideur_total(valideur_complet);


            //En cas d'erreur (ce qui est normalment impossible)
            if (!res){
                printf("Erreur de backtrack seed:%d\n",seed+boucle);
                return -1;
            }
            
            if (!(options & QUIET)){
                printf("%d/%d resolu brute ",boucle,iter);
                if (options & PRINTTIMEVALIDEUR){
                    printf("Temps valideur: %f sec ",delta_valid);
                }
                if (options & PRINTTIMEALGO){
                    printf("Temps algo: %f sec ",delta_algo);
                }
                printf("\n");
            }

        }

        if (BACKTRACK & options){
            picross_grid* grille_inconnue = gen_unk_grid(n);
            t1_valid = clock();
            valideur_partiel* valideur_partiel = gen_valideur_partiel(numeros);
            t2_valid = clock();

            t1_algo = clock();
            bool res = backtracking(grille_inconnue,valideur_partiel,0,0);
            t2_algo = clock();

            delta_valid = (double)(t2_valid - t1_valid) / CLOCKS_PER_SEC;
            delta_algo  = (double)(t2_algo - t1_algo) / CLOCKS_PER_SEC;

            free_picross(grille_inconnue);
            free_valideur_partiel(valideur_partiel);


            //En cas d'erreur (ce qui est normalment impossible)
            if (!res){
                printf("Erreur de brute_force seed:%d\n",seed+boucle);
                return -1;
            }
            
            if (!(options & QUIET)){
                printf("%d/%d resolu backtrack ",boucle,iter);
                if (options & PRINTTIMEVALIDEUR){
                    printf("Temps valideur: %f sec ",delta_valid);
                }
                if (options & PRINTTIMEALGO){
                    printf("Temps algo: %f sec ",delta_algo);
                }
                printf("\n");
            }

        }

        free_picross(grille_a_trouver);
        free_numbers(numeros);
        
    }
    if (options & PRINTSEED){
        printf("seed:%d\n",seed);
    }
    printf("Fin programme\n");
    return 0;
}