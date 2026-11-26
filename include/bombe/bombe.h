#ifndef BOMBE_H
#define BOMBE_H
#define RAYON_BOMBE_BASE 1
#define T_MAX 0.8 /* Temps avant explosion de la bombe */
#define FRAMES_MECHE 6
#define FRAMES_IGNITE 5
#define T_IGNITE 0.250 /* Le temps d'ignition */
#include <MLV/MLV_all.h>
#include <time.h>
#include "constante.h" /* Constantes du projet*/
#include "entite.h"    /* Définition du type entite*/

/**
 * @brief Représente une Bombe
 *
 */

typedef enum
{
    BOMBE_MECHE,
    BOMBE_IGNITE
    /*BOMBE_KLEE*/
} etat_bombe;

typedef struct
{
    entite b;                   /* Entité représentant la bombe*/
    int rayon;                  /* Rayon de l'explosion*/
    struct timespec temps_pose; /* Moment où la bombe a été posée*/
    etat_bombe state;
    struct timespec temps_explosion;
} bombe;

/**
 * @brief Représente une explosion
 *
 */
/**
 * @brief Permet de charger l'image associé a la bombe si aucune image n'est trouvé la bombe aura une texture noire
 *
 *
 * @param chemin chemin d'acces au sprite sheet de la bombe
 */
void charger_images_bombe(void);
void liberer_images_bombe(void);
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
/**
 * @brief Affiche une bombe à l'écran
 *
 * @param bombe
 */
void afficher_bombe(bombe bombe);

#endif