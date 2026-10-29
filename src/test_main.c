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
    charger_images_niveau();
    charger_images_joueur();
    MLV_Font *police_bouton = MLV_load_font(FONT, 20);
    MLV_Font *police_titre = MLV_load_font(FONT, 50);

    afficher_menu(police_titre, police_bouton);
    MLV_actualise_window();
    while (etat_jeu == 0 || etat_jeu == -1)
    {
        etat_jeu = interagir_menu(police_bouton);
    }

    /* --- BOUCLE PRINCIPALE --- */
    while (continuer)
    {
        if (etat_jeu == 1)
        {
            /* --- JEU --- */
            if (bomb1.b.est_en_vie == 1)
            {
                bombe_expiree(&bomb1);
            }

            /* 1. Affichage */
            afficher_niveau();

            if (bomb1.b.est_en_vie == 1)
            {
                afficher_bombe(bomb1);
            }

            afficher_joueur(j1);
            MLV_actualise_window();

            /* 2. Quitter le jeu */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
            {
                continuer = 0;
            }

            /* 3. Poser la bombe (Touche e et non espace ) */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED)
            {
                /* On vérifie que la touche n'était pas déjà enfoncée et qu'il n'y a pas déjà une bombe */
                if (touche_espace_pressee == 0 && bomb1.b.est_en_vie == 0)
                {
                    placer_bombe(&bomb1, j1);
                    touche_espace_pressee = 1;
                }
            }
            else
            {
                touche_espace_pressee = 0;
            }

            /* 4. Déplacement fluide */
            if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED)
            {
                deplacer_joueur(&j1, MLV_KEYBOARD_UP, map);
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED)
            {
                deplacer_joueur(&j1, MLV_KEYBOARD_DOWN, map);
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED)
            {
                deplacer_joueur(&j1, MLV_KEYBOARD_LEFT, map);
            }
            else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED || MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED)
            {
                deplacer_joueur(&j1, MLV_KEYBOARD_RIGHT, map);
            }

            MLV_wait_milliseconds(16);
        }
    }
    liberer_images_niveau();
    liberer_images_joueur();
    MLV_free_window();
    return 0;
}