#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <MLV/MLV_all.h>
#include "constante.h"

typedef struct {
    MLV_Image *sol;
    MLV_Image *mur_cassable;
    MLV_Image *mur_incassable;
} Images_niveau;

/* @brief */
void rempl_lvl_1(int map[LIGNES][COLONNES]);
/* @brief */
void rempl_lvl_rand(int map[LIGNES][COLONNES]);
/* @brief */ 
void charger_images_niveau(Images_niveau *imgs);
/* @brief */
void afficher_niveau(int map[LIGNES][COLONNES], Images_niveau imgs);
/* @brief */
void liberer_images_niveau(Images_niveau *imgs);

#endif