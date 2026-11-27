#include "joueur.h"
#include "constante.h"

void initialiser_joueur(entite *j, int x_depart, int y_depart){
    /* On convertit la case de départ en PIXELS (le centre de la case) */
    j->pos.x = (x_depart * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    j->pos.y = (y_depart * TAILLE_CASE) + (TAILLE_CASE / 2.0);
    j->est_en_vie = 1;
    j->direction = 3; /* regarde vers la droite */
    j->en_mouvement = 0;
    j->frame_actuelle = 0;
    j->vitesse_anim = MLV_get_time();
}

void charger_images_joueur(MLV_Image **sprite_joueur) {
    *sprite_joueur = MLV_load_image("Ressources/frisk_mlv.png");
    if (*sprite_joueur != NULL) MLV_resize_image(*sprite_joueur, LARGEUR_JOUEUR * 4, HAUTEUR_JOUEUR * 4);
}

void afficher_joueur(entite j, MLV_Image *sprite_joueur) {
    /* dimensions d'une seule cellule d'animation du sprite */
    int largeur = LARGEUR_JOUEUR;
    int hauteur = HAUTEUR_JOUEUR;
    int frame_a_dessiner, direction;

    if (j.en_mouvement == 1) {
        frame_a_dessiner = j.frame_actuelle;
        direction = j.direction;
    }
    else{ /* si le joueur est a l'arret, on force la frame 1 du perso vers le bas */
        frame_a_dessiner = 1;
        direction = 1;
    }

    if (sprite_joueur == NULL) MLV_draw_filled_rectangle(j.pos.x - (largeur / 2), j.pos.y - (hauteur / 2), largeur, hauteur, MLV_COLOR_BLUE);
    else {
        MLV_draw_partial_image(
            sprite_joueur,
            frame_a_dessiner * largeur,
            direction * hauteur,
            largeur,
            hauteur,
            j.pos.x - (largeur / 2),
            j.pos.y - (hauteur / 2)
        ); 
        /*MLV_draw_partial_image	(	const MLV_Image * 	image, 	L'image à afficher sur la fenêtre
                                        int 	x_source,  La coordonnée en X du sommet Nord-Ouest de la partie de l'image à afficher.
                                        int 	y_source,  La coordonnée en Y du sommet Nord-Ouest de la partie de l'image à afficher.
                                        int 	width_source,  	La largeur de la partie de l'image à afficher.
                                        int 	height_source,  	La hauteur de la partie de l'image à afficher.
                                        int 	x,  Coordonnée en X de la position dans la fenêtre du sommet Nord-Ouest de la partie de l'image à afficher.
                                        int 	y   Coordonnée en Y de la position dans la fenêtre du sommet Nord-Ouest de la partie de l'image à afficher.
                                    )	
                                        sert à dessiner la partie du sprite correspondant au moment*/
    }
}

void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES])
{
    float futur_x = j->pos.x;
    float futur_y = j->pos.y;
    float vitesse = 3.0; /* le joueur avance de 3 pixels à chaque image */
    /* le rayon physique du joueur */
    int rayon_x = (HAUTEUR_JOUEUR / 2) - 2;
    int rayon_y = (LARGEUR_JOUEUR / 2) - 2;
    int max_frames = 4; /* correspond au nb d'image dans le sprite */
    int coter_gauche, coter_droite, coter_haut, coter_bas;
    /* on réinitialise le mouvement pour que le joueur s'arrête si on ne touche à rien */
    j->en_mouvement = 0;

    if (touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z)
    {
        futur_y = futur_y - vitesse;
        j->direction = 0; /* Ligne 0 de l'image vaut Haut */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s)
    {
        futur_y = futur_y + vitesse;
        j->direction = 1; /* Ligne 1 de l'image vaut Bas */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_q)
    {
        futur_x = futur_x - vitesse;
        j->direction = 2; /* Ligne 2 de l'image vaut gauche */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_d)
    {
        futur_x = futur_x + vitesse;
        j->direction = 3; /* Ligne 3 de l'image vaut droite */
        j->en_mouvement = 1;
    }
    /* gestion de l'annimation */
    if (j->en_mouvement == 1)
    {
        int temps_actuel = MLV_get_time();

        /* On soustrait l'heure actuelle à l'ancienne heure pour voir le temps écoulé pour ne pas dépendre du nb de fps
           le temps 200ms est choisit arbitrairement pour avoir une animation fluide */
        if (temps_actuel - j->vitesse_anim >= 200)
        {
            /* On met à jour l'heure du dernier changement d'image */
            j->vitesse_anim = temps_actuel;
            j->frame_actuelle++;

            if (j->frame_actuelle >= max_frames)
            {
                j->frame_actuelle = 0;
            }
        }
    }
    else
    {
        /* on garde le temps actuelle si le joueur est à l'arret pour ne pas faire bugger l'annimation */
        j->vitesse_anim = MLV_get_time();
    }
    /* on calcule où se trouveront les 4 bords du joueur en pixels
       on divise par TAILLE_CASE pour savoir dans quelles cases de la map ils tombent */
    coter_gauche = (futur_x - rayon_y) / TAILLE_CASE;
    coter_droite = (futur_x + rayon_y) / TAILLE_CASE;
    coter_haut   = (futur_y - rayon_x) / TAILLE_CASE;
    coter_bas    = (futur_y + rayon_x) / TAILLE_CASE;

    /* on vérifie que les 4 coins du joueur sont bien sur de l'air (0) */
    if (map[coter_haut][coter_gauche] == 0 &&
        map[coter_haut][coter_droite] == 0 &&
        map[coter_bas][coter_gauche] == 0 &&
        map[coter_bas][coter_droite] == 0)
    {
        /* on valide le mouvement si aucun mur ne touche notre cercle */
        j->pos.x = futur_x;
        j->pos.y = futur_y;
    }
}
void liberer_images_joueur(MLV_Image *sprite_joueur) {
    if (sprite_joueur != NULL) MLV_free_image(sprite_joueur);
}