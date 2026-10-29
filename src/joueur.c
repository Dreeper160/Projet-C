#include "joueur.h"
#include "constante.h"

static MLV_Image *sprite_joueur = NULL;

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

void charger_images_joueur() {
    sprite_joueur = MLV_load_image("Ressources/sprite_frisk.png");
    MLV_resize_image(sprite_joueur, 150, 150);
}
void afficher_joueur(entite j){
    /* dimensions d'une seule cellule d'animation du sprite */
    int largeur = 38; 
    int hauteur = 38;
    int frame_a_dessiner;
/* si le joueur est à l'arrêt, on force la frame 0  */
    if (j.en_mouvement == 1) {
    frame_a_dessiner = j.frame_actuelle; 
    } else {
    frame_a_dessiner = 0; 
    }
    MLV_draw_partial_image(
        sprite_joueur,
        frame_a_dessiner * largeur,
        j.direction * hauteur,    
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

void deplacer_joueur(entite *j, MLV_Keyboard_button touche, int map[LIGNES][COLONNES]){
    float futur_x = j->pos.x;
    float futur_y = j->pos.y;
    float vitesse = 3.0; /* le joueur avance de 3 pixels à chaque image */
    int rayon = (TAILLE_CASE / 2) - 4; /* le rayon physique du joueur (18 pixels) */
    int max_frames = 4; /* correspond au nb d'image dans le sprite */
    int case_gauche, case_droite, case_haut, case_bas;
    /* on réinitialise le mouvement si on ne touche à rien, il s'arrête */
    j->en_mouvement = 0;

    if (touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_z) {
        futur_y = futur_y - vitesse;
        j->direction = 3; /* Ligne 3 de l'image vaut Haut */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_s) {
        futur_y = futur_y + vitesse;
        j->direction = 0; /* Ligne 2 de l'image vaut Bas */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_LEFT || touche == MLV_KEYBOARD_q) {
        futur_x = futur_x - vitesse;
        j->direction = 1; /* Ligne 1 de l'image vaut gauche */
        j->en_mouvement = 1;
    }
    else if (touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_d) {
        futur_x = futur_x + vitesse;
        j->direction = 2; /* Ligne 3 de l'image vaut droite */
        j->en_mouvement = 1;
    }
    /* gestion de l'annimation */
    if (j->en_mouvement == 1) {
        int temps_actuel = MLV_get_time();
        
        /* On soustrait l'heure actuelle à l'ancienne heure pour voir le temps écoulé pour ne pas dépendre du nb de fps
           le temps 200ms est choisit arbitrairement pour avoir une animation fluide */
        if (temps_actuel - j->vitesse_anim >= 200) {  
            /* On met à jour l'heure du dernier changement d'image */
            j->vitesse_anim = temps_actuel; 
            j->frame_actuelle++;
        /* on vérifie si on se déplace horizontalement car on a que 2 images dans le sprite pour le déplacement horizontale */
            if (j->direction == 1 || j->direction == 2) {
                max_frames = 2;
            }
            
            if (j->frame_actuelle >= max_frames) {
                j->frame_actuelle = 0;
            }
        }
    } else {
        /* on garde le temps actuelle si le joueur est à l'arret pour ne pas faire bugger l'annimation */
        j->vitesse_anim = MLV_get_time();
    }
    /* on calcule où se trouveront les 4 bords du joueur en pixels 
       on divise par TAILLE_CASE pour savoir dans quelles cases de la map ils tombent */
    case_gauche = (futur_x - rayon) / TAILLE_CASE;
    case_droite = (futur_x + rayon) / TAILLE_CASE;
    case_haut   = (futur_y - rayon) / TAILLE_CASE;
    case_bas    = (futur_y + rayon) / TAILLE_CASE;

    /* on vérifie que les 4 coins du joueur sont bien sur de l'air (0) */
    if (map[case_haut][case_gauche] == 0 &&
        map[case_haut][case_droite] == 0 &&
        map[case_bas][case_gauche] == 0 &&
        map[case_bas][case_droite] == 0) 
    {
    /* aucun mur ne touche notre cercle, on valide le mouvement ! */
        j->pos.x = futur_x;
        j->pos.y = futur_y;
    }
}
void liberer_images_joueur() {
    if (sprite_joueur != NULL) {
        MLV_free_image(sprite_joueur);
    }
}