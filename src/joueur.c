#include "joueur.h"
#include "constante.h"

void initialiser_joueur(entite *j, int x_depart, int y_depart){
    j->pos.x = x_depart;
    j->pos.y = y_depart;
}

void afficher_joueur(entite j){
    int centre_x = (j.pos.x * TAILLE_CASE) + (TAILLE_CASE / 2);
    int centre_y = (j.pos.y * TAILLE_CASE) + (TAILLE_CASE / 2);

    MLV_draw_filled_circle(centre_x, centre_y, (TAILLE_CASE / 2) - 4, MLV_COLOR_BLUE);
}

void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES]){
    int futur_x = j->pos.x;
    int futur_y = j->pos.y;

    if (touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z) {
        futur_y = futur_y - 1;
    }
    else if (touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s) {
        futur_y = futur_y + 1;
    }
    else if (touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_q) {
        futur_x = futur_x - 1;
    }
    else if (touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_d) {
        futur_x = futur_x + 1;
    }

    if (map[futur_y][futur_x] == 0) {
        j->pos.x = futur_x;
        j->pos.y = futur_y;
    }
}