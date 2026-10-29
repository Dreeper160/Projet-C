#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "entite.h"
#include "constante.h"

void initialiser_joueur(entite *j, int x_depart, int y_depart);
void afficher_joueur(entite j);
void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES]);

#endif