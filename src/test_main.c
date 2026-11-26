#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "constante.h"
#include "entite.h"
#include "level.h"
#include "joueur.h"
#include "bombe.h"
#include "menu_du_jeu.h"
#include "sauvegarde.h"
#include "victoire_defaite.h"

int main(void) {
    int map[LIGNES][COLONNES];
    Images_niveau imgs;
    MLV_Image *sprite_joueur = NULL;
    entite joueur;
    bombe bombe_joueur;
    int fin_jeu = 0;
    int en_menu = 1;
    int etat_jeu;
    int touche_bombe = 0;
    int touche_save = 0;
    int touche_load = 0;
    int touche_rand = 0;
    int touche_lvl1 = 0;
    int touche_victoire = 0;
    int victoire_affichee = 0;
    int i, j;
    MLV_Keyboard_button touche;
    MLV_Font *police_bouton;
    MLV_Font *police_titre;

    srand((unsigned int)time(NULL));

    /* 1. Creation de la fenetre et chargement des ressources */
    MLV_create_window("Bomberman - Test", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);
    MLV_change_frame_rate(60);

    charger_images_niveau(&imgs);
    charger_images_joueur(&sprite_joueur);
    charger_images_bombe();
    police_bouton = MLV_load_font(FONT, 20);
    police_titre = MLV_load_font(FONT, 50);

    if (police_bouton == NULL || police_titre == NULL) {
        fprintf(stderr, "Erreur : impossible de charger la police (%s).\n", FONT);
        if (police_bouton != NULL) MLV_free_font(police_bouton);
        if (police_titre != NULL) MLV_free_font(police_titre);
        liberer_images_joueur(sprite_joueur);
        liberer_images_bombe();
        liberer_images_niveau(&imgs);
        MLV_free_window();
        return 1;
    }

    /* 2. Boucle du menu principal */
    while (en_menu) {
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_menu(police_titre, police_bouton);
        MLV_actualise_window();

        etat_jeu = interagir_menu(police_bouton);

        if (etat_jeu == jouer) {
            rempl_lvl_1(map);
            initialiser_joueur(&joueur, 1, 1);
            printf("[TEST] Nouvelle partie lancee (niveau 1).\n");
            en_menu = 0;
        }
        else if (etat_jeu == charger) {
            if (charger_partie(map, &joueur, 1) == 0) {
                printf("[TEST] Sauvegarde 1 chargee avec succes.\n");
                en_menu = 0;
            }
            else {
                printf("[TEST] Echec chargement slot 1 (sauvegarde d'abord avec K en jeu).\n");
            }
        }
        else if (etat_jeu == options) {
            printf("[TEST] Bouton Options clique (module non implemente).\n");
        }
        else if (etat_jeu == quitter) {
            fin_jeu = 1;
            en_menu = 0;
        }
    }

    bombe_joueur.b.est_en_vie = 0;
    bombe_joueur.state = BOMBE_MECHE;

    /* 3. Boucle principale de test */
    while (!fin_jeu) {
        touche = MLV_KEYBOARD_NONE;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED) {
            fin_jeu = 1;
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

        /* Deplacement du joueur */
        deplacer_joueur(&joueur, touche, map);

        /* Gestion de la bombe (touche E) */
        if (bombe_joueur.b.est_en_vie == 1) {
            if (bombe_expiree(&bombe_joueur) == 1) {
                printf("[TEST] Bombe expiree.\n");
            }
        }
        if (MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED) {
            if (!touche_bombe && bombe_joueur.b.est_en_vie == 0) {
                placer_bombe(&bombe_joueur, joueur);
                printf("[TEST] Bombe posee en (%.1f, %.1f).\n",
                       bombe_joueur.b.pos.x, bombe_joueur.b.pos.y);
                touche_bombe = 1;
            }
        }
        else {
            touche_bombe = 0;
        }

        /* Test sauvegarde (touche K -> slot 1) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_k) == MLV_PRESSED) {
            if (!touche_save) {
                if (sauvegarder_partie(map, joueur, 1) == 0) {
                    printf("[TEST] Partie sauvegardee dans sauvegarde1.txt.\n");
                }
                touche_save = 1;
            }
        }
        else {
            touche_save = 0;
        }

        /* Test chargement (touche L -> slot 1) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_l) == MLV_PRESSED) {
            if (!touche_load) {
                if (charger_partie(map, &joueur, 1) == 0) {
                    victoire_affichee = 0;
                    printf("[TEST] Partie chargee depuis sauvegarde1.txt.\n");
                }
                touche_load = 1;
            }
        }
        else {
            touche_load = 0;
        }

        /* Test niveau aleatoire (touche R) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED) {
            if (!touche_rand) {
                rempl_lvl_1(map);
                rempl_lvl_rand(map);
                initialiser_joueur(&joueur, 1, 1);
                victoire_affichee = 0;
                printf("[TEST] Carte aleatoire generee.\n");
                touche_rand = 1;
            }
        }
        else {
            touche_rand = 0;
        }

        /* Retour au niveau 1 fixe (touche N) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_n) == MLV_PRESSED) {
            if (!touche_lvl1) {
                rempl_lvl_1(map);
                initialiser_joueur(&joueur, 1, 1);
                victoire_affichee = 0;
                printf("[TEST] Retour au niveau 1 fixe.\n");
                touche_lvl1 = 1;
            }
        }
        else {
            touche_lvl1 = 0;
        }

        /* Test verif_victoire (touche V : detruit tous les blocs 1) */
        if (MLV_get_keyboard_state(MLV_KEYBOARD_v) == MLV_PRESSED) {
            if (!touche_victoire) {
                for (i = 0; i < LIGNES; i++) {
                    for (j = 0; j < COLONNES; j++) {
                        if (map[i][j] == 1) {
                            map[i][j] = 0;
                        }
                    }
                }
                touche_victoire = 1;
            }
        }
        else {
            touche_victoire = 0;
        }

        /* Verification de la victoire (0 = plus aucun bloc destructible) */
        if (verif_victoire(map) == 0 && !victoire_affichee) {
            printf("[TEST] VICTOIRE detectee par verif_victoire() !\n");
            victoire_affichee = 1;
        }

        /* Rendu graphique */
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_niveau(map, imgs);
        if (bombe_joueur.b.est_en_vie == 1) {
            afficher_bombe(bombe_joueur);
        }
        afficher_joueur(joueur, sprite_joueur);

        if (victoire_affichee) {
            MLV_draw_text_with_font(200, 20, "VICTOIRE !", police_titre, MLV_COLOR_YELLOW);
        }

        MLV_actualise_window();
        MLV_delay_according_to_frame_rate();
    }

    /* 4. Liberation de la memoire */
    liberer_images_joueur(sprite_joueur);
    liberer_images_bombe();
    liberer_images_niveau(&imgs);
    MLV_free_font(police_bouton);
    MLV_free_font(police_titre);
    MLV_free_window();

    return 0;
}