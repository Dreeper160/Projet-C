#include "joueur.h"
#include "constante.h"

void initialiser_joueur(entite *j, int x_depart, int y_depart){
    /* On convertit la case de départ en PIXELS (le centre de la case) */
    j->pos.x = (x_depart * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    j->pos.y = (y_depart * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    j->est_en_vie = 1;
}

void afficher_joueur(entite j){
    MLV_draw_filled_circle(j.pos.x, j.pos.y, (TAILLE_CASE / 2) - 4, MLV_COLOR_BLUE);
}

void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES]){
    float futur_x = j->pos.x;
    float futur_y = j->pos.y;
    float vitesse = 3.0; /* Le joueur avance de 3 pixels à chaque image */
    int rayon = (TAILLE_CASE / 2) - 4; /* Le rayon physique du joueur (18 pixels) */
    
    int case_gauche, case_droite, case_haut, case_bas;

    if (touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z) {
        futur_y = futur_y - vitesse;
    }
    else if (touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s) {
        futur_y = futur_y + vitesse;
    }
    else if (touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_q) {
        futur_x = futur_x - vitesse;
    }
    else if (touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_d) {
        futur_x = futur_x + vitesse;
    }

    /* On calcule où se trouveront les 4 bords du joueur en pixels */
    /* On divise par TAILLE_CASE pour savoir dans quelles cases de la map ils tombent */
    case_gauche = (futur_x - rayon) / TAILLE_CASE;
    case_droite = (futur_x + rayon) / TAILLE_CASE;
    case_haut   = (futur_y - rayon) / TAILLE_CASE;
    case_bas    = (futur_y + rayon) / TAILLE_CASE;

    /* On vérifie que les 4 coins du joueur sont bien sur de l'air (0) */
    if (map[case_haut][case_gauche] == 0 &&
        map[case_haut][case_droite] == 0 &&
        map[case_bas][case_gauche] == 0 &&
        map[case_bas][case_droite] == 0) 
    {
        /* Aucun mur ne touche notre cercle, on valide le mouvement ! */
        j->pos.x = futur_x;
        j->pos.y = futur_y;
    }
}