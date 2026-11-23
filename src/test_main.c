#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "constante.h"
#include "entite.h"
#include "level.h"
#include "joueur.h"

int main(void) {
    /* Déclarations en haut de bloc (norme C89) */
    int map[LIGNES][COLONNES];
    Images_niveau imgs;
    entite joueur;
    int quitter = 0;
    MLV_Keyboard_button touche;

    /* Initialisation de l'aléatoire pour rempl_lvl_rand */
    srand((unsigned int)time(NULL));

    /* 1. Création de la fenêtre (toujours avant les chargements MLV) */
    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);
    MLV_change_frame_rate(60);

    /* 2. Chargement des ressources */
    charger_images_niveau(&imgs);
    charger_images_joueur();

    /* 3. Initialisation de la carte et du joueur */
    rempl_lvl_1(map);
    rempl_lvl_rand(map); /* Commente cette ligne pour tester le niveau 1 fixe */
    initialiser_joueur(&joueur, 1, 1);

    /* 4. Boucle principale */
    while (!quitter) {
        touche = MLV_KEYBOARD_NONE;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
            quitter = 1;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
            touche = MLV_KEYBOARD_UP;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
            touche = MLV_KEYBOARD_DOWN;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
            touche = MLV_KEYBOARD_LEFT;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
            touche = MLV_KEYBOARD_RIGHT;
        }

        /* Mise à jour logique */
        deplacer_joueur(&joueur, touche, map);

        /* Rendu graphique */
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_niveau(map, imgs);
        afficher_joueur(joueur);
        MLV_actualise_window();

        /* Synchronisation à 60 FPS */
        MLV_delay_according_to_frame_rate();
    }

    /* 5. Libération propre de la mémoire */
    liberer_images_joueur();
    liberer_images_niveau(&imgs);
    MLV_free_window();

    return 0;
}