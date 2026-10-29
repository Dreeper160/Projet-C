#ifndef _CONSTANTE_H_
#define _CONSTANTE_H_
#define LIGNES 15
#define COLONNES 15
#define TAILLE_CASE 45
/*ressources*/
#define FONT "Ressources/ARCADECLASSIC.TTF"

/*
 * Active l'extension POSIX.1b (1993) pour rendre visibles la fonction
 * clock_gettime() qui me permet de répucréer l'heure exacte de X chose ou action et CLOCK_MONOTONIC, qui ne font pas partie du C89 standard.
 * DOIT RESTER AVANT L'INCLUSION DE <time.h>.
 */
#define _POSIX_C_SOURCE 199309L

#endif