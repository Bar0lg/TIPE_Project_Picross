Avertissement : ce code est une monstruosité sans nom, un mélange inconsistant de français et d'anglais avec peu de commentaires, essayer de le comprendre peut mener à la folie.

Le makefile est celui que j'utilise pour tous mes codes donc certains dossiers ne servent à rien pour ce projet notamment ./dat

./spe contient un exécutable qui permet d'exécuter le programme tel que les emplacements de fichiers relatifs se font à partir de l'exécutable (dans build/bin) et non de l'endroit où l'utilisateur a lancé le programme
Cet exécutable est automatiquement mis à la racine /build/ quand on compile

/inculde contient tout les .h
/src contient tout les .c

LES FICHIRES:

    automates.c Contient tout ce qui touche aux automates: création, reconnaissance de mot, determinisation etc

    dicts.c Contient la librairie pour les dictionnaires

    listes.c gère les listes d'entiers et de duo

    logicrules.c gère toutes les règles logiques

    picross.c gère les grilles: création, libération, génération

    valideurs.c contient tout ce qui permet de valider la grille: c'est ici qu'on génère les automates de solution totale et partielle

    solver.c contient le code des algorithmes de backtracking et brute force

    main.c permet de tout exécuter

Il y a une légère description de ce que fait chaque fonction dans les .h mais comme dit plus tôt, peu de commentaire dans le code lui-même

LES ARGUMENTS:
    Pas besoin de recompiler le programme à chaque nouvelle expérience tout peut être géré avec l'exécutable
    Chaque argument peut être mis dans n'importe quel ordre
    Les crochets doivent être remplacé par des valeurs


    SPECIFICATION DE LA GRILLE:
        -n [TAILLE] change la taille de la grille (min 3, par défaut 4)

        --seed [SEED] change la graine aléatoire de départ, sinon spécifié time(NULL) est utilisé

        --iter [N] répète l'expérience N fois, la valeur de la grille de chaque expérience est incrémenté de 1 à chacun expérience

        --chance [0-100] modifie la probabilité que chaque case soit noire

    ALGORITMES:
        --backrack applique l'algorithme de backtrack avec automates déterministes

        --backtrack-nd applique l'algorithme de backtrack avec automates non déterministes

        --brute applique l'algorithme de brute force

        --L'applique les règles logiques (ne s'applique pas au brute-force)

        NOTE: Si plusieurs algorithmes sont spécifiés, la même grille passera par chaque algoritmes


    SPECIAUX:
        -g ignore tous les arguments autres que -n --seed et --chance et génère une grille aléatoire avec ces paramètres et l'affiche ainsi que l'application des règles logiques

        -d execute le code placé dans la zone de débuggage (ligne 116 de main.c)

    AFFICHAGE:
        Ces commandes afichent les diffirentes informations a chaque expériences

        --print-time-valideur : Temps de création des automates

        --print-time-algo : Temps de complétion de l'algorithme

        --print-seed : Affiche la grille

        --print-model : Affiche la grille générée aléatoirment

        --print-sol : affiche la grille trouvé par l'algorithme

        -t affiche tout les temps

        -v affiche tout

        -q ignore toute les arguments d'affichage et n'affiche rien

    ENREGISTEMENT:

        -r [CHEMEIN_FICHIER] enregistre les résultat dans un fichier
        le fichier a la forme:

        [GRAINE] [TEMPS_AUTOMATE] [TEMPS REGLE LOGIQUES] [TEMPS ALGO] [TEMPS TOTAL] [CASES TROUVE AVEC REGLES LOGIQUES] [ALGO]
        [GRAINE] [TEMPS_AUTOMATE] [TEMPS REGLE LOGIQUES] [TEMPS ALGO] [TEMPS TOTAL] [CASES TROUVE AVEC REGLES LOGIQUES] [ALGO]
        [GRAINE] [TEMPS_AUTOMATE] [TEMPS REGLE LOGIQUES] [TEMPS ALGO] [TEMPS TOTAL] [CASES TROUVE AVEC REGLES LOGIQUES] [ALGO]
        ...

        avec pour algo:
        1 -> bruteforce
        2 -> backtrack
        3 -> backtrack non-det
        4 -> backtrack + regles
        5 -> backtrack non-det + regles

    EXAMPLES
        ./build/runner.sh --iter 1000 -n 12 --backtrack --lr -r ./resultats.txt
        Résout 1000 fois des grilles de taille 12 avec un algorithme de back tracking et règles logiques et enregistre le résultat dans results.Txt