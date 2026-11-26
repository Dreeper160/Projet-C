#ifndef _EXPLOSION_H
#define _EXPLOSION_H
#define DUREE_EXPLOSION 1.0 /** Durée d'affichage, en secondes. */
#include "entite.h"
#include <time.h>
#include "bombe.h"
#include "constante.h"

/** @brief Coordonnées d'une case touchée par une explosion. */
typedef struct
{
    int ligne;
    int colonne;
} case_explosion;

/** @brief Représente une explosion active sur la grille. */
typedef struct
{
    case_explosion cases[LIGNES * COLONNES]; /** Cases touchées par les flammes. */
    int nb_cases;                            /** Nombre de cases valides dans cases. */
    int active;                              /** Indique si l'explosion est encore active. */
    struct timespec temps_apparition;        /** Heure d'apparition, avec CLOCK_MONOTONIC. */
} explosion;
/**
 * @brief
 *
 * @param exp
 * @param b
 * @param map
 */
void executer_explosion(explosion *exp, const bombe *b, int map[LIGNES][COLONNES]);
int joueur_touche_explosion(const explosion *exp, const entite *joueur);
void actualiser_explosion(explosion *exp);
/**
 * @brief
 *
 * @param exp represente l'explosion
 */
void afficher_explosion(const explosion *exp);

#endif
