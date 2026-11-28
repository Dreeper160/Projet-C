#include <stdio.h>
#include <stdlib.h>
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
#include "sauvegarde.h"
#include "victoire_defaite.h"

int main(void)
{
    int map[LIGNES][COLONNES];
    Images_niveau imgs;
    MLV_Image *sprite_joueur = NULL;
    entite joueur;
    bombe bombe_joueur;
    bonus bonus_jeu;
    int fin_jeu = 0;
    int en_menu = 1;
    int etat_jeu = quitter;
    int touche_bombe = 0;
    int touche_save = 0;
    int touche_load = 0;
    int touche_rand = 0;
    int touche_lvl1 = 0;
    int touche_victoire = 0;
    int victoire_affichee = 0;
    int audio_initialise = 0;
    int bonus_actif_precedent;
    int i, j;
    explosion explosion_joueur;
    MLV_Keyboard_button touche;
    MLV_Font *police_bouton;
    MLV_Font *police_titre;
    MLV_Music *musique_bonus = NULL;

    bombe_joueur.rayon = RAYON_BOMBE_BASE;
    bombe_joueur.b.est_en_vie = 0;
    bombe_joueur.state = BOMBE_MECHE;
    initialiser_bonus(&bonus_jeu);
    explosion_joueur.active = 0;
    explosion_joueur.nb_cases = 0;

    srand((unsigned int)time(NULL));

    MLV_create_window("Bomberman", "Bomberman", COLONNES * TAILLE_CASE, LIGNES * TAILLE_CASE);
    MLV_change_frame_rate(60);

    charger_images_niveau(&imgs);
    charger_images_joueur(&sprite_joueur);
    charger_images_bombe();
    charger_images_explosion();
    charger_images_trifolium();
    police_bouton = MLV_load_font(FONT, 20);
    police_titre = MLV_load_font(FONT, 50);

    if (police_bouton == NULL || police_titre == NULL)
    {
        fprintf(stderr, "Erreur : impossible de charger la police (%s).\n", FONT);
        if (police_bouton != NULL)
            MLV_free_font(police_bouton);
        if (police_titre != NULL)
            MLV_free_font(police_titre);
        liberer_images_joueur(sprite_joueur);
        liberer_images_bombe();
        liberer_images_explosion();
        liberer_images_trifolium();
        liberer_images_niveau(&imgs);
        MLV_free_window();
        return 1;
    }

    while (en_menu)
    {
        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_menu(police_titre, police_bouton);
        MLV_actualise_window();
        etat_jeu = interagir_menu(police_bouton);

        if (etat_jeu == jouer)
        {
            rempl_lvl_1(map);
            initialiser_joueur(&joueur, 1, 1);
            en_menu = 0;
        }
        else if (etat_jeu == charger)
        {
            if (charger_partie(map, &joueur, 1) == 0)
                en_menu = 0;
            else
                fprintf(stderr, "Impossible de charger la sauvegarde 1.\n");
        }
        else if (etat_jeu == options)
        {
            fprintf(stderr, "Le menu Options n'est pas encore implemente.\n");
        }
        else if (etat_jeu == quitter)
        {
            fin_jeu = 1;
            en_menu = 0;
        }
    }

    if (!fin_jeu)
    {
        MLV_init_audio();
        audio_initialise = 1;
        musique_bonus = MLV_load_music("Ressources/sounds/Yu-Peng_Chen_HOYO-MiX_-_Let_s_Go_Crimson_Knight.mp3");
        if (musique_bonus == NULL)
            fprintf(stderr, "Impossible de charger la musique du bonus; la partie continue sans musique.\n");
    }

    while (!fin_jeu)
    {
        touche = MLV_KEYBOARD_NONE;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) == MLV_PRESSED)
        {
            fin_jeu = 1;
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

        deplacer_joueur(&joueur, touche, map);
        if (bombe_joueur.b.est_en_vie == 1 &&
            bombe_expiree(&bombe_joueur) == 1)
            executer_explosion(&explosion_joueur, &bombe_joueur, map, &bonus_jeu);

        bonus_actif_precedent = bonus_jeu.effet.actif;
        actualiser_bonus(&bonus_jeu);
        if (bonus_actif_precedent == 1 && bonus_jeu.effet.actif == 0)
        {
            bombe_joueur.rayon = RAYON_BOMBE_BASE;
            if (musique_bonus != NULL)
                Mix_FadeOutMusic(4000);
        }

        if (ramasser_trifolium(&bonus_jeu, &joueur) == 1)
        {
            if (musique_bonus != NULL)
                MLV_play_music(musique_bonus, 1.0, -1);
            bombe_joueur.rayon = RAYON_BONUS;
        }

        actualiser_explosion(&explosion_joueur);
        if (bonus_jeu.effet.actif == 0 &&
            joueur_touche_explosion(&explosion_joueur, &joueur))
            joueur.est_en_vie = 0;

        if (MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED)
        {
            if (!touche_bombe && bombe_joueur.b.est_en_vie == 0)
            {
                placer_bombe(&bombe_joueur, joueur);
                touche_bombe = 1;
            }
        }
        else
        {
            touche_bombe = 0;
        }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_k) == MLV_PRESSED)
        {
            if (!touche_save)
            {
                if (sauvegarder_partie(map, joueur, 1) == 0)
                    printf("Partie sauvegardee dans saves/sauvegarde1.txt.\n");
                touche_save = 1;
            }
        }
        else
        {
            touche_save = 0;
        }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_l) == MLV_PRESSED)
        {
            if (!touche_load)
            {
                if (charger_partie(map, &joueur, 1) == 0)
                    victoire_affichee = 0;
                touche_load = 1;
            }
        }
        else
        {
            touche_load = 0;
        }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_r) == MLV_PRESSED)
        {
            if (!touche_rand)
            {
                rempl_lvl_1(map);
                rempl_lvl_rand(map);
                initialiser_joueur(&joueur, 1, 1);
                victoire_affichee = 0;
                touche_rand = 1;
            }
        }
        else
        {
            touche_rand = 0;
        }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_n) == MLV_PRESSED)
        {
            if (!touche_lvl1)
            {
                rempl_lvl_1(map);
                initialiser_joueur(&joueur, 1, 1);
                victoire_affichee = 0;
                touche_lvl1 = 1;
            }
        }
        else
        {
            touche_lvl1 = 0;
        }

        if (MLV_get_keyboard_state(MLV_KEYBOARD_v) == MLV_PRESSED)
        {
            if (!touche_victoire)
            {
                for (i = 0; i < LIGNES; i++)
                {
                    for (j = 0; j < COLONNES; j++)
                    {
                        if (map[i][j] == 1)
                            map[i][j] = 0;
                    }
                }
                touche_victoire = 1;
            }
        }
        else
        {
            touche_victoire = 0;
        }

        if (verif_victoire(map) == 0)
            victoire_affichee = 1;

        MLV_clear_window(MLV_COLOR_BLACK);
        afficher_niveau(map, imgs);
        afficher_trifolium(&bonus_jeu);
        afficher_explosion(&explosion_joueur);
        if (bombe_joueur.b.est_en_vie == 1)
            afficher_bombe(bombe_joueur, bonus_jeu.effet.actif);
        afficher_joueur(joueur, sprite_joueur);
        if (victoire_affichee)
            MLV_draw_text_with_font(200, 20, "VICTOIRE !", police_titre, MLV_COLOR_YELLOW);
        MLV_actualise_window();
        MLV_delay_according_to_frame_rate();
    }

    liberer_images_joueur(sprite_joueur);
    liberer_images_bombe();
    liberer_images_explosion();
    liberer_images_trifolium();
    liberer_images_niveau(&imgs);
    MLV_free_font(police_bouton);
    MLV_free_font(police_titre);
    if (audio_initialise)
    {
        if (musique_bonus != NULL)
        {
            MLV_stop_music();
            MLV_free_music(musique_bonus);
        }
        MLV_free_audio();
    }
    MLV_free_window();

    return 0;
}
