#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_
#include <stdio.h>
#include "constante.h"
#include "entite.h"

int sauvegarder_partie(int map[LIGNES][COLONNES], entite j, int nb);
int charger_partie(int map[LIGNES][COLONNES], entite *j, int nb);

#endif