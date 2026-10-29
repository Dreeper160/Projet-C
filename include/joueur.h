#ifndef _JOUEUR_H_
#define _JOUEUR_H_
#include "entite.h"
#include "constante.h"

/* @brief */ 
void charger_images_joueur();
/*@brief */ 
void liberer_images_joueur();
/*@brief 
 @param j 
 @param x_depart 
 @param y_depart */ 
void initialiser_joueur(entite *j, int x_depart, int y_depart);
/* @brief 
   @param j */
void afficher_joueur(entite j);
/* @brief 
   @param j 
   @param touche 
   @param map */ 
void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES]);

#endif