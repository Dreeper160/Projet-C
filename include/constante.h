#ifndef _CONSTANTE_H_
#define _CONSTANTE_H_
#define LIGNES 15
#define COLONNES 15
#define TAILLE_CASE 45
#define NB_MAX 4
#define INTERLIGNE 30
#define HAUTEUR_JOUEUR (TAILLE_CASE - 5)
#define LARGEUR_JOUEUR ((HAUTEUR_JOUEUR * 2) / 3)
/*ressources*/
#define FONT "Ressources/fonts/ARCADECLASSIC.TTF"
/*
 * Active l'extension POSIX.1b (1993) pour rendre visibles la fonction
 * clock_gettime() qui me permet de répucréer l'heure exacte de X chose ou action et CLOCK_MONOTONIC, qui ne font pas partie du C89 standard.
 * DOIT RESTER AVANT L'INCLUSION DE <time.h>.
 * Faut pas toucher la team
 */
#define _POSIX_C_SOURCE 199309L

#endif