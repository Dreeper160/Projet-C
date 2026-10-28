#include "constante.h"
#include "entite.h"
#include "joueur.h"
#include "level.h"

int main(void)
{
    entite j1;
    int continuer = 1;

    initialiser_joueur(&j1, 1, 1);

    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);

    while (continuer)
    {
        /* 1. Affichage */
        afficher_niveau();
        afficher_joueur(j1);
        MLV_actualise_window();

        /* 2. Vérification de la touche Echap pour quitter (Non-bloquant) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
            continuer = 0;
        }
        /* 3. Déplacement fluide sans cooldown */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
            deplacer_joueur(&j1, MLV_KEYBOARD_UP, map);
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
            deplacer_joueur(&j1, MLV_KEYBOARD_DOWN, map);
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
            deplacer_joueur(&j1, MLV_KEYBOARD_LEFT, map);
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
            deplacer_joueur(&j1, MLV_KEYBOARD_RIGHT, map);
        }
        /* 4. Maintien strict du framerate à 60 FPS */
        MLV_wait_milliseconds(16);
        /* 4. Limitation du processeur à environ 60 images par seconde (16 millisecondes) */
        MLV_wait_milliseconds(16);
    }

    MLV_free_window();
    return 0;
}