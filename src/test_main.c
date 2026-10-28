#include <MLV/MLV_all.h>
#include "constante.h"
#include "entite.h"
#include "joueur.h"
#include "level.h"

int main(void)
{
    entite j1;
    int continuer = 1;
    
    /* Variable pour empêcher le joueur de traverser la carte à la vitesse de la lumière */
    int cooldown = 0; 

    initialiser_joueur(&j1, 1, 1);

    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);

    /* --- LA BOUCLE DE JEU (60 FPS) --- */
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

        /* 3. Déplacement fluide avec délai */
        if (cooldown == 0) {
            /* MLV_get_keyboard_state lit le clavier en direct sans jamais mettre le jeu en pause */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
                deplacer_joueur(&j1, MLV_KEYBOARD_UP, map);
                cooldown = 10; /* On bloque le mouvement pendant 10 "tours" de boucle */
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
                deplacer_joueur(&j1, MLV_KEYBOARD_DOWN, map);
                cooldown = 10;
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
                deplacer_joueur(&j1, MLV_KEYBOARD_LEFT, map);
                cooldown = 10;
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
                deplacer_joueur(&j1, MLV_KEYBOARD_RIGHT, map);
                cooldown = 10;
            }
        } else {
            /* Si le cooldown n'est pas à 0, on le diminue à chaque tour de boucle */
            cooldown--;
        }

        /* 4. Limitation du processeur à environ 60 images par seconde (16 millisecondes) */
        MLV_wait_milliseconds(16);
    }

    MLV_free_window();
    return 0;
}