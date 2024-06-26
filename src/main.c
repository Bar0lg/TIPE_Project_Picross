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
#include "logicrules.h"

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
#define LOGICRULES Fl(11)
#define GENGRILLE Fl(12)
#define RECORD Fl(13)

#define DEFAULT BACKTRACK|PRINTSEED
#define VERBOSE PRINTSEED | PRINTTIMEALGO | PRINTTIMEVALIDEUR | PRINTMODELE | PRINTSOL;
#define ALL_TIME PRINTTIMEALGO | PRINTTIMEVALIDEUR

#define RECORD_TO_FILE(file,seed,time_valid,time_lr,time_algo,lr_completed,mode) \
fprintf(file,"%d %f %f %f %f %d %d\n",seed,time_valid,time_lr,time_algo,(time_algo+time_lr+time_valid),lr_completed,mode)

int main(int argc,char** argv){
    int n = 4;
    int iter = 1;
    int seed = time(NULL);
    int options = 0;//Options par defaut
    char file_name[50] = "";
    FILE* record_file = NULL;
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
        if (strcmp(arg, "-r") ==0){
            assert(argc >= i+1);
            options |= RECORD;
            strcpy(file_name, argv[i+1]);
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
        if (strcmp(arg,"--lr") == 0){
            options |= LOGICRULES;
        }
        if (strcmp(arg,"-g") == 0){
            options |= GENGRILLE;
        }
    }
    printf("Debut du programme...\n");
    if (options & DEBUG){
        //INSERER CODE DEBUG ICI
        printf("No code in debug mode");
        return 0;
    }
    if (options & RECORD){
        record_file = fopen(file_name, "w");
    }
    if (options & PRINTSEED){
        printf("seed:%d\n",seed);
    }
    if (options & GENGRILLE){
        printf("Generation de la grille %d",seed);
        srand(seed);
        picross_grid* grille = gen_random_grid(n, chance);
        picross_grid* lr_grid = gen_unk_grid(n);
        picross_numbers* nums = gen_numbers_from_grid(grille);
        estimation_t* estimation = full_estimation(nums);
        int nb_lr = apply_rules(lr_grid, nums, estimation, 5);
        print_picc(grille);
        print_nums(nums);
        print_full_estimation(estimation);
        printf("LR solved:%d\n",nb_lr);
        print_picc(lr_grid);
        free_picross(lr_grid);
        free_picross(grille);
        free_numbers(nums);
        free_full_estimation(estimation);
        return 0;
    }
    for (int boucle = 1;boucle < iter +1;boucle++){
        clock_t t1_valid = 0;
        clock_t t2_valid = 0;
        double delta_valid = 0;
        clock_t t1_algo = 0;
        clock_t t2_algo = 0;
        double delta_algo = 0;
        clock_t t1_lr = 0;
        clock_t t2_lr = 0;
        double delta_lr = 0;
        int logic_rules_completed = -1;
        int mode = 0;

        srand(seed+boucle);
        picross_grid* grille_a_trouver = gen_random_grid(n,chance);
        picross_numbers* numeros = gen_numbers_from_grid(grille_a_trouver);
        if(options & PRINTMODELE){
            print_picc(grille_a_trouver);
            print_nums(numeros);
        }

        if (BRUTE & options){
            mode = 0;
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
            if (options & RECORD){
                RECORD_TO_FILE(record_file, seed+boucle, delta_valid, delta_lr, delta_algo, logic_rules_completed, mode);
            }

        }
        if (BACKTRACK & options){
            mode = 1;
            picross_grid* grille_inconnue = gen_unk_grid(n);
            t1_valid = clock();
            valideur_det* valideur_partiel = gen_valideur_partiel(numeros);
            t2_valid = clock();
            if (options & LOGICRULES){
                mode = 3;
                t1_lr = clock();
                estimation_t* estimation = full_estimation(numeros);
                logic_rules_completed = apply_rules(grille_inconnue, numeros, estimation, 5);
                t2_lr = clock();
                free_full_estimation(estimation);
                delta_lr = (double)(t2_lr - t1_lr) / CLOCKS_PER_SEC;
            }

            t1_algo = clock();
            bool res = backtracking(grille_inconnue,valideur_partiel,0,0);
            t2_algo = clock();

            delta_valid = (double)(t2_valid - t1_valid) / CLOCKS_PER_SEC;
            delta_algo  = (double)(t2_algo - t1_algo) / CLOCKS_PER_SEC;

            if (options & PRINTSOL){
                print_picc(grille_inconnue);
            }

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
                    printf("Temps LR: %f sec ",delta_lr);
                    printf("Nb fait:%d ",logic_rules_completed);
                }
                if (options & PRINTTIMEALGO){
                    printf("Temps algo: %f sec ",delta_algo);
                }
                printf("\n");
            }
            if (options & RECORD){
                RECORD_TO_FILE(record_file, seed+boucle, delta_valid, delta_lr, delta_algo, logic_rules_completed, mode);
            }

        }
        if (BACKTRACK_ND & options){
            mode = 2;
            picross_grid* grille_inconnue = gen_unk_grid(n);
            t1_valid = clock();
            valideur_ndet* valideur_partiel_ndet = gen_valideur_ndet(numeros);
            t2_valid = clock();

            if (options & LOGICRULES){
                mode = 4;
                t1_lr = clock();
                estimation_t* estimation = full_estimation(numeros);
                logic_rules_completed = apply_rules(grille_inconnue, numeros, estimation, 5);
                t2_lr = clock();
                free_full_estimation(estimation);
                delta_lr = (double)(t2_lr - t1_lr) / CLOCKS_PER_SEC;
            }

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
                    printf("Temps LR: %f sec",delta_lr);
                    printf("Nb fait: %d ",logic_rules_completed);
                }
                if (options & PRINTTIMEALGO){
                    printf("Temps algo: %f sec ",delta_algo);
                }
                printf("\n");
            }
            if (options & RECORD){
                RECORD_TO_FILE(record_file, seed+boucle, delta_valid, delta_lr, delta_algo, logic_rules_completed, mode);
            }

        }
        free_picross(grille_a_trouver);
        free_numbers(numeros);
        
    }
    if (options & RECORD){
        fclose(record_file);
    }
    
    printf("Fin programme\n");
    return 0;
}