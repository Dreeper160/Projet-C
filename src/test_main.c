#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include "constante.h"
#include "entite.h"
#include "level.h"
#include "joueur.h"
#include "bombe.h"
#include "bonus.h"
#include "menu_du_jeu.h"
#include "explosion.h"

int main(void)
{
    /* Déclarations en haut de bloc (norme C89) */
    int map[LIGNES][COLONNES];
    Images_niveau imgs;
    entite joueur;
    bombe bombe_joueur;
    bonus bonus_jeu;
    int quitter = 0;
    int touche_bombe_pressee = 0;
    int etat_jeu = 0;
    explosion explosion_joueur;
    MLV_Keyboard_button touche;
    MLV_Font *police_bouton;
    MLV_Font *police_titre;
    MLV_Music *musique_bonus;
    int bonus_actif_precedent;

    bombe_joueur.rayon = RAYON_BOMBE_BASE;
    initialiser_bonus(&bonus_jeu);
    explosion_joueur.active = 0;
    explosion_joueur.nb_cases = 0;

    /* Initialisation de l'aléatoire pour rempl_lvl_rand */
    srand((unsigned int)time(NULL));

    /* 1. Création de la fenêtre (toujours avant les chargements MLV) */
    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);
    charger_images_joueur();
    charger_images_bombe();
    charger_images_explosion();
    charger_images_trifolium();
    police_bouton = MLV_load_font(FONT, 20);
    police_titre = MLV_load_font(FONT, 50);

    if (police_bouton == NULL || police_titre == NULL)
    {
        liberer_images_joueur();
        liberer_images_bombe();
        liberer_images_explosion();
        liberer_images_trifolium();
        MLV_free_window();
        return 1;
    }

    afficher_menu(police_titre, police_bouton);
    MLV_actualise_window();
    while (etat_jeu == 0 || etat_jeu == -1)
    {
        etat_jeu = interagir_menu(police_bouton);
    }
    if (etat_jeu == quitter)
    {
        liberer_images_joueur();
        liberer_images_bombe();
        liberer_images_explosion();
        liberer_images_trifolium();
        MLV_free_font(police_bouton);
        MLV_free_font(police_titre);
        MLV_free_window();
        return 0;
    }

    MLV_init_audio();
    musique_bonus = MLV_load_music("Ressources/sounds/Yu-Peng_Chen_HOYO-MiX_-_Let_s_Go_Crimson_Knight.mp3");
    if (musique_bonus == NULL)
    {
        fprintf(stderr, "Impossible de charger la musique du bonus.\n");
        MLV_free_audio();
        liberer_images_joueur();
        liberer_images_bombe();
        liberer_images_explosion();
        liberer_images_trifolium();
        MLV_free_font(police_bouton);
        MLV_free_font(police_titre);
        MLV_free_window();
        return 1;
    }

    /* 2. Chargement des ressources */
    charger_images_niveau(&imgs);

    /* 3. Initialisation de la carte et du joueur */
    rempl_lvl_1(map);
    rempl_lvl_rand(map); /* Commente cette ligne pour tester le niveau 1 fixe */
    initialiser_joueur(&joueur, 1, 1);
    bombe_joueur.b.est_en_vie = 0;
    bombe_joueur.state = BOMBE_MECHE;

    /* 4. Boucle principale */
    while (!quitter)
    {
        touche = MLV_KEYBOARD_NONE;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
        {
            quitter = 1;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_UP) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED)
        {
            touche = MLV_KEYBOARD_UP;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_DOWN) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED)
        {
            touche = MLV_KEYBOARD_DOWN;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_LEFT) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED)
        {
            touche = MLV_KEYBOARD_LEFT;
        }
        else if (MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) == MLV_PRESSED ||
                 MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED)
        {
            touche = MLV_KEYBOARD_RIGHT;
        }

        /* Mise à jour logique */
        deplacer_joueur(&joueur, touche, map);
        if (bombe_joueur.b.est_en_vie == 1 &&
            bombe_expiree(&bombe_joueur) == 1)
        {
            executer_explosion(&explosion_joueur, &bombe_joueur, map, &bonus_jeu);
        }
        bonus_actif_precedent = bonus_jeu.effet.actif;
        actualiser_bonus(&bonus_jeu);
        if (bonus_actif_precedent == 1 && bonus_jeu.effet.actif == 0)
        {
            bombe_joueur.rayon = RAYON_BOMBE_BASE;
            Mix_FadeOutMusic(4000);
        }

        if (ramasser_trifolium(&bonus_jeu, &joueur) == 1)
        {
            MLV_play_music(musique_bonus, 1.0, -1);
            bombe_joueur.rayon = RAYON_BONUS;
        }
        actualiser_explosion(&explosion_joueur);
        if (bonus_jeu.effet.actif == 0 &&
            joueur_touche_explosion(&explosion_joueur, &joueur))
            joueur.est_en_vie = 0;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED)
        {
            if (touche_bombe_pressee == 0 &&
                bombe_joueur.b.est_en_vie == 0)
            {
                placer_bombe(&bombe_joueur, joueur);
                touche_bombe_pressee = 1;
            }
        }
        else
        {
            touche_bombe_pressee = 0;
        }

        /* Rendu graphique */
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_niveau(map, imgs);
        afficher_trifolium(&bonus_jeu);
        afficher_explosion(&explosion_joueur);
        if (bombe_joueur.b.est_en_vie == 1)
        {
            afficher_bombe(bombe_joueur, bonus_jeu.effet.actif);
        }
        afficher_joueur(joueur);
        MLV_actualise_window();

        /* Synchronisation à 60 FPS */
        MLV_delay_according_to_frame_rate();
    }

    /* 5. Libération propre de la mémoire */
    liberer_images_joueur();
    liberer_images_bombe();
    liberer_images_explosion();
    liberer_images_trifolium();
    liberer_images_niveau(&imgs);
    MLV_free_font(police_bouton);
    MLV_free_font(police_titre);
    MLV_stop_music();
    MLV_free_music(musique_bonus);
    MLV_free_audio();
    MLV_free_window();

    return 0;
}