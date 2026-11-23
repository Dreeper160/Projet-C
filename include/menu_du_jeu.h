#ifndef _MENU_DU_JEU_H_
#define _MENU_DU_JEU_H_
#include <MLV/MLV_all.h>
#include "constante.h"

typedef enum{
    quitter = 0,
    jouer = 1,
    charger = 2,
    options = 3,
    menu_pause = 4
} Etat;

void afficher_menu(MLV_Font *font_titre, MLV_Font *font_boutons);
int interagir_menu(MLV_Font *font_boutons);

#endif
