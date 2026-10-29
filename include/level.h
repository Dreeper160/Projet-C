#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <MLV/MLV_all.h>
#include "constante.h"

extern int map[LIGNES][COLONNES];

/* @brief */ 
void charger_images_niveau();
/* @brief */
void afficher_niveau();
/* @brief */
void liberer_images_niveau();

#endif