#ifndef BOMBE_H
#define BOMBE_H

#define T_MAX 2 /* Temps maximal associé à une bombe*/
#include <MLV/MLV_all.h>
#include <time.h>
#include "constante.h" /* Constantes du projet*/
#include "entite.h"    /* Définition du type entite*/

/**
 * @brief Représente une Bombe
 *
 */
typedef struct
{
    entite b;                   /* Entité représentant la bombe*/
    int rayon;                  /* Rayon de l'explosion*/
    struct timespec temps_pose; /* Moment où la bombe a été posée*/
} bombe;

/**
 * @brief Représente une explosion
 *
 */
typedef struct
{
    entite explo;                     /* Entité représentant l'explosion*/
    struct timespec temps_apparition; /* Moment où l'explosion apparaît*/
} explosion;

/**
 * @brief Affiche une bombe à l'écran
 *
 * @param bombe
 */
void afficher_bombe(bombe bombe);

/**
 * @brief  Place une bombe à partir de la position de l'entité j
 *
 * @param b la bombe
 * @param j l'entite qui place la bombe
 */
void placer_bombe(bombe *bom, entite j);
/**
 * @brief
 *
 * @param b Récupere la bombe qui doit disparaitre
 * @return int
 */
int bombe_expiree(bombe *bom);
#endif