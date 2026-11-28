#ifndef _BONUS_H
#define _BONUS_H

#include "constante.h"
#include "entite.h"
#include <time.h>

#include <stdlib.h>
#define RAYON_BONUS 3
#define FRAME_TRIFOLIUM 4
#define DUREE_EFFET_TRIFOLIUM 15 /*durée du boost*/
#define TEMPS_APPARITION 5
#define TAUX_DE_DROP 1 /*equivaut a 1% */
typedef struct
{
    int visible;

    int ligne;
    int colonne;
    struct timespec apparition;
} bonus_trifolium;

typedef struct
{
    int actif;
    struct timespec debut;
} effet_trifolium;

typedef struct
{
    bonus_trifolium trefle;
    effet_trifolium effet;
} bonus;
void initialiser_bonus(bonus *b);
int spawn_trifolium(bonus *b, int ligne, int colonne);
int ramasser_trifolium(bonus *b, const entite *joueur);
void actualiser_bonus(bonus *b);
void charger_images_trifolium(void);
void liberer_images_trifolium(void);
void afficher_trifolium(const bonus *b);

#endif