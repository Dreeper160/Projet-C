#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <MLV/MLV_all.h>
#include "constante.h"

extern int map[LIGNES][COLONNES];

void charger_images_niveau();
void afficher_niveau();
void liberer_images_niveau();

#endif