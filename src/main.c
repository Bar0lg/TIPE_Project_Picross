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
#define PRINTMODELE Fl(8)
#define PRINTSOL Fl(9)
#define BACKTRACK_ND Fl(10)

#define DEFAULT BACKTRACK|PRINTSEED
#define VERBOSE PRINTSEED | PRINTTIMEALGO | PRINTTIMEVALIDEUR | PRINTMODELE | PRINTSOL;
#define ALL_TIME PRINTTIMEALGO | PRINTTIMEVALIDEUR

int main(int argc,char** argv){
    int n = 3;
    int iter = 1;
    int seed = time(NULL);
    int options = 0;//Options par defaut

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
        if (strcmp(arg,"--backtrack")== 0){
            options |= BACKTRACK;
        }
        if (strcmp(arg,"--backtrack-nd")== 0){
            options |= BACKTRACK_ND;
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
        if (strcmp(arg,"-q") == 0){
            options |= QUIET;
        }
        if (strcmp(arg,"-d") == 0){
            options |= DEBUG;
        }
        if (strcmp(arg,"--print-model") == 0){
            options |= PRINTMODELE;
        }
        if (strcmp(arg,"--print-sol") == 0){
            options |= PRINTSOL;
        }
        if (strcmp(arg,"-v") == 0){
            options |= VERBOSE;
        }
        if (strcmp(arg,"-t") == 0){
            options |= ALL_TIME;
        }
        if (strcmp(arg,"--default") == 0){
            options |= DEFAULT;
        }

        if (strcmp(arg, "--help") == 0){
            printf("Options: -n --seed --iter --chance --backtrack --brute --print-time-valideur --print-time-algo --print-seed --quiet --debug --print-model --print-sol\n ");
        }
    }
    printf("Debut du programme...\n");
    if (options & DEBUG){
        //bool t[] = {false,false,false,false};
        //printf("%d",binary_from_bool_int(t, 4));
        //Mettre le code debug ici
        srand(seed+1);
        picross_grid* test_grille = gen_random_grid(n,chance);
        print_picc(test_grille);
        picross_numbers* test_nums = gen_numbers_from_grid(test_grille);
        valideur_det* val_test = gen_valideur_total(test_nums);
        printf("TEST VAL: %d\n",est_solution_valide_total(test_grille,val_test));

        free_valideur_det(val_test);
        free_picross(test_grille);
        free_numbers(test_nums);
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
        if(options & PRINTMODELE){
            print_picc(grille_a_trouver);
            print_nums(numeros);
        }

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

            if (options & PRINTSOL){
                print_picc(grille_vide);
            }
            //for (int i=0;i<3;i++){
            //    printf("%d\n",i);
            //    print_auto(valideur_complet->ligne[i]);
            //    print_auto(valideur_complet->col[i]);
            //
            //}
            free_picross(grille_vide);
            free_valideur_det(valideur_complet);


            //En cas d'erreur (ce qui est normalment impossible)
            if (!res){
                printf("Erreur de brute-force seed:%d\n",seed+boucle);
                free_picross(grille_a_trouver);
                free_numbers(numeros);
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
            valideur_det* valideur_partiel = gen_valideur_partiel(numeros);
            t2_valid = clock();

            t1_algo = clock();
            bool res = backtracking(grille_inconnue,valideur_partiel,0,0);
            t2_algo = clock();

            delta_valid = (double)(t2_valid - t1_valid) / CLOCKS_PER_SEC;
            delta_algo  = (double)(t2_algo - t1_algo) / CLOCKS_PER_SEC;

            if (options & PRINTSOL){
                print_picc(grille_inconnue);
            }

            print_auto(valideur_partiel->ligne[0]);
            free_picross(grille_inconnue);
            free_valideur_det(valideur_partiel);


            //En cas d'erreur (ce qui est normalment impossible)
            if (!res){
                printf("Erreur de backtrack seed:%d\n",seed+boucle);
                free_picross(grille_a_trouver);
                free_numbers(numeros);
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
        if (BACKTRACK_ND & options){
            picross_grid* grille_inconnue = gen_unk_grid(n);
            t1_valid = clock();
            valideur_ndet* valideur_partiel_ndet = gen_valideur_ndet(numeros);
            t2_valid = clock();

            t1_algo = clock();
            bool res = backtracking_ndet(grille_inconnue,valideur_partiel_ndet,0,0);
            t2_algo = clock();

            delta_valid = (double)(t2_valid - t1_valid) / CLOCKS_PER_SEC;
            delta_algo  = (double)(t2_algo - t1_algo) / CLOCKS_PER_SEC;

            if (options & PRINTSOL){
                print_picc(grille_inconnue);
            }
            free_picross(grille_inconnue);
            free_valideur_ndet(valideur_partiel_ndet);


            //En cas d'erreur (ce qui est normalment impossible)
            if (!res){
                printf("Erreur de backtrack seed:%d\n",seed+boucle);
                free_picross(grille_a_trouver);
                free_numbers(numeros);
                return -1;
            }
            
            if (!(options & QUIET)){
                printf("%d/%d resolu backtrack-nd ",boucle,iter);
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