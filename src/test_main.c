#include "constante.h"
#include "entite.h"
#include "joueur.h"
#include "level.h"
#include "bombe.h"
#include "menu_du_jeu.h"
#include <MLV/MLV_all.h>

int main()
{
    entite j1;
    bombe bomb1;
    int continuer = 1;
    int etat_jeu = 0; /* 0 = Menu, 1 = En jeu */
    
    /* Variable pour empêcher de poser 60 bombes par seconde si on maintient Espace */
    int touche_espace_pressee = 0; 

    /* Initialisations */
    initialiser_joueur(&j1, 1, 1);
    bomb1.b.est_en_vie = 0; /* La bombe n'est pas posée au démarrage */

    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);

    /* --- BOUCLE PRINCIPALE --- */
    while (continuer)
    {
        if (etat_jeu == 0)
        {
            /* --- MENU --- */
            MLV_clear_window(MLV_COLOR_BLACK);
            afficher_menu();
            MLV_actualise_window();

            /* Appel de ta fonction test (elle met le jeu en pause en attendant le clic) */
            interagir_menu();
            MLV_actualise_window();
            
            /* Pour le test : on attend 1 seconde pour te laisser lire les coordonnées, puis on lance le jeu */
            MLV_wait_milliseconds(1000);
            etat_jeu = 1;
        }
        else if (etat_jeu == 1)
        {
            /* --- JEU --- */
            /* 1. Affichage */
            afficher_niveau();

            /* Si la bombe est active, on la dessine d'abord pour que le joueur passe par-dessus */
            if (bomb1.b.est_en_vie == 1) {
                afficher_bombe(bomb1);
            }

            afficher_joueur(j1);
            MLV_actualise_window();

            /* 2. Quitter le jeu */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
                continuer = 0;
            }

            /* 3. Poser la bombe (Touche Espace) */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
                /* On vérifie que la touche n'était pas déjà enfoncée et qu'il n'y a pas déjà une bombe */
                if (touche_espace_pressee == 0 && bomb1.b.est_en_vie == 0) {
                    placer_bombe(&bomb1, j1);
                    touche_espace_pressee = 1;
                }
            } else {
                touche_espace_pressee = 0;
            }

            /* 4. Déplacement fluide */
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

            MLV_wait_milliseconds(16);
        }
    }

    MLV_free_window();
    return 0;
}